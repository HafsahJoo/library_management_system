/*
   librarian.cpp
   Author: M00952394
   Created: 30/12/2023
   Updated: 14/01/2024
*/

#include "librarian.h"
#include "date.h"
#include "book.h"
#include "validation.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <cmath>
#include "librarian_functions.h"

Librarian::Librarian(int staffID, std::string name,
                     std::string address, std::string email, int salary)
{
    this->staffID = staffID;
    setName(name);
    setAddress(address);
    setEmail(email);
    setSalary(salary);
}

void Librarian::addMember()
{

    int memberID;
    std::string name, address, email;
    memberID = validateMemberID();
    std::cin.ignore();
    name = validateName();
    address = validateAddress();
    email = validateEmail();

    // Check if memberID is unique
    for (unsigned i = 0; i < members.size(); ++i)
    {
        if (memberID == std::stoi(members[i]->getMemberID()))
        {
            std::cout << "\nMemberID already exists. Use a unique one!"
                      << std::endl;
            return;
        }
    }

    // Add the new instance of member to the vector
    members.push_back(new Member(memberID, name, address, email));
    std::cout << "\nMember has successfully been added!" << std::endl;
    std::cout << "Member ID: " << memberID << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "Email: " << email << std::endl;
}

void Librarian::issueBook(int memberID, int bookID)
{
    bool found = false;
    // Check if memberID exists and if book has already been borrowed.
    for (unsigned i = 0; i < members.size(); ++i)
    {
        if (memberID == std::stoi(members[i]->getMemberID()))
        {
            found = true;
        }
        std::vector<Book> borrowedBooks = members[i]->getBooksBorrowed();
        for (unsigned j = 0; j < borrowedBooks.size(); ++j)
        {
            if (std::stoi(borrowedBooks[j].getBookID()) == bookID)
            {
                std::cout << "\nThis book has already been borrowed!"
                          << std::endl;
                return;
            }
        }
    }

    if (!found)
    {
        std::cout << "\nThis MemberID does not exist";
        return;
    }

    // Get details of book from file
    std::string* bookDetails = readFile(bookID);
    if (bookDetails[0] == "no bookID")
    {
        std::cout << "\nThis Book ID does not exist!";
        return;
    }

    Book book(bookID, bookDetails[0], bookDetails[1], bookDetails[2]);

    Date date = createDateInstance();

    // Call the borrowBook method for that member
    for (unsigned i = 0; i < members.size(); ++i)
    {
        if (memberID == std::stoi(members[i]->getMemberID()))
        {
            book.borrowBook(members[i], date);
            std::cout << "\nBook has been successfully issued"<< std :: endl;
        }
    }
}

void Librarian::returnBook(int memberID, int bookID)
{
    for (unsigned i = 0; i < members.size(); ++i)
    {
        if (memberID == std::stoi(members[i]->getMemberID()))
        {
            // Get the list of books borrowed by the member
            std::vector<Book> borrowedBooks = members[i]->getBooksBorrowed();

            for (unsigned j = 0; j < borrowedBooks.size(); ++j)
            {

                if (std::stoi(borrowedBooks[j].getBookID()) == bookID)
                {
                    // Get today's date
                    std::tm todayDate = getTodayDate();
                    int year = todayDate.tm_year + 1900;
                    int month = todayDate.tm_mon + 1;
                    int day = todayDate.tm_mday;
                    // Compares today's date with due date
                    if (borrowedBooks[j].getDueDate().getYear() < year ||
                        (borrowedBooks[j].getDueDate().getYear() == year &&
                         borrowedBooks[j].getDueDate().getMonth() < month) ||
                        (borrowedBooks[j].getDueDate().getYear() == year &&
                         borrowedBooks[j].getDueDate().getMonth() == month &&
                         borrowedBooks[j].getDueDate().getDay() < day))
                    {
                        // Calculate fine if date is overdue
                        this->calcFine(memberID);
                    }
                    else{
                        std::cout << "\nNo fine to be paid for this book."
                                  << std::endl;
                    }
                    // Mark the book as returned
                    borrowedBooks[j].returnBook();
                    std::cout << "\nBook has been successfully returned"
                                    << std :: endl;
                    return;
                }
            }
            // Output a message if the member has not borrowed the  book
            std::cout << "\nThis member has not borrowed this book!"
                      << std::endl;
            return;
        }
    }
    // Output a message if the specified member ID does not exist
    std::cout << "\nThis MemberID does not exist!" << std::endl;
}

void Librarian::displayBorrowedBooks(int memberID)
{
    bool foundMember = false;

    for (unsigned i = 0; i < members.size(); ++i)
    {
        if (memberID == std::stoi(members[i]->getMemberID()))
        {
            foundMember = true;
            std::vector<Book> borrowedBooks = members[i]->getBooksBorrowed();
            // check if member has borrowed at least a book
            if (borrowedBooks.empty())
            {
                std::cout << "\nNo books borrowed by this member."
                          << std::endl;
            }
            else
            {
                std::cout << "\nBooks borrowed by this member: \n"
                          << std::endl;
                // Display the books borrowed by the member
                for (unsigned j = 0; j < borrowedBooks.size(); ++j)
                {
                    std::cout << j + 1 << ". "
                              << borrowedBooks[j].getBookName() << std::endl;
                }
            }
            break;
        }
    }

    if (!foundMember)
    {
        std::cout << "\nThis MemberID does not exist." << std::endl;
    }
}

void Librarian::calcFine(int memberID)
{
    for (unsigned i = 0; i < members.size(); ++i)
    {
        if (memberID == std::stoi(members[i]->getMemberID()))
        {
            std::vector<Book> borrowedBooks = members[i]->getBooksBorrowed();
            for (unsigned j = 0; j < borrowedBooks.size(); ++j)
            {
                // Get today's date
                std::chrono::system_clock::time_point todayDate =
                    std::chrono::system_clock::now();
                std::tm dueDate = {};
                dueDate.tm_year =
                    borrowedBooks[j].getDueDate().getYear() - 1900;
                dueDate.tm_mon = borrowedBooks[j].getDueDate().getMonth() - 1;
                dueDate.tm_mday = borrowedBooks[j].getDueDate().getDay();

                // Convert due date to system_clock::time_point
                std::chrono::system_clock::time_point bookDueDate =
                std::chrono::system_clock::from_time_t(std::mktime(&dueDate));

                // Calculate the difference in days between the dates
                std::chrono::duration<double> difference =
                    todayDate - bookDueDate;
                int differenceDaysInt =
                    static_cast<int>(std::floor(difference.count() / (86400)));

                 // Check if the book is overdue.
                if (differenceDaysInt > 0)
                {
                    // Output the fine amount for the overdue book
                    std::cout << "\n The fine to be paid for BookID "
                              << borrowedBooks[j].getBookID() << " is £ "
                              << differenceDaysInt << std::endl;
                }
            }
        }
    }
}

int Librarian::getStaffID()
{
    return staffID;
}

void Librarian::setStaffID(int staffID)
{
    this->staffID = staffID;
}

int Librarian::getSalary()
{
    return salary;
}

void Librarian::setSalary(int salary)
{
    this->salary = salary;
}

std::vector<Member *> Librarian::getMembers()
{
    return members;
}

void Librarian::setMembers(Member* member)
{
    members.push_back(member);
}
