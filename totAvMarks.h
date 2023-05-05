// ./toAvMarks.h
// (Preprocessor) If the header is not defined, define it and write the signature of the function to be used
#ifndef TOTAVMARKS_H

// Define the header
#define TOTAVMARKS_H

// Header file to use the mysql c++/connector
#include <mysql-cppconn-8/mysql/jdbc.h>

// Signature of the function to be used
void updateTotAndAvg(sql::Statement*);

// End the preprocessor if statement
#endif