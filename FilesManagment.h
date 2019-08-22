//
// Created by ariel on 28-Nov-18.
//

#ifndef EX2_FILESMANAGMENT_H
#define EX2_FILESMANAGMENT_H

#include <fstream>
#include <vector>
#include "interface.h"
#include "MyEmployee.h"
#include "MyPlane.h"
#include "MyFlight.h"
#include "MyCustomer.h"
#include "MyReservation.h"

class FilesManagment {
    fstream m_stream;

private:
    template<class T, class func>
    T *getItemById(vector<T *> v, string &requestedId, const func &f);

    Classes getClassFromString(const string &s) const;

    vector<string> getLineData(string &currLine, char separate) const;
    Jobs getJobFromStrNum(const string &s) const;
    map<Jobs, int> getCrewMap(string &details) const;

    bool isAlreadyInFile(fstream &stream, string currentID, string fileName) const;

    vector<string> loadEmpsOrPlanesDates(const string &fileName);
    vector<string> loadEmpsIdFromFlight(string &flightId) const;
    vector<Employee*> addAllEmployees(const vector<string> &ids);

public:
    void saveEmployees(const vector<Employee *> &employees);
    void savePlanes(const vector<Plane *> &planes);
    void saveFlights(const vector<Flight *> &flights);
    void saveCustomers(const vector<Customer *> &customers);
    void saveReservations(const vector<Reservation *> &reservations);

    void savePlanesDates(const vector<Flight *> &flights);
    vector<string> loadPlanesDates();
    void saveEmpsDates(const vector<Flight *> &flights);
    vector<string> loadEmpsDates();

    vector<Employee *> loadEmployees();
    vector<Plane *> loadPlanes();
    vector<Flight *> loadFlights();
    vector<Customer *> loadCustomers();
    vector<Reservation *> loadReservations(vector<Customer *> &customers, vector<Flight *> &flights);

    void saveAll(const vector<Employee *> &employees, const vector<Plane *> &planes, const vector<Flight *> &flights,
                 const vector<Customer *> &customers, const vector<Reservation *> &reservations);
};

/**
 * An object function, used to compare an ID of a comparable item with a given string
 */
struct comparingFunc {
    bool operator()(ID *comparable1, const string &comparable2) const {
        return comparable1->getID() == comparable2;
    }
};

#endif //EX2_FILESMANAGMENT_H
