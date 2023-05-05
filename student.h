// ./clearS.h

// (Preprocessor) If the STUDENT_H header is not defined, so that it is not defined multiple times
#ifndef STUDENT_H

// Define the STUDENT_H header
#define STUDENT_H

// Include header file for mysql c++/connector
#include <mysql-cppconn-8/mysql/jdbc.h>

// Signature for the function defined in the clearS.cpp file
void student(sql::Statement*, std::map<std::string, std::string>&);

// End the preprocessor if statement
#endif