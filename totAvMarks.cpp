/*
  Include the header files
*/

// Header file to use the namespace std including the cout, cin, string etc
#include <iostream>

// Header file to use the mysql c++/connector
#include <mysql-cppconn-8/mysql/jdbc.h>

/*
  Function to update the total marks and the average marks in the students table
  params:
    stmt: pointer to the mysql statement object to execute the mysql query
*/
void updateTotAndAvg(sql::Statement *stmt)
{
  try
  {
    // Variable to store the query string
    std::string query;
    
    // Store the query to update the totalMarks in the variable
    query = "update Students set totalMarks=mathsMarks+physicsMarks+sdfMarks;";
    // Execute the query
    stmt->execute(query);

    // Store the query to update the avgMarks in the variable
    query = "update Students set avgMarks=totalMarks/3;";
    // Execute the query
    stmt->execute(query);

  }

  // Catch the mysql exception thrown in the try block
  catch (const sql::SQLException &e)
  {
    // Display the error
    std::cerr << e.what() << '\n';
  }
}
