/*
   member.cpp
   Author: M00952394
   Created: 30/12/2023
   Updated: 14/01/2024
*/

#include "member.h"

Member::Member(int memberID, std::string name, std::string address,
               std::string email)
{
    this->memberID = memberID;
    setName(name);
    setAddress(address);
    setEmail(email);
}

std::string Member::getMemberID()
{
    return std::to_string(memberID);
}

std::vector<Book> Member::getBooksBorrowed()
{
    return booksLoaned;
}

void Member::setBooksBorrowed(Book book)
{
    // Check if the book is already in the vector
    for (unsigned i = 0; i < booksLoaned.size(); ++i)
    {
        if (book.getBookID() == booksLoaned[i].getBookID())
        {
            // If the book is found, remove it.
            booksLoaned.erase(booksLoaned.begin() + i);
            return;
        }
    }
    // If the book is not found in the vector, add it.
    booksLoaned.push_back(book);
}
