//
// Created by ariel on 28-Nov-18.
//

#include <algorithm>
#include "MyImplementation.h"

/**
 * Constructor
 */
MyImplementation::MyImplementation() {
    m_isEmpsLoaded = m_isPlanesLoaded = m_isFlightsLoaded = m_isCustomersLoaded = m_isResLoaded =
    m_isPlanesDatesLoaded = false;
}

MyImplementation::~MyImplementation() {
    // Deleting all the allocated memory
    for (auto &itor : m_employees) { delete itor; }
    for (auto &itor : m_flights) { delete itor; }
    for (auto &itor : m_planes) { delete itor; }
    for (auto &itor : m_customers) { delete itor; }
    for (auto &itor : m_reservations) { delete itor; }
}

Employee *MyImplementation::addEmployee(int seniority, int birthYear, string employerId, Jobs title) {
    // Getting the employer of the employee (if exists)
    Employee *employer;
    if (employerId.length() == 0) {
        employer = nullptr;
    } else {
        try {
            employer = this->getEmployee(employerId);
        } catch (const invalid_argument &ia) {
            employer = nullptr;
        }
    }
    Employee *emp = new MyEmployee(seniority, birthYear, title, employer);
    m_employees.push_back(emp);
    return emp;
}

Employee *MyImplementation::getEmployee(string id) {
    this->loadEmployees();
    for (auto employee : m_employees) {
        if (employee->getID() == id) {
            return employee;
        }
    }
    // If the input id doesn't exist - throw an exception
    throw invalid_argument("The employee id doesn't exist");
}

Plane *MyImplementation::addPlane(int model_number, map<Jobs, int> crewNeeded, map<Classes, int> maxPassengers) {
    // Getting the specific amounts of each class
    int maxFirst = maxPassengers[FIRST_CLASS];
    int maxEconomy = maxPassengers[SECOND_CLASS];
    // Create a new object, add to the list and return it
    Plane *pl = new MyPlane(model_number, crewNeeded, maxFirst, maxEconomy);
    m_planes.push_back(pl);
    m_fileManager.savePlanesDates(m_flights);
    return pl;
}

Plane *MyImplementation::getPlane(string id) {
    this->loadPlanes();
    for (auto &itor : m_planes) {
        if (itor->getID() == id) {
            return itor;
        }
    }
    // If the input id doesn't exist - throw an exception
    throw invalid_argument("Input plane id doesn't exist");
}

Plane *MyImplementation::getPlaneByModel(int reqModelNum) {
    this->loadPlanes();
    for (auto &itor : m_planes) {
        if (itor->getModelNumber() == reqModelNum) {
            return itor;
        }
    }
    return nullptr;
}

bool MyImplementation::isTherePlaneAvailable(int reqModelNum, Date &reqDate) {
    int countPlanesWithModel = 0;

    // Counting how many planes are there in the list of planes with the same model number
    this->loadPlanes();
    for (auto plane : m_planes) {
        if (plane->getModelNumber() == reqModelNum) {
            countPlanesWithModel++;
        }
    }
    // Loading the planes-dates data to see when a plane with the same model is occupied
    this->loadPlanesDates();

    for (auto itor : m_planesDatesData) {
        // Getting the date of the flight
        string currDate = itor.substr(itor.find('|') + 1, 10);
        // Getting the plane model of the flight
        reverse(itor.begin(), itor.end());
        string temp = itor.substr(1);
        string flightModel = temp.substr(0, temp.find('|'));
        reverse(flightModel.begin(), flightModel.end());
        /*
         * If a flight is on the requested date with the requested type of plane - the number of available planes
         * is reduced
         */
        if (reqDate.getDate() == currDate && reqModelNum == stoi(flightModel)) {
            countPlanesWithModel--;
        }
        // If there are no available planes
        if (countPlanesWithModel <= 0) {
            return false;
        }
    }
    return true;
}

const vector<string> MyImplementation::getAvailableEmployees(const Date &flightDate) {
    vector<string> availableIds;

    // Each object in the vector is a string of FLIGHT_ID|DATE|EMPLOYEE_ID
    vector<string> empsAndDates = m_fileManager.loadEmpsDates();
    this->loadEmployees();

    /*
     * Iterating over all the employees and checking for available employees at the given date.
     * Employees who are available are added to a temporary vector that is used to prevent duplicates
     */
    for (auto itorI = empsAndDates.begin(); itorI != empsAndDates.end(); itorI++) {
        string currDate = itorI->substr(itorI->find('|') + 1, 10);
        // If the starting date is the same as the flight date - move to the next register
        if (flightDate.getDate() == currDate) {
            continue;
        }
        string temp = itorI->substr(itorI->find('|') + 1);
        temp = temp.substr(temp.find('|') + 1);
        string startingId = temp.substr(0, temp.length() - 1);

        bool isEmpAvailable = true;
        for (auto itorK = (++itorI); itorK != empsAndDates.end(); itorK++) {
            // First, check if the current id is the same as the starting id; if not then check the next employee
            string currId = itorK->substr(itorK->rfind('|') + 1);
            if (currId != startingId) {
                continue;
            }
            // Next, check if the current date is the same as the flight date; if so then the employee cannot fly
            string currDate = itorK->substr(itorK->find('|'), 10);
            if (currDate == flightDate.getDate()) {
                isEmpAvailable = false;
                break;
            }
        }
        // If the employee is available - check if he isn't already in the 'availables' vector. If not - add him
        if (isEmpAvailable && !this->isEmployeeInVector(availableIds, startingId)) {
            availableIds.push_back(startingId);
        }
    }
    // Finally, add the employees that aren't listed in any flight and are only found in the employees list
    for (auto employee : m_employees) {
        string currId = employee->getID();
        if (!this->isEmployeeInVector(availableIds, currId) && !this->isEmployeeInVector(empsAndDates, currId)) {
            availableIds.push_back(currId);
        }
    }
    return availableIds;
}

bool MyImplementation::isEmployeeInVector(const vector<string> &v, string &id) const {
    for (auto itor = v.begin(); itor != v.end(); itor++) {
        if (*itor == id) {
            return true;
        }
    }
    return false;
}

const map<Jobs, int> MyImplementation::generateCrewMap(const vector<string> &ids) {
    map<Jobs, int> map;
    // Initializing the map
    map[MANAGER] = map[PILOT] = map[NAVIGATOR] = map[FLY_ATTENDANT] = map[OTHER] = 0;

    // Iterating through the vector of IDs, retrieving the title of the employee and updating the respective counter
    for (auto itor = ids.begin(); itor != ids.end(); itor++) {
        Employee *emp(this->getEmployee(*itor));
        map[emp->getTitle()]++;
    }
    return map;
}

bool MyImplementation::isThereEnoughCrewMembers(map<Jobs, int> &currentMap, map<Jobs, int> requiredMap) const {
    // If one of the counters in the map we generated is lower - there aren't enough crew members available
    for (auto itor : currentMap) {
        Jobs job = itor.first;
        if (currentMap[job] < requiredMap[job]) {
            return false;
        }
    }
    return true;
}

vector<Employee *> MyImplementation::createFlightCrew(vector<string> &ids, map<Jobs, int> mapRequired) {
    vector<Employee *> crew;
    // Iterating over the vector of IDs and getting the job of the employee
    for (auto itor = ids.begin(); itor != ids.end(); itor++) {
        Employee *emp(this->getEmployee(*itor));
        Jobs job = emp->getTitle();

        // If more employees of the specific job are needed - add them to the flight crew
        if (mapRequired[job] > 0) {
            crew.push_back(emp);
            mapRequired[job]--;
        }
    }
    return crew;
}

Flight *MyImplementation::addFlight(int modelNumber, Date date, string source, string destination) {
    // Check if the requested plane model exists
    Plane *plane = this->getPlaneByModel(modelNumber);
    if (plane == nullptr) {
        throw invalid_argument("Cannot create flight - requested plane model doesn't exist");
    }
    // Check if there is a plane available at the same date
    if (!this->isTherePlaneAvailable(modelNumber, date)) {
        throw invalid_argument("Cannot create flight - no planes available");
    }
    // Check if there's an available crew
    vector<string> ids = this->getAvailableEmployees(date);
    if (ids.empty()) {
        throw invalid_argument("Cannot create flight - not enough crew members available");
    }
    map<Jobs, int> map = this->generateCrewMap(ids);
    // Compare between the resulted map with an actual required map for the specific plane model
    if (!this->isThereEnoughCrewMembers(map, plane->getCrewNeeded())) {
        throw invalid_argument("Cannot create flight - not enough crew members available");
    }
    // Create a list based on the required amounts in the map
    vector<Employee *> crew = this->createFlightCrew(ids, plane->getCrewNeeded());
    Flight *flight = new MyFlight(modelNumber, crew, date, source, destination);
    m_flights.push_back(flight);
    m_fileManager.savePlanesDates(m_flights);
    m_fileManager.saveEmpsDates(m_flights);
    return flight;
}


Flight *MyImplementation::getFlight(string id) {
    this->loadFlights();
    for (auto &itor : m_flights) {
        if (itor->getID() == id) {
            return itor;
        }
    }
    // If the input id doesn't exist - throw an exception
    throw invalid_argument("The flight id doesn't exist");
}

Customer *MyImplementation::addCustomer(string fullName, int priority) {
    if (priority < 1 || priority > 5) {
        throw invalid_argument("Illegal priority entered");
    }
    // Creating a new customer object with an empty reservations map
    Customer *ct = new MyCustomer(fullName, priority);
    m_customers.push_back(ct);
    return ct;
}

Customer *MyImplementation::getCustomer(string id) {
    this->loadCustomers();
    for (auto &itor : m_customers) {
        if (itor->getID() == id) {
            return itor;
        }
    }
    // If the input id doesn't exist - throw an exception
    throw invalid_argument("The customer id doesn't exist");
}

Reservation *MyImplementation::addResevation(string customerId, string flightId, Classes cls, int maxBaggage) {
    // Getting all the needed information. If one of the IDs don't exist - an exception will be thrown
    Customer *ct = this->getCustomer(customerId);
    Flight *flt = this->getFlight(flightId);
    Plane *plane = this->getPlaneByModel(flt->getModelNumber());

    // Checking if there is an empty seat in the requested class 
    if (!dynamic_cast<MyPlane *>(plane)->isTherePlaceOnPlane(cls)) {
        throw invalid_argument("Requested class is full. Cannot create reservation");
    }
    // Creating a new reservation object and adding it to the customer's list and flight's list of reservations
    Reservation *res = new MyReservation(ct, flt, cls, maxBaggage);
    dynamic_cast<MyCustomer *>(ct)->addReservation(res);
    dynamic_cast<MyFlight *>(flt)->addReservation(res);
    m_reservations.push_back(res);
    return res;
}

Reservation *MyImplementation::getReservation(string id) {
    this->loadReservations();
    for (auto &itor : m_reservations) {
        if (itor->getID() == id) {
            return itor;
        }
    }
    // If the input id doesn't exist - throw an exception
    throw invalid_argument("The reservation id doesn't exist");
}

/**
 * Saving all of the data to the files
 */
void MyImplementation::exit() {
    m_fileManager.saveAll(m_employees, m_planes, m_flights, m_customers, m_reservations);
}

/**
 * Loading the existing employees from their file
 */
void MyImplementation::loadEmployees() {
    if (!m_isEmpsLoaded) {
        // Appending the employees vector with the loaded items
        vector<Employee *> v = m_fileManager.loadEmployees();
        m_employees.insert(m_employees.end(), v.begin(), v.end());
        m_isEmpsLoaded = true;
    }
}

/**
 * Loading the existing planes from their file
 */
void MyImplementation::loadPlanes() {
    if (!m_isPlanesLoaded) {
        vector<Plane *> v = m_fileManager.loadPlanes();
        m_planes.insert(m_planes.end(), v.begin(), v.end());
        m_isPlanesLoaded = true;
    }
}

/**
 * Loading the existing flights from their file
 */
void MyImplementation::loadFlights() {
    if (!m_isFlightsLoaded) {
        vector<Flight *> v = m_fileManager.loadFlights();
        m_flights.insert(m_flights.end(), v.begin(), v.end());
        m_isFlightsLoaded = true;
    }
}

/**
 * Loading the existing customers from their file
 */
void MyImplementation::loadCustomers() {
    if (!m_isCustomersLoaded) {
        vector<Customer *> v = m_fileManager.loadCustomers();
        m_customers.insert(m_customers.end(), v.begin(), v.end());
        m_isCustomersLoaded = true;
    }
}

/**
 * Loading the existing reservations from their file
 */
void MyImplementation::loadReservations() {
    if (!m_isResLoaded) {
        vector<Reservation *> v = m_fileManager.loadReservations(m_customers, m_flights);
        m_reservations.insert(m_reservations.end(), v.begin(), v.end());
        m_isResLoaded = true;
    }
}

void MyImplementation::loadPlanesDates() {
    if (m_planesDatesData.empty() || !m_isPlanesDatesLoaded) {
        vector<string> v = m_fileManager.loadPlanesDates();
        for (auto itor : v) {
            m_planesDatesData.push_back((itor));
        }
        m_isPlanesDatesLoaded = true;
    }
}