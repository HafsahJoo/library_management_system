#ifndef _VALIDATION_H_
#define _VALIDATION_H_

/*
   validation.h
   Author: M00952394
   Created: 04/01/2024
   Updated: 14/01/2024
*/

#include <string>

/*
  Validates user input to ensure it falls within a specified range.
  @param userInput The string input to be validated.
  @return True if the input is within the range (1-5), false otherwise.
*/
bool validateChoice(std::string userInput);

/*
  Checks if the input string contains any non alphabet characters.
  @param inputValue The string to be checked.
  @return True if the string contains non alphabet characters, false otherwise.
*/
bool checkForAlphabet(std::string inputValue);

/*
  Checks if the input string contains only numeric characters.
  @param inputValue The string to be checked.
  @return True if the string contains only numeric characters, false otherwise.
*/
bool checkForNumber(std::string inputValue);

/*
  Checks if the given input value contains any special characters.
  @param inputValue The string to be checked.
  @return True if the input value contains special characters, false otherwise.
*/
bool containsSpecialCharacters(std::string inputValue);

/*
  Validates the input string to ensure it contains
  only numeric characters and converts it to an integer.
  @return The validated member ID as an integer.
*/
int validateMemberID();

/*
  Validates the input string to ensure it contains
  only numeric characters and converts it to an integer.
  @return The validated book ID as an integer.
*/
int validateBookID();

/*
  Validates the input string to ensure it contains
  only alphabetic characters (no numbers) and is not empty.
  @return The validated member's name as a string.
*/
std::string validateName();

/*
  Validates the input string to ensure it is not empty
  @return The validated member's address as a string.
*/
std::string validateAddress();

/*
  Validates the input string to ensure it contains
  '@' and is not empty
  @return The validated member's email as a string.
*/
std::string validateEmail();

#endif