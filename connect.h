// ./connect.h

// (Preprocessor) If the CONNECT_H header is not defined, so that it is not defined multiple times
#ifndef CONNECT_H

// Define the CONNECT_H header
#define CONNECT_H

/* Include the header file */
// Header to use the mysql c++/connector
#include <mysql-cppconn-8/mysql/jdbc.h>

// Signature of the function defined in the connect.h file so that it can be used in any other file where this header is included
sql::Statement* connect();

// Ending the preprocessor if statement
#endif