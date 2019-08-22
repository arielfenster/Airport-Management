//
// Created by ariel on 28-Nov-18.
//

#include "MyCustomer.h"
#include "IDGenerator.h"

MyCustomer::MyCustomer(string fullName, int priority) {
    m_ID = IDGenerator().getNewId("Customer");
    m_name = fullName;
    m_priority = priority;
    m_reservations = {};
}

MyCustomer::MyCustomer(string id, string fullName, int priority) {
    m_ID = id;
    m_name = fullName;
    m_priority = priority;
}

MyCustomer::~MyCustomer() {
    for (auto &itor : m_reservations) {
        delete itor;
    }
}

string MyCustomer::getID() {
    return m_ID;
}

string MyCustomer::getFullName() {
    return m_name;
}

int MyCustomer::getPriority() {
    return m_priority;
}

list<Reservation *> MyCustomer::getReservations() {
    list<Reservation *> list;
    for (auto itor : m_reservations) {
        list.push_back(itor);
    }
    return list;
}

void MyCustomer::addReservation(Reservation *&res) {
    m_reservations.push_back(res);
}