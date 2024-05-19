#ifndef _LIBRARIAN_H_
#define _LIBRARIAN_H_

/*
   librarian.h
   Author: M00952394
   Created: 30/12/2023
   Updated: 11/01/2024
*/

#include "person.h"
#include "member.h"

/*
  Represents a librarian who manages the library system.
  The Librarian class inherits from the Person class and provides
  functionality to add members, issue and return books, calculate fines,
  and display borrowed books for a member.
*/
class Librarian : public Person
{
private:
    int staffID;
    int salary;
    std::vector<Member *> members;

public:

    /*
      Constructor for the Librarian class.
      @param staffID The ID of the staff.
      @param name The name of the staff.
      @param address The first name of the book's author.
      @param e The last name of the book's author.
    */
    Librarian(int staffID, std::string name, std::string address,
              std::string email, int salary);

    /*
        Add a new member to the 'members' vector
    */
    void addMember();

    /*
        Issue a book to a member if the memberID exists and
        if the book is available
        @param memberID the memberID to issue the book to
        @param bookID the bookID of the book to issue
    */
    void issueBook(int memberID, int bookID);

    /*
        Check if the member exists and has borrowed that book
        then check if book is overdue and calculate fine if so.
        @param memberID the memberID of the member returning the book
        @param bookID the bookID of the book being returned
    */
    void returnBook(int memberID, int bookID);

    /*
        Display books borrowed by a member is the memberID exists
        @param memberID the memberID of the member to display book for
    */
    void displayBorrowedBooks(int memberID);

    /*
        Calculate the fine to be paid for overdue books
        @param memberID the memberID of the member to calculate fine for
    */
    void calcFine(int memberID);

    /*
        Getter for the staffID of the librarian  
        @return the staffID of the librarian
    */
    int getStaffID();

    /*
        setter for the staffID of the librarian
        @param staffID the staffID of the librarian
    */
    void setStaffID(int staffID);

    /*
        Getter for the salary of the librarian
        @return the salary of the librarian
    */
    int getSalary();

    /*
        setter for the salary of the librarian
        @param salary the salary of the librarian
    */
    void setSalary(int salary);
 
    /*
        Getter for the members vector
        @return the members vector
    */
    std::vector<Member*> getMembers();

    /*
        Add a new member to the 'members' vector
        @param member the member to add
    */
    void setMembers(Member* member);
};

#endif
