//
// Created by ariel on 28-Nov-18.
//

#include "MyPlane.h"
#include "IDGenerator.h"

MyPlane::MyPlane(int modelNum, map<Jobs, int> &crewNeeded, int maxFirstCls, int maxEconomy) {
    m_ID = IDGenerator().getNewId("Plane");
    m_model = modelNum;
    m_crew = crewNeeded;
    m_maxFirstClass = maxFirstCls;
    m_maxEconomy = maxEconomy;
    m_currentFirstClass = m_currentEconomy = 0;
}

MyPlane::MyPlane(string id, int modelNum, map<Jobs, int> &crewNeeded, int maxFirstCls, int maxEconomy) {
    m_ID = id;
    m_model = modelNum;
    m_crew = crewNeeded;
    m_maxFirstClass = maxFirstCls;
    m_maxEconomy = maxEconomy;
    m_currentFirstClass = m_currentEconomy = 0;
}

MyPlane::~MyPlane() {

}

string MyPlane::getID() {
    return m_ID;
}

int MyPlane::getModelNumber() {
    return m_model;
}

map<Jobs, int> MyPlane::getCrewNeeded() {
    return m_crew;
}

int MyPlane::getMaxFirstClass() {
    return m_maxFirstClass;
}

int MyPlane::getMaxEconomyClass() {
    return m_maxEconomy;
}

bool MyPlane::isTherePlaceOnPlane(Classes requestedClass) {
    // If the requested class is full - the customer cannot be added to the flight
    if (requestedClass == FIRST_CLASS) {
        if (m_currentFirstClass >= m_maxFirstClass) {
            return false;
        }
    } else {
        if (m_currentEconomy >= m_maxEconomy) {
            return false;
        }
    }
    this->updateClassSeats(requestedClass);
    return true;
}

void MyPlane::updateClassSeats(Classes seatedClass) {
    if (seatedClass == FIRST_CLASS) {
        m_currentFirstClass++;
    } else {
        m_currentEconomy++;
    }
}