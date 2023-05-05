// ./auth.h
// (Preprocessor) If the AUTH_H header is not defined, define it and write the signature for the function to be used
#ifndef AUTH_H

// Defining the AUTH_H header
#define AUTH_H

/* Include the header files */
// Header to use the std namespace
#include <iostream>

// Header to use the mysql c++/connector
#include <mysql-cppconn-8/mysql/jdbc.h>

// signature of the function defined in the auth.cpp file so that it can be used in any other file this file is included in
int authenticate(std::string, std::string, sql::Statement*, char, std::map<std::string, std::string>&);

// Ending the preprocessor if statement
#endif