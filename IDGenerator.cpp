//
// Created by ariel on 28-Nov-18.
//

#include <fstream>
#include "IDGenerator.h"

string IDGenerator::getNewId(string s) {
    fstream stream;
    ifstream instream;
    ofstream outstream;
    string file;
    // Creating a file name object with the given description
    s[0] = (char) tolower(s[0]);
    file = s + "id.txt";

    // First check if the file exists. If not - create the file, write the first ID number and then close
    stream.open(file);
    if (!stream.is_open()) {
        outstream.open(file);
        outstream << 1;
        outstream.close();
    } else {
        stream.close();
    }
    /*
     * Note: Obviously there isn't any point in using all three of stream objects where I can just use the 'fstream'
     * that has the capabilities of the two others. However, it failed to update the number in the file so I had to
     * use all three objects - the 'fstream' object is only used to check if the file exists in the first place. TY
     */
    string id;
    // Opening the file, reading the number and closing
    instream.open(file);
    instream >> id;
    instream.close();
    // Opening the file, updating the number and closing
    outstream.open(file);
    outstream << (stoi(id)+1);
    outstream.close();

    // Adding Specific capital initials before the actual ID number
    string temp = s.substr(0, 2);
    temp[0] = (char) toupper(temp[0]);
    temp[1] = (char) toupper(temp[1]);
    return temp + id;
}