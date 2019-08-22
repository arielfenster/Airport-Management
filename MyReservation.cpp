//
// Created by ariel on 28-Nov-18.
//

#include "MyReservation.h"
#include "IDGenerator.h"

MyReservation::MyReservation(Customer *customer, Flight *flight, Classes requested_class, int max_baggage) {
    m_ID = IDGenerator().getNewId("Reservation");
    m_customer = customer;
    m_flight = flight;
    m_class = requested_class;
    m_maxBaggage = max_baggage;
}

MyReservation::MyReservation(string id, Classes requested_class, int max_baggage) {
    m_ID = id;
    m_class = requested_class;
    m_maxBaggage = max_baggage;
}

MyReservation::MyReservation(string id, Customer *customer, Flight *flight, Classes requested_class, int max_baggage) {
    m_ID = id;
    m_customer = customer;
    m_flight = flight;
    m_class = requested_class;
    m_maxBaggage = max_baggage;
}

MyReservation::~MyReservation() {

}

string MyReservation::getID() {
    return m_ID;
}

Customer *MyReservation::getCustomer() {
    return m_customer;
}

Flight *MyReservation::getFlight() {
    return m_flight;
}

Classes MyReservation::getClass() {
    return m_class;
}

int MyReservation::getMaxBaggage() {
    return m_maxBaggage;
}