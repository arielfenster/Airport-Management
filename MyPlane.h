//
// Created by ariel on 28-Nov-18.
//

#ifndef EX2_MYPLANE_H
#define EX2_MYPLANE_H

#include "interface.h"

class MyPlane : public Plane {
    string m_ID;
    int m_model;
    map<Jobs, int> m_crew;
    int m_maxFirstClass;
    int m_maxEconomy;
    int m_currentFirstClass;
    int m_currentEconomy;

    void updateClassSeats(Classes seatedClass);
public:
    MyPlane(int modelNum, map<Jobs, int> &crewNeeded, int maxFirstCls, int maxEconomy);
    MyPlane(string id, int modelNum, map<Jobs,int> &crewNeeded, int maxFirstCls, int maxEconomy);

    virtual string getID();
    virtual int getModelNumber();
    virtual map<Jobs, int> getCrewNeeded();
    virtual int getMaxFirstClass();
    virtual int getMaxEconomyClass();
    bool isTherePlaceOnPlane(Classes requestedClass);
    virtual ~MyPlane();
};


#endif //EX2_MYPLANE_H
