/*
   librarian_functions.cpp
   Author: M00952394
   Created: 05/01/2024
   Updated: 14/01/2024
*/

#include "librarian_functions.h"
#include <chrono>

std::string* readFile(int bookID)
{
    std::string* bookDetails = new std::string[3];
    std::string line, mybookID;
    static std::string filename; // static variable to store the filename
    std::ifstream file;
    // If filename is empty ,ask for filename
    if (filename.empty())
    {
        bool fileOpened = false;
        while (!fileOpened)
        {
            std::cout << "\nPlease enter the file name : ";
            std::cin >> filename;

            file.open(filename, std::ios::in);
            if (file.is_open())
            {
                fileOpened = true;
            }
            else
            {
                std::cout << "Unable to open file. Please try again."
                          << std::endl;
            }
        }
    }
    else
    { // If filename is not empty, directly open the file
        file.open(filename, std::ios::in);
    }
    bool found = false;
    while (std::getline(file, line) && !found)
    {
        std::istringstream str(line);
        std::getline(str, mybookID, ','); // Extract the bookID

        // Extract the book details if the bookID matches
        if (mybookID == std::to_string(bookID))
        {   
            bookDetails = extractBookDetails(str);
            found = true;
        }
    }
    file.close();
    if (!found)
    {
        bookDetails[0] = "no bookID";
    }
    return bookDetails;
}

std::string* extractBookDetails(std::istringstream &str)
{
    std::string* bookDetails = new std::string[3];
    std::string bookName, pageCount, authorFirstName, authorLastName, bookType;

    std::string name;
    bool quote = false;
    // check if there if Double quotes in the book name (presence of ,)
    while (std::getline(str, name, ','))
    {
        if (name.front() == '"' && name.back() != '"')
        {
            quote = true;
            bookName = name;
        }
        else if (name.front() != '"' && name.back() == '"')
        {
            quote = false;
            bookName += "," + name;
            bookDetails[0] = bookName;
            std::getline(str, pageCount, ',');
            std::getline(str, authorFirstName, ',');
            std::getline(str, authorLastName, ',');
            std::getline(str, bookType, ',');
            bookDetails[1] = authorFirstName;
            bookDetails[2] = authorLastName;
            break;
        }
        else if (quote)
        {
            bookName += "," + name;
        }
        else
        {
            // If there is no double quotes in the book name
            bookDetails[0] = name;
            std::getline(str, pageCount, ',');
            std::getline(str, authorFirstName, ',');
            std::getline(str, authorLastName, ',');
            std::getline(str, bookType, ',');
            bookDetails[1] = authorFirstName;
            bookDetails[2] = authorLastName;
            break;
        }
    }
    return bookDetails;
}

Date createDateInstance()
{
    // Get the current system time
    auto todayDate = std::chrono::system_clock::now();
    // Add 3 days to today's date
    auto threeDaysLater = todayDate + std::chrono::hours(72);

    std::time_t date = std::chrono::system_clock::to_time_t(threeDaysLater);
    std::tm* dateComponents = std::localtime(&date);
    
    // Extract year, month, and day from the tm structure
    int year = dateComponents->tm_year + 1900;
    int month = dateComponents->tm_mon + 1;
    int day = dateComponents->tm_mday;

    // Create a Date object with the extracted date components
    Date theDate(day, month, year);
    return theDate;
}

std::tm getTodayDate()
{
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
    // Convert the time_t object to a tm structure to extract date components
    std::tm dateComponents = *std::localtime(&nowTime);
    return dateComponents;
}

