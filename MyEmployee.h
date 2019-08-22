//
// Created by ariel on 28-Nov-18.
//

#ifndef EX2_MYEMPLOYEE_H
#define EX2_MYEMPLOYEE_H

#include "interface.h"

class MyEmployee : public Employee {
    string m_ID;
    int m_seniority;
    int m_birthYear;
    Jobs m_title;
    Employee *m_employer;
public:
    MyEmployee(int seniority, int birthYear, Jobs title, Employee *employer);
    MyEmployee(string id, int seniority, int birthYear, Jobs title, Employee *employer);

    virtual string getID();
    virtual int getSeniority();
    virtual int getBirthYear();
    virtual Jobs getTitle();
    virtual Employee *getEmployer();
    virtual ~MyEmployee();
};


#endif //EX2_MYEMPLOYEE_H
