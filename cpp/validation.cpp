/*
 * validation.cpp
 * Author: M00952394
 * Created: 05/01/2024
 * Updated: 14/01/2024
 */

#include "validation.h"
#include <iostream>

bool validateChoice(std::string userInput)
{
    // Check if userInput is within valid range
    if (userInput != "1" && userInput != "2" &&
        userInput != "3" && userInput != "4" && userInput != "5")
    {
        std::cout << "Invalid choice. Please enter a number between 1 and 5 ";
        return false;
    }
    return true;
}

bool checkForAlphabet(std::string inputValue)
{
    // Loop through each character in inputValue
    for (unsigned i = 0; i < inputValue.length(); i++)
    {
        // Check if character is a digit
        if (isdigit(inputValue[i]) == true)
        {
            return true;
        }
    }
    return false;
}

bool checkForNumber(std::string inputValue)
{
    for (unsigned i = 0; i < inputValue.length(); i++)
    {
        if (isdigit(inputValue[i]) == false)
        {
            return false;
        }
    }
    return true;
}

bool containsSpecialCharacters(std::string inputValue)
{
    for (unsigned i = 0; i < inputValue.length(); i++)
    {
        // Check if it is a special character
        if (std::ispunct(inputValue[i]))
        {
            return true;
        }
    }
    return false;
}

int validateMemberID()
{
    std::string memberID;

    std::cout << "Enter memberID: ";
    std::cin >> memberID;

    // Continuously prompt until a valid memberID is provided
    while (checkForNumber(memberID) == false)
    {
        std::cout << "Please enter an integer:  ";
        std::cin >> memberID;
    }
    return std::stoi(memberID);
}

int validateBookID()
{
    std::string bookID;

    std::cout << "Enter bookID: ";
    std::cin >> bookID;

    while (checkForNumber(bookID) == false)
    {
        std::cout << "Please enter an integer:  ";
        std::cin >> bookID;
    }
    return std::stoi(bookID);
}

std::string validateName()
{
    std::string name;

    std::cout << "Enter Member's name: ";
    std::getline(std::cin, name);

    // validate name input
    while (checkForAlphabet(name) == true || name.empty() ||
             containsSpecialCharacters(name) == true)
    {
        if (name.empty())
        {
            std::cout << "Please enter a non-empty value : " ;
        }
        else if (checkForAlphabet(name) == true)
        {
            std::cout << "Name cannot contain numbers. Please enter again : ";
        }
        else if (containsSpecialCharacters(name) == true)
        {
            std::cout << "Name cannot contain " <<
                "special characters. Please enter again : ";
        }
        std::getline(std::cin, name);
    }
    return name;
}

std::string validateAddress(){
    std::string address;

    std::cout << "Enter Member's address: ";
    std::getline(std::cin, address);

    while(address.empty())
    {
        std::cout << "Please enter a non-empty value : ";
        std::getline(std::cin, address);
    }

    return address;
};

std::string validateEmail(){
    std::string email;

    std::cout << "Enter Member's email: ";
    std::getline(std::cin, email);

    // Continuously prompt until email contain '@' and is not empty.
    while(email.empty() || email.find('@') == std::string::npos 
        || email.find('.') == std::string::npos)
    {
        std::cout << "Please enter a valid value : ";
        std::getline(std::cin, email);
    }

    return email;
}