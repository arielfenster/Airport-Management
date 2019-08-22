//
// Created by ariel on 28-Nov-18.
//

#include "MyEmployee.h"
#include "IDGenerator.h"

/**
 * Constructor
 * @param seniority
 * @param birthYear
 * @param title
 * @param employer
 */
MyEmployee::MyEmployee(int seniority, int birthYear, Jobs title, Employee *employer) {
    m_ID = IDGenerator().getNewId("Employee");
    m_seniority = seniority;
    m_birthYear = birthYear;
    m_title = title;
    m_employer = employer;
}

/**
 * Constructor. Used in reading the object from a file
 * @param id
 * @param seniority
 * @param birth_year
 * @param title
 * @param employer
 */
MyEmployee::MyEmployee(string id, int seniority, int birth_year, Jobs title, Employee *employer) {
    m_ID = id;
    m_seniority = seniority;
    m_birthYear = birth_year;
    m_title = title;
    m_employer = employer;
}

MyEmployee::~MyEmployee() {

}

string MyEmployee::getID() {
    return m_ID;
}

int MyEmployee::getSeniority() {
    return m_seniority;
}

int MyEmployee::getBirthYear() {
    return m_birthYear;
}

Employee *MyEmployee::getEmployer() {
    return m_employer;
}

Jobs MyEmployee::getTitle() {
    return m_title;
}