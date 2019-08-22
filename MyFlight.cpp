//
// Created by ariel on 28-Nov-18.
//

#include "MyFlight.h"
#include "IDGenerator.h"

MyFlight::MyFlight(int modelNum, vector<Employee *> flightCrew, Date date,
                   string departure, string destination) : m_date(date) {
    m_ID = IDGenerator().getNewId("Flight");
    m_model = modelNum;
    m_reservations = {};
    m_assignedCrew = flightCrew;
    m_depart = departure;
    m_dest = destination;
}

MyFlight::MyFlight(string id, int modelNum, vector<Employee *> flightCrew, Date date, string departure,
                   string destination) : m_date(date) {
    m_ID = id;
    m_model = modelNum;
    m_reservations = {};
    m_assignedCrew = flightCrew;
    m_depart = departure;
    m_dest = destination;
}

MyFlight::~MyFlight() {
    for (auto &itor : m_reservations) {
        delete itor;
    }
}

string MyFlight::getID() {
    return m_ID;
}

int MyFlight::getModelNumber() {
    return m_model;
}

list<Reservation *> MyFlight::getReservations() {
    list<Reservation *> list;
    for (auto itor : m_reservations) {
        list.push_back(itor);
    }
    return list;
}

list<Employee *> MyFlight::getAssignedCrew() {
    list<Employee *> list;
    for (auto &itor : m_assignedCrew) {
        list.push_back(itor);
    }
    return list;
}

Date MyFlight::getDate() {
    return m_date;
}

string MyFlight::getSource() {
    return m_depart;
}

string MyFlight::getDestination() {
    return m_dest;
}

void MyFlight::addReservation(Reservation *&res) {
    m_reservations.push_back(res);
}