// ./teacher.cpp
/*
  Including the head files
*/
// Header for console in/out stream, string, etc.
#include <iostream>

// Header file for mysql c++/connector
#include <mysql-cppconn-8/mysql/jdbc.h>

// To use the stringstream
#include <sstream>

/* Include the header files for the modules */

// File to with function to recalculate the total and average marks for students after updating the marks
#include "totAvMarks.h"

// File with function to clear the console screen
#include "clearS.h"

/*
  Function to be called when the teacher logs in
  params:
    stmt: pointer to the mysql statement object which is use to execute the queries
    teacherDet: map that stores the teacher's details
*/
void teacher(sql::Statement *stmt, std::map<std::string, std::string> &teacherDet)
{

  // Display the welcome line
  std::cout << "==============================" << std::endl;
  std::cout << "Welcome, " << teacherDet["fn"] << " " << teacherDet["ln"] << " (" << teacherDet["type"] << ")" << std::endl;

  // Loop the menu till the user chooses to exit the program
  while (true)
  {
    // Display the options
    std::cout << "==============================" << std::endl;
    std::cout << "Choose one of the following: " << std::endl
              << "1. Change Name" << std::endl
              << "2. Change Password" << std::endl
              << "3. Enter Marks" << std::endl
              << "4. Add Student" << std::endl
              << "5. Add Teacher" << std::endl
              << "6. Display all students" << std::endl
              << "7. Leave database" << std::endl
              << "8. Exit" << std::endl
              << ": ";

    // Variable to store the user's response
    int opt;

    // Accept the user's response
    std::cin >> opt;

    // Run a switch statement to check the user's input
    switch (opt)
    {

    // User chooses option 1 -> Change name
    case 1:
    {

      // Clear the screen
      clear();

      // Heading for the name change
      std::cout << "==========CHANGE NAME==========" << std::endl;

      // Ask the user for the new username
      std::cout << "Enter new name (firstName lastName): ";

      // Create a map to store the new user
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
          // stringstream to store the query
          std::stringstream ss;

          // Store the query in the stringstream
          ss << "Update Teacher set firstName='" << newName["fn"] << "', lastName='" << newName["ln"] << "' where id='" << teacherDet["id"] << "'";

          // Execute the query to update the student's name
          stmt->execute(ss.str());

          // Update the firstname and the last name in the user details map that was passed as the argument
          teacherDet["fn"] = newName["fn"];
          teacherDet["ln"] = newName["ln"];

          // Everything went OK, display the success message
          std::cout << "Done!" << std::endl
                    << std::endl;
        }

        // Catch the mysql exceptions thrown in the try block
        catch (sql::SQLException &e)
        {

          // Display the error
          std::cerr << "Error Occurred: " << e.what() << std::endl;

          // To exit the program
          return;
        }
      }
      break;
    }

    // User chooses option 2 -> Change password
    case 2:
    {
      // Clear the output console
      clear();

      // Display the change password header
      std::cout << "==========CHANGE PASSWORD==========" << std::endl;

      // Ask the user for the new password
      std::cout << "Enter new password: ";

      // String to store the new password
      std::string newPass;

      // Accept the new password from the user
      std::cin >> newPass;

      // Confirmation to change the password
      std::cout << "Change Password? (Y/N): ";

      // Variable to store the user's choice
      char opt;

      // Accept the user's response
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
          ss << "Update Teacher set password='" << newPass << "' where id='" << teacherDet["id"] << "'";

          // Execute the query
          stmt->execute(ss.str());

          // Display the success output
          std::cout << "Done!" << std::endl
                    << std::endl;
        }

        // Catch the mysql error which may occur during the execution of the mysql statements
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

    // User chooses option 3 -> Enter student's marks
    case 3:
    {
      // Clear the output console
      clear();

      // Ask the user for the subject for which the marks are to be entered
      std::cout << "Enter subject (maths/physics/sdf): ";

      // Create a string variable to store the subject
      std::string subj;

      // Accept the user's response
      std::cin >> subj;

      // Loop to keep entering the students marks
      while (true)
      {
        // Ask fot the student's id. If q is entered exit the marks loop
        std::cout << "Enter student id ('q' to exit): ";

        // String to store the student id
        std::string sid;

        // Accept the user's response
        std::cin >> sid;

        // If the user does not want to enter more marks
        if (sid == "q")
        {
          // Break the marks loop
          break;
        }

        // Ask the teacher for the marks of the student
        std::cout << "Enter " << subj << " Marks: ";

        // Variable to store the marks
        float marks;

        // Accept the marks from the teacher
        std::cin >> marks;

        // Stringstream to make the query
        std::stringstream ss;

        // Make the query
        ss << "UPDATE Students set " << subj << "Marks=" << marks << ", tid='" << teacherDet["id"] << "' where id='" << sid << "'";

        // Execute the update marks query
        stmt->execute(ss.str());

        std::cout << std::endl;
      }

      // Update all the student's total and average marks according to the new values entered
      updateTotAndAvg(stmt);

      // Clear the output console
      clear();
      break;
    }

    // User chooses option 4 -> Add students to the database
    case 4:
    {
      // Clear the output console screen
      clear();

      // Display header for Add students
      std::cout << "==========ADD STUDENTS==========" << std::endl;

      // Map to store the data of the new student
      std::map<std::string, std::string> newStudent;

      // Asking the user for the student's name
      std::cout << "Enter student name (firstName lastName): ";
      // Accept the user's response
      std::cin >> newStudent["fn"] >> newStudent["ln"];

      // Ask the user for the student id
      std::cout << "Enter student id: ";
      // Accept the user's response
      std::cin >> newStudent["sid"];

      try
      {
        // Stringstream to make the query string
        std::stringstream ss;

        // Make the query string
        ss << "INSERT INTO Students(id, lastName, firstName, tId) values('";
        ss << newStudent["sid"] << "', '" << newStudent["ln"] << "', '";
        ss << newStudent["fn"] << "', '" << teacherDet["id"] << "')";

        // Execute the insert statement
        stmt->execute(ss.str());

        // Display the success message
        std::cout << "Done!" << std::endl;
      }

      // Catch the sql exceptions thrown in the try block
      catch (sql::SQLException &e)
      {
        // Display the error message
        std::cerr << "Error Occurred: " << e.what() << std::endl;
      }
      break;
    }

    // User chooses option 5 -> Add new teacher
    case 5:
    {
      // Clear the output console screen
      clear();

      // Header for add teacher
      std::cout << "==========ADD TEACHER==========" << std::endl;

      // map to store the new teacher's details
      std::map<std::string, std::string> newTeacher;

      // Ask for the teacher's name
      std::cout << "Enter teacher name (firstName lastName): ";
      // Accept the new teacher's name
      std::cin >> newTeacher["fn"] >> newTeacher["ln"];

      // Ask for the new teacher's id
      std::cout << "Enter Teacher id: ";
      // Accept the response
      std::cin >> newTeacher["tid"];

      try
      {
        // stringstream to make the query
        std::stringstream ss;

        // Make the query
        ss << "INSERT INTO Teacher(id, lastName, firstName) values('" << newTeacher["tid"] << "', '" << newTeacher["ln"] << "', '" << newTeacher["fn"] << "')";

        // Execute the query
        stmt->execute(ss.str());

        // Display the success message
        std::cout << "Done!" << std::endl;
      }

      // Catch the mysql error thrown in the try block
      catch (sql::SQLException &e)
      {
        // Display the error message
        std::cerr << "Error Occurred: " << e.what() << std::endl;
      }
      break;
    }

    // User chooses option 6 -> To display the details of all the students
    case 6:
    {
      // Clear the output console screen
      clear();

      // Display the all students header
      std::cout << "==========ALL STUDENTS==========" << std::endl
                << std::endl;

      try
      {
        // stringstream to make the query string
        std::stringstream ss;

        // Make the query string
        ss << "SELECT id, firstName, lastName, totalMarks, avgMarks from Students";

        // Execute the query and store the result in ResultSet object
        sql::ResultSet *res(stmt->executeQuery(ss.str()));

        // Display the header for the students table
        std::cout << "+-------+---------------+---------------+---------------+-------+" << std::endl;
        std::cout << "|ID     |First Name     |Last Name      |Total Marks    |Average|" << std::endl;
        std::cout << "+-------+---------------+---------------+---------------+-------+" << std::endl;

        // Loop to display all the data fetched
        while (res->next())
        {
          // Display the student's data
          std::cout << "|" << res->getString("id") << "\t|" << res->getString("firstName")
                    << "\t\t|" << res->getString("lastName") << "\t\t|" << res->getDouble("totalMarks")
                    << "\t\t|" << res->getDouble("avgMarks") << "\t|" << std::endl;
        }

        // Display the bottom line after the contents of the table
        std::cout << "+-------+---------------+---------------+---------------+-------+" << std::endl;

        std::cout << std::endl
                  << std::endl;
      }

      // Catch the mysql errors thrown in the try error
      catch (sql::SQLException &e)
      {
        // Display the error
        std::cerr << e.what() << '\n';
      }
      break;
    }

    // User chooses option 7 -> Delete account
    case 7:
    {
      // Confirm to delete the account
      std::cout << "Are you sure you want to delete you account? (Y/N): ";

      // Variable to store the user's response
      char option;

      // Accept the user's response
      std::cin >> option;

      // If the user does not want to delete the account
      if (option == 'n' || option == 'N')
        // Go to the next iteration of the loop
        continue;

      // If the user wants to delete the account
      else if (option == 'y' || option == 'Y')
      {
        // stringstream to make the query string
        std::stringstream ss;

        // Make the query string
        ss << "delete from Teacher where id='" << teacherDet["id"] << "'";

        // Execute the mysql query
        stmt->execute(ss.str());

        // Display the success message
        std::cout << "Done! Good Bye!";
        return;
      }
      break;
    }

    // User chooses option 8 -> Exit the program
    case 8:
      return;

      // User chooses invalid option
    default:
      // Display error message
      std::cout << "Wrong option. Try Again!" << std::endl
                << std::endl;
      break;
    }
  }
}