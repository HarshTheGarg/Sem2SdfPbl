// ./clearS.cpp
/* including header files */
// Header file for std namespace, including cout, cin, string etc
#include <iostream>

// Header file to use system command
#include <stdlib.h>

/*
Function to clear the console screen, based on the user's OS.
No output
*/
void clear()
{
  // If the user is using the Windows OS
#ifdef _WIN32
  // command to clear the screen is CLS on Windows
  system("CLS");
#endif

// If the user is using the Linux based OS
#ifdef __linux__
  // Command to clear the screen in clear for linux based system
  system("clear");
#endif
}