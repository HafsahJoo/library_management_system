/*
   main.cpp
   Author: M00952394
   Created: 01/01/2024
   Updated: 12/01/2024
*/

#include <iostream>
#include "librarian.h"
#include "validation.h"


/*
    Display the menu 
    @return choice The user's choice
*/
std::string menu()
{
    std::string choice;
    std::cout << "\n\n       --------------------------------- " << std::endl;
    std::cout << "      |             MENU                |" << std::endl;
    std::cout << "      |---------------------------------|" << std::endl;
    std::cout << "      | 1. Add a new member             |" << std::endl;
    std::cout << "      | 2. Issue a book                 |" << std::endl;
    std::cout << "      | 3. Return a book                |" << std::endl;
    std::cout << "      | 4. Display books borrowed       |" << std::endl;
    std::cout << "      | 5. Exit the program             |" << std::endl;
    std::cout << "       --------------------------------- " << std::endl;
    std::cout << "\nEnter your choice (1-5): ";

    std::cin >> choice;
    return choice;
}




int main()
{
    std::string userChoice;
    int  memberID, bookID;
    Librarian librarian(1512, "hafsah joomun", "royal,road portlouis",
                        "bj273@live.mdx.ac.uk", 3000);

    // Keep displaying menu until user presses 5.
    while (userChoice != "5")
    {
        userChoice = menu();
        while (!validateChoice(userChoice))
        {
            userChoice = menu();
        }
        if (userChoice == "1") {
            librarian.addMember();
        } else if (userChoice == "2") {
            memberID=validateMemberID();
            bookID=validateBookID();
            librarian.issueBook(memberID, bookID);
        } else if (userChoice == "3") {
            memberID=validateMemberID();
            bookID=validateBookID();          
            librarian.returnBook(memberID, bookID);
        } else if (userChoice == "4") {
            memberID=validateMemberID();
            librarian.displayBorrowedBooks(memberID);
        } 
    }
    return 0;
}
