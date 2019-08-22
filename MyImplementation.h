//
// Created by ariel on 28-Nov-18.
//

#ifndef EX2_MYIMPLEMENTATION_H
#define EX2_MYIMPLEMENTATION_H

#include "interface.h"
#include "FilesManagment.h"

class MyImplementation : public Ex2 {
    FilesManagment m_fileManager;
    vector<Employee *> m_employees;
    vector<Plane *> m_planes;
    vector<Flight *> m_flights;
    vector<Customer *> m_customers;
    vector<Reservation *> m_reservations;
    vector<string> m_planesDatesData;

    bool m_isEmpsLoaded;
    bool m_isPlanesLoaded;
    bool m_isFlightsLoaded;
    bool m_isCustomersLoaded;
    bool m_isResLoaded;
    bool m_isPlanesDatesLoaded;

    Plane* getPlaneByModel(int requestedModelNum);
    bool isTherePlaneAvailable(int requestedModelNum, Date &requestedDate);

    const vector<string> getAvailableEmployees(const Date &flightDate);
    bool isEmployeeInVector(const vector<string> &v, string &id) const;

    const map<Jobs,int> generateCrewMap(const vector<string> &ids);
    bool isThereEnoughCrewMembers(map<Jobs,int> &present, map<Jobs,int> required) const;
    vector<Employee*> createFlightCrew(vector<string> &ids, map<Jobs, int> mapRequired);

public:
    MyImplementation();

    virtual Employee *addEmployee(int seniority, int birthYear, string employerId, Jobs title);
    virtual Employee *getEmployee(string id);
    virtual Plane *addPlane(int modelNumber, map<Jobs, int> crew_needed, map<Classes, int> maxPassengers);
    virtual Plane *getPlane(string id);
    virtual Flight *addFlight(int modelNumber, Date date, string source, string destination);
    virtual Flight *getFlight(string id);
    virtual Customer *addCustomer(string fullName, int priority);
    virtual Customer *getCustomer(string id);
    virtual Reservation *addResevation(string customerId, string flightId, Classes cls, int maxBaggage);
    virtual Reservation *getReservation(string id);
    virtual void exit();

    virtual ~MyImplementation();

    void loadEmployees();
    void loadPlanes();
    void loadFlights();
    void loadCustomers();
    void loadReservations();
    void loadPlanesDates();
};


#endif //EX2_MYIMPLEMENTATION_H
