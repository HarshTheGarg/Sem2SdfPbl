//  ./auth.cpp
/* 
  Include the header files to be used
*/

// Header file to include the std namespace, including cin, cout, string etc
#include <iostream>

// Header file to use stringstream
#include <sstream>

// Header to use the mysql c++/connector
#include <mysql-cppconn-8/mysql/jdbc.h>

/*
  Authenticate the user based on the information entered
  params:
    userId: The ID entered by the user
    pass: The password entered by the user
    stmt: The sql c++/connector statement to execute the sql queries
    userType: char that stores the type of the user (s for student and t for teacher)
    user: pointer to map to store the user details

    return: integer 1 for success, 0 for failure
*/
int authenticate(std::string userId, std::string pass, sql::Statement *stmt, char userType, std::map<std::string, std::string> &user)
{
  // try the commands
  try
  {
    // String to store the name of the table based on the userType
    std::string table;

    // If user is a student
    if(userType == 'S' || userType == 's')
    {
      table = "Students";
    }

    // If user is a teacher
    else if ( userType == 'T' || userType == 't')
    {
      table = "Teacher";
    }

    // String stream to create the mysql query
    std::stringstream ss;

    // Creating the mysql query using the function input parameters
    ss << "SELECT id, firstName as fn, lastName as ln from " << table << " where id='" << userId << "' and password='" << pass << "'";
    
    // Executing the query and storing the result in the res object variable of sql::ResultSet class
    sql::ResultSet *res(stmt->executeQuery(ss.str()));

    // Run only if the query executed successfully and returned only one row
    if ( res != NULL && res->rowsCount() == 1)
    {
      // Moving to the next result
      res->next();

      // Store the first name to the user map with key - fn
      user["fn"] = res->getString("fn");

      // Store the last name to the user map with key - ln
      user["ln"] = res->getString("ln");

      // Store the type of student (Student/Teacher) to the user man with key - type
      user["type"] = userType == 'S' || userType == 's' ? "Student" : "Teacher";

      // Store the user's id to the user map with key - id
      user["id"] = res->getString("id");

      // return 1 => Success
      return 1;
    }
    else
    {
      // return 0 => No result was returned => Some error
      return 0;
    }
  }

  // Catch a mysql exception
  catch(sql::SQLException &e)
  {
    // Print the error that occurred to the console
    std::cerr << e.what() << '\n';

    // return 0 => Some error
    return 0;
  }
}