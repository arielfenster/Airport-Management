//
// Created by ariel on 28-Nov-18.
//

#include <fstream>
#include "interface.h"

Date::Date(string date) {       // format YYYY-MM-DD
    // Checking if the size is right
    if (date.length() != 10) {
        throw invalid_argument("Illegal date format\n");
    }
    // Checking for dash symbols
    if (date.substr(4, 1) != "-" || date.substr(7, 1) != "-") {
        throw invalid_argument("Illegal date format\n");
    }
    // Checking the individual numbers
    string year = date.substr(0, 4);
    string month = date.substr(5, 2);
    string day = date.substr(8);
    if (year < "0" || year > "9999" || month < "01" || month > "12" || day < "01" || day > "31") {
        throw invalid_argument("Illegal date format\n");
    }
    this->date = date;
    }

bool Date::operator<(const Date &d) const {
    return this->date < d.date;
}

bool Date::operator>(const Date &d) const {
    return this->date > d.date;
}

bool Date::operator==(const Date &d) const {
    return this->date == d.date;
}
