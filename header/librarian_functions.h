#ifndef _LIBRARIAN_FUNCTIONS_H_
#define _LIBRARIAN_FUNCTIONS_H_

/*
   librarian_functions.h
   Author: M00952394
   Created: 05/01/2024
   Updated: 11/01/2024
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include<chrono>
#include "date.h"

/*
  Reads the content of a file with the given book ID.
  @param bookID The ID of the book to read.
  @return A pointer to a std::string containing the content of the file.
 */
std::string* readFile(int bookID);
/*
   Creates a date instance with the current date + 3 days
   @return the date instance
*/
Date createDateInstance();

/*
  Extracts book details from a given input string stream.
  @param str The input string stream from which to extract the book details.
  @return A pointer to a std::string object containing the extracted book details.
*/
std::string* extractBookDetails(std::istringstream &str);

/*
  Retrieve the current date as a std::tm structure
  @return A std::tm structure representing the current date and time.
*/
std::tm getTodayDate();

#endif