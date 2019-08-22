//
// Created by ariel on 28-Nov-18.
//

#include <algorithm>
#include "FilesManagment.h"
#include "MyImplementation.h"

#define EMPLOYEES_TXT_FILE "employees.txt"
#define PLANES_TXT_FILE "planes.txt"
#define FLIGHTS_TXT_FILE "flights.txt"
#define CUSTOMERS_TXT_FILE "customers.txt"
#define RES_TXT_FILE "reservations.txt"
#define PLANES_DATES_FILE "planes_dates.txt"
#define EMPLOYEES_DATES_FILE "employees_dates.txt"


/**
 * The function receives the vector of existing employees and saves them to a file.
 * @param employees - vector of employees
 */
void FilesManagment::saveEmployees(const vector<Employee *> &employees) {
    if (employees.empty()) { return; }
    string file = EMPLOYEES_TXT_FILE;
    m_stream.open(file);
    if (!m_stream.is_open()) {
        ofstream out;
        out.open(file);
        out << "ID\t|\tSENIORITY\t|\tBIRTH_YEAR\t|\tJOB\t|\tEMPLOYER\n";
        out.close();
    } else {
        m_stream.close();
    }
    // Iterating over the vector and writing the objects' data to the file
    for (auto employee : employees) {
        // Saving the current object only if it hasn't been saved before - preventing duplicates
        if (!this->isAlreadyInFile(m_stream, employee->getID(), EMPLOYEES_TXT_FILE)) {
            m_stream.close();
            m_stream.open(file, ios::app);
            m_stream << employee->getID() << "|" << employee->getSeniority() << "|" << employee->getBirthYear() << "|"
                     << employee->getTitle();
            // If the current employee doesn't have an employer - we don't save anything
            if (employee->getEmployer() != nullptr) {
                m_stream << "|" << employee->getEmployer()->getID();
            }
            m_stream << "|" << endl;
            m_stream.close();
        }
    }
    if (m_stream.is_open()) {
        m_stream.close();
    }
}

/**
 * The function opens the employees file, loads the data, stores it in a vector and returns the vector
 * @return a vector of existing employees
 */
vector<Employee *> FilesManagment::loadEmployees() {
    vector<Employee *> employees;
    string line;
    m_stream.open(EMPLOYEES_TXT_FILE);
    // Ignoring the first line of text
    getline(m_stream, line);

    // Reading each line in the file
    while (getline(m_stream, line)) {
        // Sending the current line to a function to load all the information
        std::vector<string> v = this->getLineData(line, '|');
        // Converting the job string description to an actual Jobs object
        Jobs job = this->getJobFromStrNum(v.at(3));

        // Checking if the current employee has an employer, if so - retrieve him
        Employee *employer;
        // If the size of the vector is 5 - the employee has an employer
        if (v.size() == 5) {
            employer = this->getItemById(employees, v.at(4), comparingFunc());
        } else {
            employer = nullptr;
        }
        // Adding a new employee to the vector
        employees.push_back(new MyEmployee(v.at(0), stoi(v.at(1)), stoi(v.at(2)), job, employer));
    }
    m_stream.close();
    return employees;
}

/**
 * The function receives the vector of existing planes and saves them to a file.
 * @param planes - vector of planes
 */
void FilesManagment::savePlanes(const vector<Plane *> &planes) {
    if (planes.empty()) { return; }
    string file = PLANES_TXT_FILE;
    m_stream.open(file);
    if (!m_stream.is_open()) {
        ofstream out;
        out.open(file);
        out << "ID\t|\tMODEL\t|\tASSIGNED_CREW\t|\tMAX_FIRST_CLASS\t|\tMAX_ECONOMY\n";
        out.close();
    } else {
        m_stream.close();
    }
    for (auto itor = planes.begin(); itor != planes.end(); itor++) {
        // Saving the current object only if it hasn't been saved before - preventing duplicates
        if (!this->isAlreadyInFile(m_stream, (*itor)->getID(), PLANES_TXT_FILE)) {
            m_stream.close();
            m_stream.open(file, ios::app);
            m_stream << (*itor)->getID() << "|" << (*itor)->getModelNumber() << "|";

            // Iterating over each of the jobs
            map<Jobs, int> currMap = (*itor)->getCrewNeeded();
            map<Jobs, int>::iterator jobsItor;
            for (jobsItor = currMap.begin(); jobsItor != currMap.end(); jobsItor++) {
                // Adding the job description and the amount of crew members
                m_stream << jobsItor->first << ":" << jobsItor->second << ",";
            }
            // Continue writing the rest of the plane's data
            m_stream << "|" << (*itor)->getMaxFirstClass() << "|" << (*itor)->getMaxEconomyClass() << "|" << endl;
            m_stream.close();
        }
    }
    if (m_stream.is_open()) {
        m_stream.close();
    }
}

/**
 * The function opens the planes file, loads the data, stores it in a vector and returns the vector
 * @return a vector of existing planes
 */
vector<Plane *> FilesManagment::loadPlanes() {
    vector<Plane *> planes;
    string line;
    m_stream.open(PLANES_TXT_FILE);
    // Ignoring the first line of text
    getline(m_stream, line);

    while (getline(m_stream, line)) {
        // Get the current plane details
        std::vector<string> v = this->getLineData(line, '|');
        // Get the crew details
        map<Jobs, int> map = this->getCrewMap(v.at(2));
        // Add the plane to the vector
        planes.push_back(new MyPlane(v.at(0), stoi(v.at(1)), map, stoi(v.at(3)), stoi(v.at(4))));
    }
    m_stream.close();
    return planes;
}

/**
 * The function receives the vector of existing flights and saves them to a file.
 * @param flights - vector of flights
 */
void FilesManagment::saveFlights(const vector<Flight *> &flights) {
    if (flights.empty()) { return; }
    string file = FLIGHTS_TXT_FILE;
    m_stream.open(file);
    if (!m_stream.is_open()) {
        ofstream out;
        out.open(file);
        out << "ID\t|\tMODEL\t|\tDATE\t|\tDEPARTURE\t|\tDESTINATION\n";
        out.close();
    } else {
        m_stream.close();
    }
    for (auto itor = flights.begin(); itor != flights.end(); itor++) {
        // Saving the current object only if it hasn't been saved before - preventing duplicates
        if (!this->isAlreadyInFile(m_stream, (*itor)->getID(), file)) {
            m_stream.close();
            m_stream.open(file, ios::app);
            // getDate()->getDate(): First is the Date object and second is the string date
            m_stream << (*itor)->getID() << "|" << (*itor)->getModelNumber() << "|" << (*itor)->getDate().getDate()
                     << "|"
                     << (*itor)->getSource() << "|" << (*itor)->getDestination() << "|" << endl;
            m_stream.close();
        }
    }
    if (m_stream.is_open()) {
        m_stream.close();
    }
}

/**
 * The function opens the flights file, loads the data, stores it in a vector and returns the vector
 * @return a vector of existing flights
 */
vector<Flight *> FilesManagment::loadFlights() {
    vector<Flight *> flights;
    vector<Employee *> crew;
    string line;
    m_stream.open(FLIGHTS_TXT_FILE);
    // Ignoring the first line of text
    getline(m_stream, line);

    // Reading each line in the file
    while (getline(m_stream, line)) {
        std::vector<string> v = this->getLineData(line, '|');
        crew = this->addAllEmployees(this->loadEmpsIdFromFlight(v.at(0)));
        flights.push_back(new MyFlight(v.at(0), stoi(v.at(1)), crew, Date(v.at(2)), v.at(3), v.at(4)));
    }
    m_stream.close();
    return flights;
}

/**
 * The function receives the vector of existing customers and saves them to a file.
 * @param customers - vector of customers
 */
void FilesManagment::saveCustomers(const vector<Customer *> &customers) {
    if (customers.empty()) { return; }
    string file = CUSTOMERS_TXT_FILE;
    m_stream.open(file);
    if (!m_stream.is_open()) {
        ofstream out;
        out.open(file);
        out << "ID\t|\tNAME\t|\tPRIORITY\n";
        out.close();
    } else {
        m_stream.close();
    }

    // Iterating over the vector and writing the objects' data to the file
    for (auto itor = customers.begin(); itor != customers.end(); itor++) {
        // Saving the current object only if it hasn't been saved before - preventing duplicates
        if (!this->isAlreadyInFile(m_stream, (*itor)->getID(), file)) {
            m_stream.close();
            m_stream.open(file, ios::app);
            m_stream << (*itor)->getID() << "|" << (*itor)->getFullName() << "|" << (*itor)->getPriority() << "|"
                     << endl;
            m_stream.close();
        }
    }
    if (m_stream.is_open()) {
        m_stream.close();
    }
}

/**
 * The function opens the customers file, loads the data, stores it in a vector and returns the vector
 * @return a vector of existing customers
 */
vector<Customer *> FilesManagment::loadCustomers() {
    vector<Customer *> customers;
    string line;
    m_stream.open(CUSTOMERS_TXT_FILE);
    // Ignoring the first line of text
    getline(m_stream, line);

    // Reading each line in the file
    while (getline(m_stream, line)) {
        std::vector<string> v = this->getLineData(line, '|');
        customers.push_back(new MyCustomer(v.at(0), v.at(1), stoi(v.at(2))));
    }
    m_stream.close();
    return customers;
}

/**
 * The function receives the vector of existing reservations and saves them to a file.
 * @param reservations - vector of reservations
 */
void FilesManagment::saveReservations(const vector<Reservation *> &reservations) {
    if (reservations.empty()) { return; }
    string file = RES_TXT_FILE;
    m_stream.open(file);
    if (!m_stream.is_open()) {
        ofstream out;
        out.open(file);
        out << "ID\t|\tCUSTOMER_ID\t|\tFLIGHT_ID\t|\tSEATED_CLASS\t|\tMAX_BAGGAGE\n";
        out.close();
    } else {
        m_stream.close();
    }
    m_stream.open(file, ios::app);

    // Iterating over the vector and writing the objects' data to the file
    for (auto itor = reservations.begin(); itor != reservations.end(); itor++) {
        // Saving the current object only if it hasn't been saved before - preventing duplicates
        if (!this->isAlreadyInFile(m_stream, (*itor)->getID(), file)) {
            m_stream.close();
            m_stream.open(file, ios::app);
            m_stream << (*itor)->getID() << "|" << (*itor)->getCustomer()->getID() << "|"
                     << (*itor)->getFlight()->getID() << "|" << (*itor)->getClass() << "|" <<
                     (*itor)->getMaxBaggage() << "|" << endl;
            m_stream.close();
        }
    }
    if (m_stream.is_open()) {
        m_stream.close();
    }
}

/**
 * The function opens the reservations file, loads the data, stores it in a vector and returns the vector
 * @param ctvector - vector of existing customers
 * @param flyvector  - vector of existing flights
 * @return a vector of existing reservations
 */
vector<Reservation *> FilesManagment::loadReservations(vector<Customer *> &customers, vector<Flight *> &flights) {
    vector<Reservation *> reservations;
    string line;
    m_stream.open(RES_TXT_FILE);
    // Ignoring the first line of text
    getline(m_stream, line);

    // Reading each line in the file
    while (getline(m_stream, line)) {
        // Getting all the details
        std::vector<string> v = this->getLineData(line, '|');
        Classes cls = this->getClassFromString(v.at(3));
        Customer *customer = this->getItemById(customers, v.at(1), comparingFunc());
        Flight *flight = this->getItemById(flights, v.at(2), comparingFunc());

        // Creating a new reservation object, adding to the vector and updating the customer's and flight's lists
        Reservation *res = new MyReservation(v.at(0), customer, flight, cls, stoi(v.at(4)));
        reservations.push_back(res);
        dynamic_cast<MyCustomer *>(customer)->addReservation(res);
        dynamic_cast<MyFlight *>(flight)->addReservation(res);
    }
    m_stream.close();
    return reservations;
}

/**
 * A generic function.
 * @tparam T - class of the exercise, can be either Employee/Costumer/Flight/Plane/Reservation
 * @tparam func - a comparing function structure, used to compare between strings
 * @param v - vector of items of variable T
 * @param requestedId - the ID we want to match
 * @param f - an object function variable, uses its function to compare between strings without a specific type
 * @return the ID-matching-item if exists, null otherwise
 */
template<class T, class func>
T *FilesManagment::getItemById(vector<T *> v, string &requestedId, const func &f) {
    for (auto itor = v.begin(); itor != v.end(); itor++) {
        if (f(*itor, requestedId)) {
            return *itor;
        }
    }
    return nullptr;
}

/**
 * The function writes to a specific file all the plane models that exist and the dates that the planes are flying in.
 * Since there are multiple planes with the same model number, duplicate models are allowed, as well as duplicate dates.
 * @param flights - vector of existing flights, containing the plane model and flight date
 */
void FilesManagment::savePlanesDates(const vector<Flight *> &flights) {
    if (flights.empty()) { return; }
    string file = PLANES_DATES_FILE;
    m_stream.open(file);
    if (!m_stream.is_open()) {
        ofstream out;
        out.open(file);
        out << "FLIGHT_ID\t|\tFLIGHT_DATE\t|\tPLANE_MODEL_NUMBER\n";
        out.close();
    } else {
        m_stream.close();
    }
    // Iterating through the vector and saving only the items that weren't saved before
    for (auto flight : flights) {
        if (!this->isAlreadyInFile(m_stream, flight->getID(), file)) {
            m_stream.close();
            m_stream.open(file, ios::app);
            m_stream << flight->getID() << "|" << flight->getDate().getDate() << "|" << flight->getModelNumber() << "|"
                     << endl;
            m_stream.close();
        }
    }
    if (m_stream.is_open()) {
        m_stream.close();
    }
}

vector<string> FilesManagment::loadPlanesDates() {
    return this->loadEmpsOrPlanesDates(PLANES_DATES_FILE);
}

/**
 * The function writes to a specific file all the employees IDs and the dates they are working in.
 * Since an employee can work in multiple dates, duplicate IDs are allowed as well as duplicate dates.
 * @param flights - vector of existing flights, containing a vector of employees and flight date
 */
void FilesManagment::saveEmpsDates(const vector<Flight *> &flights) {
    if (flights.empty()) { return; }
    string file = EMPLOYEES_DATES_FILE;
    m_stream.open(file);
    if (!m_stream.is_open()) {
        ofstream out;
        out.open(file);
        out << "FLIGHT_ID\t|\tFLIGHT_DATE\t|\tEMPLOYEE_ID\n";
        out.close();
    } else {
        m_stream.close();
    }
    // Iterating over all the flights
    for (auto flight : flights) {
        if (!this->isAlreadyInFile(m_stream, flight->getID(), file)) {
            m_stream.close();
            m_stream.open(file, ios::app);
            // Iterating over all the employees in the flight
            for (auto employee : flight->getAssignedCrew()) {
                m_stream << flight->getID() << "|" << flight->getDate().getDate() << "|" << employee->getID() << "|"
                         << endl;
            }
            m_stream.close();
        }
    }
    if (m_stream.is_open()) {
        m_stream.close();
    }
}

vector<string> FilesManagment::loadEmpsDates() {
    return this->loadEmpsOrPlanesDates(EMPLOYEES_DATES_FILE);
}

vector<string> FilesManagment::loadEmpsOrPlanesDates(const string &fileName) {
    vector<string> vec;
    string line;
    m_stream.open(fileName);
    // Ignoring the first line of text
    getline(m_stream, line);

    // Reading each line in the file
    while (getline(m_stream, line)) {
        // Adding a string of FLIGHT_ID|FLIGHT_DATE|EMPLOYEE_ID/FLIGHT_MODEL
        vec.push_back(line);
    }
    m_stream.close();
    return vec;
}

vector<string> FilesManagment::loadEmpsIdFromFlight(string &flightId) const {
    vector<string> ids;
    string line;
    ifstream instream(EMPLOYEES_DATES_FILE);
    // Ignoring the first line of text
    getline(instream, line);

    while (getline(instream, line)) {
        string currId = line.substr(0, line.find('|'));

        // Adding only the employees on the requested flight
        if (currId == flightId) {
            // Getting only the employee ID from the line - substringing until we reach the specific area of text
            string temp = line.substr(line.find('|') + 1);
            temp = temp.substr(temp.find('|') + 1);
            temp = temp.substr(0, temp.length() - 1);
            ids.push_back(temp);
        }
    }
    instream.close();
    return ids;
}

vector<Employee *> FilesManagment::addAllEmployees(const vector<string> &ids) {
    vector<Employee *> employees;
    MyImplementation imp;
    for (auto &itor : ids) {
        Employee *temp = imp.getEmployee(itor);
        Employee *e = new MyEmployee(temp->getID(), temp->getSeniority(), temp->getBirthYear(), temp->getTitle(),
                                     temp->getEmployer());
        employees.push_back(e);
    }
    return employees;
}

bool FilesManagment::isAlreadyInFile(fstream &stream, string currentID, string fileName) const {
    if (!stream.is_open()) {
        stream.open(fileName);
    }
    string line;
    while (getline(stream, line)) {
        if (currentID == line.substr(0, line.find('|'))) {
            return true;
        }
    }
    return false;
}

/**
* Receives a string description of a job and returns the corresponding Job object
* @param s - string of a job
* @return corresponding Job object
*/
Jobs FilesManagment::getJobFromStrNum(const string &s) const {
    Jobs j = (Jobs) (stoi(s));
    return j;
}

Classes FilesManagment::getClassFromString(const string &s) const {
    if (s == "FIRST_CLASS") {
        return FIRST_CLASS;
    } else {
        return SECOND_CLASS;
    }
}

vector<string> FilesManagment::getLineData(string &currLine, char separate) const {
    vector<string> v;
    // Inserting all the data into a vector
    while (currLine.length() != 0) {
        unsigned endIndex = currLine.find(separate);
        string temp = currLine.substr(0, endIndex);
        v.push_back(temp);
        // Shortening the line string after every time to get the next value
        currLine = currLine.substr(endIndex + 1);
    }
    return v;
}

map<Jobs, int> FilesManagment::getCrewMap(string &details) const {
    map<Jobs, int> map;
    vector<string> v = this->getLineData(details, ',');
    for (unsigned int i = 0; i < v.size(); i++) {
        // Getting the job description
        Jobs j = this->getJobFromStrNum(v.at(i).substr(0, 1));
        // Getting the amount of members with that job
        int amount = stoi(v.at(i).substr(2));
        map[j] = amount;
    }
    return map;
};

/**
 * Saving all of the data to their respective files
 * @param employees - vector of employees
 * @param planes - vector of planes
 * @param flights  - vector of flights
 * @param customers  - vector of customers
 * @param reservations - vector of reservations
 */
void FilesManagment::saveAll(const vector<Employee *> &employees, const vector<Plane *> &planes,
                             const vector<Flight *> &flights, const vector<Customer *> &customers,
                             const vector<Reservation *> &reservations) {
    this->saveEmployees(employees);
    this->savePlanes(planes);
    this->saveFlights(flights);
    this->saveCustomers(customers);
    this->saveReservations(reservations);
    this->savePlanesDates(flights);
    this->saveEmpsDates(flights);
}
