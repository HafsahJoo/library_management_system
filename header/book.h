#ifndef _BOOK_H_
#define _BOOK_H_

/*
   book.h
   Author: M00952394
   Created: 30/12/2023
   Updated: 11/01/2024
*/

#include <string>
#include "date.h"

class Member;

/*
  The Book class stores information about a book.
  It provides methods to get and set the book's information,
   as well as borrow and return the book.
*/
class Book
{
private:
    int bookID;
    std::string bookName;
    std::string authorFirstName;
    std::string authorLastName;
    std::string bookType;
    Date dueDate;
    Member* borrower;

public:
    /*
      Constructor for the Book class.
      @param bookID The ID of the book.
      @param bookName The name of the book.
      @param authorFirstName The first name of the book's author.
      @param authorLastName The last name of the book's author.
    */
    Book(int bookID, std::string bookName, std::string authorFirstName,
         std::string authorLastName);

    /*
      Getter for the book ID.
      @return A string representation of the book's ID.
    */
    std::string getBookID();

    /*
      Getter for the book name.
      @return The name book's name.
    */
    std::string getBookName();

    /*
      Getter for the author's first name.
      @return The first name of the book's author.
    */
    std::string getAuthorFirstName();

    /*
      Getter for the author's last name.
      @return The last name of the book's author.
    */
    std::string getAuthorLastName();

    /*
      Getter for the due date of the book.
      @return The due date of the book.
    */
    Date getDueDate();

    /*
      Setter for the due date of the book.
      @param dueDate The due date to be set for the book.
    */
    void setDueDate(Date dueDate);

    /*
      Return a book
    */
    void returnBook();

    /*
      Borrow the book by a member with a specified due date.
      @param borrower The member borrowing the book.
      @param dueDate The due date for returning the book.
    */
    void borrowBook(Member* borrower, Date dueDate);
};

#endif