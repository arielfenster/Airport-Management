//
// Created by ariel on 28-Nov-18.
//

#ifndef EX2_MYRESERVATION_H
#define EX2_MYRESERVATION_H

#include "interface.h"

class MyReservation : public Reservation {
    string m_ID;
    Customer *m_customer;
    Flight *m_flight;
    Classes m_class;
    int m_maxBaggage;
public:
    MyReservation(Customer *customer, Flight *flight, Classes requestedClass, int maxBaggage);
    MyReservation(string id, Classes requestedClass, int maxBaggage);
    MyReservation(string id, Customer *customer, Flight *flight, Classes requestedClass, int maxBaggage);

    virtual string getID();
    virtual Customer *getCustomer();
    virtual Flight *getFlight();
    virtual Classes getClass();
    virtual int getMaxBaggage();
    virtual ~MyReservation();
};


#endif //EX2_MYRESERVATION_H
