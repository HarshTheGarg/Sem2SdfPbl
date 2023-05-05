// ./connect.cpp
/*
  Including the head files 
*/
// Header for console in/out stream, string, etc.
#include <iostream>

// Header file for mysql c++/connector
#include <mysql-cppconn-8/mysql/jdbc.h>

// Defining the macros 
// these will be replaced by the pre-processor before the code is compiled
// These contain the values to be used to connect to the database

// Location of the host
#define HOST "localhost::3306"

// mysql user Name
#define USER "root"

// mysql user password
#define PASSWORD "password1234"

// mysql database to be used
#define SCHEMA "project"

/*
  Function to connect to the data base
    return: pointer to sql statement object, 
      which can be used to execute mysql queries by other functions
*/
sql::Statement* connect()
{
  try
  {

    // driver to connect to the mysql database
    sql::Driver *driver(get_driver_instance());

    // use the driver to connect to the database, and store the connection result in the conn variable
    sql::Connection *conn(driver->connect(HOST, USER, PASSWORD));

    // If the connection was successful
    if ( conn ) 
    {
      // Use the required database
      conn->setSchema(SCHEMA);

      // Create a mysql statement will be used to execute mysql queries
      sql::Statement *stmt(conn->createStatement());

      // return the mysql statement
      return stmt;
    }

    // If the connection failed without throwing error ( just in case )
    else 
    {
      return NULL;
    }
  }

  // Catching the mysql exceptions thrown by the function called inside the try block
  catch(const sql::SQLException &e)
  {
    // Display the error
    std::cerr << e.what() << '\n';

    // return NULL so that the main function can handle the error 
    return NULL;
  }
}
