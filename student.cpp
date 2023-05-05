// ./main.cpp
/*
  Including the head files
*/
// Header for console in/out stream, string, etc.
#include <iostream>

// Header file for mysql c++/connector
#include <mysql-cppconn-8/mysql/jdbc.h>

// Header file to use stringstream
#include <sstream>

// Include the header file for the file with function to clear the console screen
#include "clearS.h"

/*
  Function to run when the user is a student
  params:
    stmt: mysql object pointer to execute the queries
    stuDet: map that store the users details (name, user type, user id)
*/
void student(sql::Statement *stmt, std::map<std::string, std::string> &stuDet)
{
  // Display the welcome text
  std::cout << "==============================" << std::endl;
  std::cout << "Welcome, " << stuDet["fn"] << " "
            << stuDet["ln"] << " (" << stuDet["type"]
            << ")" << std::endl;

  // Loop the menu till the user chooses to exit the program
  while (true)
  {

    // Display the options
    std::cout << "==============================" << std::endl;
    std::cout << "Choose one of the following: " << std::endl
              << "1. Change Name" << std::endl
              << "2. Change Password" << std::endl
              << "3. Show Marks" << std::endl
              << "4. Leave database" << std::endl
              << "5. Exit" << std::endl
              << ": ";

    // Variable to store the user's response
    int opt;

    // Accept the value entered by the user
    std::cin >> opt;

    // Run a switch to check the user's input
    switch (opt)
    {
      // User chooses option 1 -> Change name
    case 1:
    {

      // Clear the screen
      clear();

      // Heading for changing the name
      std::cout << "==========CHANGE NAME==========" << std::endl;

      // Asking the user for the new username
      std::cout << "Enter new name (firstName lastName): ";

      // Creating a map to store the new user name
      std::map<std::string, std::string> newName;

      // Accept the value from the user and store it in the map
      std::cin >> newName["fn"] >> newName["ln"];

      // Confirm to change the user name
      std::cout << "Change name to " << newName["fn"] << " " << newName["ln"] << "? (Y/N): ";

      // Store the user's response
      char opt;

      // Accept the user's response
      std::cin >> opt;

      // If the user doesn't want to change the name
      if (opt == 'n' || opt == 'N')
      {
        // Go to the next iteration of the loop
        continue;
      }

      // If the user want to change the name
      else if (opt == 'y' || opt == 'Y')
      {
        try
        {
          // Stringstream to store the query
          std::stringstream ss;

          // Storing the query
          ss << "Update Students set firstName='" << newName["fn"] << "', lastName='" << newName["ln"] << "' where id='" << stuDet["id"] << "'";

          // Execute the query to update the first name and the last name
          stmt->execute(ss.str());

          // Update the first name and last name in the user details map that was passed as the argument
          stuDet["fn"] = newName["fn"];
          stuDet["ln"] = newName["ln"];

          // Everything went ok, display the success message
          std::cout << "Done!" << std::endl
                    << std::endl;
        }

        // Catch the mysql exceptions thrown in the try block and handle them
        catch (sql::SQLException &e)
        {

          // Display the Error
          std::cerr << "Error Occurred: " << e.what() << std::endl;

          // To exit the program
          return;
        }
      }
      break;
    }

    // User choose option 2 -> Change password
    case 2:
    {

      // Clear the output console
      clear();

      // Display the change password header
      std::cout << "==========CHANGE PASSWORD==========" << std::endl;

      // Ask the user for new password
      std::cout << "Enter new password: ";

      // string to store the new password
      std::string newPass;

      // Accepting the new password
      std::cin >> newPass;

      // Confirmation to change the password
      std::cout << "Change Password? (Y/N): ";

      // Variable to store the user's choice
      char opt;

      // Accept the user's choice
      std::cin >> opt;

      // If the user does not want to change the password
      if (opt == 'n' || opt == 'N')
      {
        // Continue to the next iteration of the loop
        continue;
      }

      // If the user wants to change the password
      else if (opt == 'y' || opt == 'Y')
      {
        try
        {

          // stringstream to make the query
          std::stringstream ss;

          // Make the query
          ss << "Update Students set password='" << newPass << "' where id='" << stuDet["id"] << "'";

          // Execute the query
          stmt->execute(ss.str());

          // Display the success output
          std::cout << "Done!" << std::endl
                    << std::endl;
        }

        // Catch the mysql error which may occur during the execution of the mysql statement
        catch (sql::SQLException &e)
        {
          // Display the error
          std::cerr << "Error Occurred: " << e.what() << std::endl;

          // To exit the program if error occurred
          return;
        }
      }
      break;
    }

    // User chooses option 3 -> Display all the marks
    case 3:
    {
      // Clear the output console
      clear();

      // stringstream to make the query
      std::stringstream ss;

      // make the query to return the marks of all the subjects, total, average and the tid of the teacher who last updated the marks
      ss << "Select mathsMarks as mm, physicsMarks as pm, ";
      ss << "sdfMarks as sm, totalMarks as tots, avgMarks as avg, ";
      ss << "tId from Students where id='" << stuDet["id"] << "'";

      // Execute the query and store the result in the resultSet object
      sql::ResultSet *res(stmt->executeQuery(ss.str()));

      // Iterating to the next result
      res->next();

      /* Display the individual subject marks */
      std::cout << "Maths Marks: " << res->getDouble("mm") << std::endl;
      std::cout << "Physics Marks: " << res->getDouble("pm") << std::endl;
      std::cout << "SDF Marks: " << res->getDouble("sm") << std::endl;
      std::cout << std::endl;

      /* Display the total and the average marks */
      std::cout << "Total Marks: " << res->getDouble("tots") << std::endl;
      std::cout << "Average Marks: " << res->getDouble("avg") << std::endl;
      std::cout << std::endl;

      // string stream to make the query to get the teacher name
      std::stringstream s2;

      // Making the query string
      s2 << "Select firstName as fn, lastName as ln ";
      s2 << "from Teacher where id='" << res->getString("tId") << "'";

      // Execute the query and store the result in a new resultSet object
      sql::ResultSet *res2(stmt->executeQuery(s2.str()));

      // No result is returned if the teacher left the database
      if (res2->rowsCount() < 1)
      {
        // Display the appropriate message
        std::cout << "The teacher left" << std::endl;
      }
      // if teacher exists
      else
      {
        // Iterating to the first result
        res2->next();

        // Display the name of the teacher who last updated the marks
        std::cout << "Last updated by: " << res2->getString("fn") << " " << res2->getString("ln");
      }

      std::cout << std::endl
                << std::endl
                << std::endl;
      break;
    }

    // User chooses option 4 -> Delete the account
    case 4:
    {
      // Clear the output console
      clear();

      // Confirm to delete the account
      std::cout << "Are you sure you want to delete you account? (Y/N): ";

      // Variable to store the user's option
      char option;

      // Accept the user's option
      std::cin >> option;

      // If user does not want to change the password
      if (option == 'n' || option == 'N')
        // Go to the next iteration of the loop
        continue;

      // If the user wants to delete the account
      else if (option == 'y' || option == 'Y')
      {
        // stringstream to make the query string
        std::stringstream ss;

        // Make the query string
        ss << "delete from Students where id='" << stuDet["id"] << "'";

        // Execute the delete query
        stmt->execute(ss.str());

        // Display the goodbye text
        std::cout << "Done! Good Bye!";

        // Exit the program as the user now no longer exists
        return;
      }
    }

    // User chooses option 5 -> Exit the program
    case 5:
      // Exit the program
      return;

    // User choose some incorrect option
    default:
      // Display the error message
      std::cout << "Wrong option! Try again: " << std::endl;
      break;
    }
  }
}