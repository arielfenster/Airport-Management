//
// Created by ariel on 28-Nov-18.
//

#ifndef EX2_MYCUSTOMER_H
#define EX2_MYCUSTOMER_H

#include <vector>
#include "interface.h"

class MyCustomer : public Customer {
    string m_ID;
    string m_name;
    int m_priority;
    vector<Reservation *> m_reservations;
public:
    MyCustomer(string fullName, int priority);
    MyCustomer(string id, string fullName, int priority);

    virtual string getID();
    virtual string getFullName();
    virtual int getPriority();
    virtual list<Reservation *> getReservations();
    void addReservation(Reservation *&res);
    virtual ~MyCustomer();
};


#endif //EX2_MYCUSTOMER_H
