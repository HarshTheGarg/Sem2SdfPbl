// ./main.cpp
/*
  Including the head files 
*/
// Header for console in/out stream, string, etc.
#include <iostream>

// Header file for mysql c++/connector
#include <mysql-cppconn-8/mysql/jdbc.h>

// To use the system command
#include <stdlib.h>

/* Include the header files for the modules */

// File to establish the connection to the database
#include "connect.h"

// File with function to authenticate the user
#include "auth.h"

// File with function to clear the console screen
#include "clearS.h"

// File containing the functionality for the teacher
#include "teacher.h"

// File containing the functionality for the students
#include "student.h"


/* 
  Main function that is called when the executable is run
*/
int main()
{
  try
  {
    // Clear the screen when the program is run
    clear();

    /* Connecting to the database using the connect function defined in 
    the connect.cpp file which returns the sql::Statement */
    sql::Statement *stmt = connect();
    
    // If nothing is returned/connection failed exit the program
    if (stmt == NULL)
    {
      // Return to end the execution of the program
      return 0;
    }

    // Variable to store the access type of user (s/S for Student of t/T for Teacher)
    char usrType;

    // Ask the user to enter their access type
    std::cout << "Enter access type: Student (S) or Teacher (T): ";

    // Accepting the user's response
    std::cin >> usrType;

    // Check if wrong input entered by the user
    if (usrType != 'S' && usrType != 's' && usrType != 't' && usrType != 'T')
    {
      // If invalid access type entered, throw the appropriate error message
      throw "Invalid Access Type!";
    }

    // Creating string variables to store the user's id and password
    std::string uid, pass;

    // Asking the user to enter their ID
    std::cout << "Enter ID: ";

    // Accept the user's response
    std::cin >> uid;

    // Ask the user for their password
    std::cout << "Enter Password: ";

    // Accept the user's response
    std::cin >> pass;

    // Create a map that will store the user's details which will be transferred to other files 
    std::map<std::string, std::string> userDet;

    // Authenticating the user using the auth.cpp file which return 1 for success and 0 for failure
    int authd = authenticate(uid, pass, stmt, usrType, userDet);

    // Check if authentication was a failure
    if (authd == 0)
    {
      // Throwing the appropriate error
      throw "User Not Found";
    }


    // Clearing the screen
    clear();

    // If the user is a teacher call the appropriate function
    if (userDet["type"] == "Teacher")
    {
      // Calling the teacher function in the teacher.cpp file
      teacher(stmt, userDet);
    }

    // If the user is Student
    else if (userDet["type"] == "Student")
    {
      // Call the student function in the student.cpp file
      student(stmt, userDet);
    }
  }

  /* Catching the errors thrown in the try block */ 
  // Catching the string errors thrown
  catch (const char *s)
  {
    // Displaying the error to the user
    std::cerr << "Error: " << s << std::endl;
  }

  // Catching default error
  catch (...)
  {
    // Display error
    std::cerr << "Some error occurred..." << '\n';
  }

  // Show the program abort message
  std::cout << std::endl
            << std::endl
            << "Aborting.... See you later!" << std::endl;
}