//
// Created by ariel on 28-Nov-18.
//

#ifndef EX2_MYFLIGHT_H
#define EX2_MYFLIGHT_H

#include <vector>
#include "interface.h"

class MyFlight : public Flight {
    string m_ID;
    int m_model;
    vector<Reservation *> m_reservations;
    vector<Employee *> m_assignedCrew;
    Date m_date;
    string m_depart;
    string m_dest;
public:
    MyFlight(int modelNum, vector<Employee *> flightCrew, Date date, string departure, string destination);
    MyFlight(string id, int modelNum, vector<Employee *> flightCrew, Date date, string departure, string destination);

    virtual string getID();
    virtual int getModelNumber();
    virtual list<Reservation *> getReservations();
    virtual list<Employee *> getAssignedCrew();
    virtual Date getDate();
    virtual string getSource();
    virtual string getDestination();
    void addReservation(Reservation* &res);
    virtual ~MyFlight();
};

#endif //EX2_MYFLIGHT_H
