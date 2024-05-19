#ifndef _MEMBER_H_
#define _MEMBER_H_

/*
   member.h
   Author: M00952394
   Created: 30/12/2023
   Updated: 11/01/2024
*/

#include "person.h"
#include "book.h"
#include <vector>
#include <iostream>
#include <string>

/*
  The Member class is a derived class of the Person class and 
  represents a member in a library system.
*/
class Member : public Person
{
private:
    int memberID;
    std::vector<Book> booksLoaned;

public:
    /*
        Constructor for Member class.
        @param memberID The ID of the member.
        @param name The name of the member.
        @param address The address of the member.
        @param email The email of the member.
    */
    Member(int memberID, std::string name, std::string address,
           std::string email);

    /*
        Getter for memberID.
        @return A string representation of the member's ID.
    */
    std::string getMemberID();

    /*
        Getter for booksLoaned vector.
        @return The vector containing the books borrowed by the member.
    */
    std::vector<Book> getBooksBorrowed();

    /*
        Setter for booksLoaned vector.
        Removes the book if it exists in the vector, otherwise adds the book.
        @param book The book to be added or removed from the borrowed books.
    */
    void setBooksBorrowed(Book book);
};

#endif
