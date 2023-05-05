// ./teacher.h
// (Preprocessor) If the TEACHER_H header is not defined, define it and write the signature for the function to be used
#ifndef TEACHER_H

// Define the TEACHER_H header
#define TEACHER_H

// Header file to use the mysql c++/connector
#include <mysql-cppconn-8/mysql/jdbc.h>

// Signature of the function to be used
void teacher(sql::Statement *, std::map<std::string, std::string> &);

// End the preprocessor if statement
#endif