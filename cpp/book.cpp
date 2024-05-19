/*
   book.cpp
   Author: M00952394
   Created: 30/12/2023
   Updated: 12/01/2024
*/

#include "book.h"
#include "member.h"
#include <iostream>


Book::Book(int bookID, std::string bookName, std::string authorFirstName,
           std::string authorLastName)
{
    this->bookID = bookID;
    this->bookName = bookName;
    this->authorFirstName = authorFirstName;
    this->authorLastName = authorLastName;
}

std::string Book::getBookID()
{
    return std::to_string(bookID);
}

std::string Book::getBookName()
{
    return bookName;
}

std::string Book::getAuthorFirstName()
{
    return authorFirstName;
}

std::string Book::getAuthorLastName()
{
    return authorLastName;
}

Date Book::getDueDate()
{
    return dueDate;
}

void Book::setDueDate(Date dueDate)
{
    this->dueDate = dueDate;
}

void Book::returnBook()
{
    borrower->setBooksBorrowed(*this);
}

void Book::borrowBook(Member* borrower, Date dueDate)
{
    // Set the due date for the book
    setDueDate(dueDate);
    this->borrower = borrower;
    // Update the borrower's list of borrowed books
    borrower->setBooksBorrowed(*this);
}
