/*
   librarian_test.cpp
   Author: M00952394
   Created: 10/01/2024
   Updated: 12/01/2024
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "librarian.h"
#include "person.h"
#include "book.h"
#include "member.h"

TEST_CASE("Tests for Add member functionality", "[Librarian]")
{
    Librarian librarian(2601, "Sarah", "Portlouis", "sarah@gmail.com", 50000);

    SECTION("Test add new member")
    {
        std::stringstream librarianInput;
        // Create a string stream with the input
        librarianInput << "145\nJohn\nportlouis\nJohn@gmail.com\n";

        // Save the original cin buffer
        std::streambuf* inputBuffer = std::cin.rdbuf();

        // Redirect cin to a different stream buffer
        std::cin.rdbuf(librarianInput.rdbuf());

        librarian.addMember();

        // Restore the original cin buffer
        std::cin.rdbuf(inputBuffer);

        REQUIRE(librarian.getMembers().size() == 1);
        REQUIRE(librarian.getMembers()[0]->getName() == "John");
        REQUIRE(librarian.getMembers()[0]->getAddress() == "portlouis");
        REQUIRE(librarian.getMembers()[0]->getEmail() == "John@gmail.com");
    }

    SECTION("Test add existing member")
    {
        std::stringstream librarianInput;
        librarianInput << "150\njohn\nportlouis\njohn@gmail.com\n";

        std::streambuf* inputBuffer = std::cin.rdbuf();

        
        std::cin.rdbuf(librarianInput.rdbuf());

        librarian.addMember();
        
        // Member has been successfully added
        REQUIRE(librarian.getMembers().size() == 1);
        REQUIRE(librarian.getMembers()[0]->getName() == "john");

        // Attempt to add a member with existing memberID
        librarianInput << "150\nAlison\nMahebourg\nalison@gmail.com\n";

        std::cin.rdbuf(librarianInput.rdbuf());

        librarian.addMember();

        std::cin.rdbuf(inputBuffer);

        // Member was not added since memberID is not unique
        REQUIRE(librarian.getMembers().size() == 1);
        REQUIRE(librarian.getMembers()[0]->getName() == "john");
    }
}

TEST_CASE("Tests for issue book functionality", "[Librarian]")
{
    Librarian librarian(2601, "Sarah", "Portlouis", "sarah@gmail.com", 50000);

    SECTION("Issue book to an existing member")
    {

        std::stringstream librarianInput;
        librarianInput << "10\nGeetika\nTriolet\ngeetika@gmail.com\n";
        std::streambuf* inputBuffer = std::cin.rdbuf();

        
        std::cin.rdbuf(librarianInput.rdbuf());

        // Adding a new member
        librarian.addMember();

        std::stringstream fileName;

        fileName << "a.csv";

        std::cin.rdbuf(fileName.rdbuf());

        // Issue book to the member
        librarian.issueBook(10, 10);

        std::cin.rdbuf(inputBuffer);

        auto members = librarian.getMembers()[0];
        // Check if the book has been added to the member's borrowed books
        REQUIRE(members->getBooksBorrowed().size() == 1);
        REQUIRE(members->getBooksBorrowed()[0].getBookID() == "10");
    }

    SECTION("Issue book to a non existing member")
    {
        std::stringstream librarianInput;
        librarianInput << "a.csv";

        std::streambuf* inputBuffer = std::cin.rdbuf();
        std::stringstream output;
        std::streambuf* outputBuffer = std::cout.rdbuf();

        // Redirect cout to use 'output' stringstream for to store output
        std::cout.rdbuf(output.rdbuf());
        std::cin.rdbuf(librarianInput.rdbuf());

        librarian.issueBook(145, 10);

        std::cin.rdbuf(inputBuffer);
        std::cout.rdbuf(outputBuffer);
        // Store captured output from 'output' stringstream into a string
        std::string outputStr = output.str();

        // Check if the output contains the expected string
        REQUIRE(outputStr.find("This MemberID does not exist") !=
                std::string::npos);
    }

    SECTION("Issue the same book twice to the same member")
    {

        std::stringstream librarianInput;
        librarianInput << "145\nJanvi\ntriolet\njanvi@gmail.com\n";

        std::streambuf* inputBuffer = std::cin.rdbuf();

        std::cin.rdbuf(librarianInput.rdbuf());

        librarian.addMember();

        std::cin.rdbuf(inputBuffer);

        librarian.issueBook(145, 10);

        // Check if the book has been added to the member's borrowed books
        REQUIRE(librarian.getMembers()[0]->getBooksBorrowed().size() == 1);

        // Attempt to issue the same book to the same member again
        librarian.issueBook(145, 10);

        REQUIRE(librarian.getMembers().size() == 1);

        // Number of borrowed books stays the same
        REQUIRE(librarian.getMembers()[0]->getBooksBorrowed().size() == 1);
    }

    SECTION("Issue the same book to 2 different members")
    {

        std::stringstream librarianInput;
        librarianInput << "145\nJanvi\ntriolet\njanvi@gmail.com\n";

        std::streambuf* inputBuffer = std::cin.rdbuf();

        std::cin.rdbuf(librarianInput.rdbuf());

        librarian.addMember();

        librarianInput << "15\nBhanavi\nTerre rouge\nBhanavi@gmail.com\n";

        std::cin.rdbuf(librarianInput.rdbuf());

        librarian.addMember();

        std::cin.rdbuf(inputBuffer);

        librarian.issueBook(145, 10);

        // Check if the book has been added to the member's borrowed books
        REQUIRE(librarian.getMembers()[0]->getBooksBorrowed().size() == 1);

        // Attempt to issue the same book to the same member again
        librarian.issueBook(15, 10);

        // Check if the book has been added to the 2nd member's borrowed books
        REQUIRE(librarian.getMembers()[1]->getBooksBorrowed().size() == 0);
    }

    SECTION("Issue a non-existing book to a member")
    {
        std::stringstream librarianInput;
        librarianInput << "145\nJanvi\ntriolet\njanvi@gmail.com\n";

        std::streambuf* inputBuffer = std::cin.rdbuf();

        std::cin.rdbuf(librarianInput.rdbuf());

        librarian.addMember();

        std::cin.rdbuf(inputBuffer);

        librarian.issueBook(145, 14524);

        // Book has not been added to the member's list of borrowed book.
        REQUIRE(librarian.getMembers()[0]->getBooksBorrowed().size() == 0);
    }
}

TEST_CASE("Tests for Display borrowed books functionality", "[Librarian]")
{
    Librarian librarian(2601, "Sarah", "Portlouis", "sarah@gmail.com", 50000);

    SECTION("Display books for an existing member")
    {
        librarian.setMembers
                (new Member(100,"ishita","Quatresbornes","ishita@gmail.com"));
        librarian.getMembers()[0]->setBooksBorrowed
                (Book(200, "Book A", "joe", "monkey"));
        librarian.getMembers()[0]->setBooksBorrowed
                (Book(201, "Book B", "bil", "ate"));

        std::stringstream output;
        std::streambuf* outputBuffer = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());

        librarian.displayBorrowedBooks(100);

        std::cout.rdbuf(outputBuffer);

        std::string outputStr = output.str();

        // Check if the member has 2 borrowed books
        REQUIRE(librarian.getMembers()[0]->getBooksBorrowed().size() == 2);

        // check if the 2 books are being displayed
        REQUIRE(outputStr.find("Book A") != std::string::npos);
        REQUIRE(outputStr.find("Book B") != std::string::npos);
    }

    SECTION("Display books for a non existing member")
    {
        std::stringstream output;
        std::streambuf* outputBuffer = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());

        librarian.displayBorrowedBooks(110);

        std::cout.rdbuf(outputBuffer);

        std::string outputStr = output.str();

        //Check if the correct message is output
        REQUIRE(outputStr.find("This MemberID does not exist.")
                 != std::string::npos);
    }
}

TEST_CASE("Tests for Return book functionality", "[Librarian]")
{
    Librarian librarian(2601, "Sarah", "Portlouis", "sarah@gmail.com", 50000);
    SECTION("Return Book with Fine")
    {
        
        librarian.setMembers
            (new Member(100,"ishita","Quatresbornes","ishita@gmail.com"));
        Book book(10, "harry potter", "jk", "rowling");

        // Make the member borrow a book with a due date of 1/1/2024
        book.borrowBook(librarian.getMembers()[0], Date(1, 1, 2024));

        //Check if book has been successfully borrowed
        REQUIRE(librarian.getMembers()[0]->getBooksBorrowed().size() == 1);
        std::stringstream output;
        std::streambuf* outputBuffer = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());

        librarian.returnBook(100, 10);
        std::cout.rdbuf(outputBuffer);

        std::string outputStr = output.str();

        // Check if the fine is being displayed
        REQUIRE(outputStr.find("The fine to be paid for BookID")
                != std::string::npos);

        // Check if book has been returned
        REQUIRE(librarian.getMembers()[0]->getBooksBorrowed().size() == 0);
    }
    SECTION("Return Book with No Fine")
    {

        librarian.setMembers
            (new Member(100,"ishita","Quatresbornes","ishita@gmail.com"));

        std::stringstream librarianInput;
        librarianInput << "a.csv";
        std::streambuf* inputBuffer = std::cin.rdbuf();
        std::cin.rdbuf(librarianInput.rdbuf());

        librarian.issueBook(100, 10);

        std::cin.rdbuf(inputBuffer);
        REQUIRE(librarian.getMembers()[0]->getBooksBorrowed().size() == 1);

        std::stringstream output;
        std::streambuf* outputBuffer = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());

        librarian.returnBook(100, 10);

        std::cout.rdbuf(outputBuffer);
        std::string outputStr = output.str();

        // Check if there is no fine and book has been returned
        REQUIRE(outputStr.find("No fine to be paid for this book.") 
            != std::string::npos);
        REQUIRE(librarian.getMembers()[0]->getBooksBorrowed().size() == 0);
    }

    SECTION("Return a book from a memberID which does not exist")
    {

        std::stringstream output;
        std::streambuf* outputBuffer = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());

        librarian.returnBook(100, 11);

        std::cout.rdbuf(outputBuffer);

        std::string outputStr = output.str();
        REQUIRE(librarian.getMembers().size() == 0);
        REQUIRE(outputStr.find("\nThis MemberID does not exist!") 
            != std::string::npos);
    }

    SECTION("Return Book which has not been borrowed by this member")
    {
        librarian.setMembers
            (new Member(100,"ishita","Quatresbornes","ishita@gmail.com"));

        std::stringstream librarianInput;
        librarianInput << "a.csv";
        std::streambuf* inputBuffer = std::cin.rdbuf();
        std::cin.rdbuf(librarianInput.rdbuf());

        //Member borrows book with bookID 11
        librarian.issueBook(100, 11);

        std::cin.rdbuf(inputBuffer);

        std::stringstream output;
        std::streambuf* outputBuffer = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());

        //Member borrows book with bookID 10
        librarian.returnBook(100, 10);

        std::cout.rdbuf(outputBuffer);
        std::string outputStr = output.str();

        REQUIRE(outputStr.find("This member has not borrowed this book!") 
            != std::string::npos);
        // Check is book with bookID 10 has not been returned
        REQUIRE(librarian.getMembers()[0]->getBooksBorrowed().size() == 1);

    }

    
}

TEST_CASE("Testing getter/setter of Librarian class", "[Librarian]")
{
    Librarian librarian(2601, "Sarah", "Portlouis", "sarah@gmail.com", 50000);

    SECTION("Test getter and setter for salary")
    {
        REQUIRE(librarian.getSalary() == 50000); // Initial salary check

        librarian.setSalary(35000); // Change salary
        REQUIRE(librarian.getSalary() == 35000);
    }

    SECTION("Test getter and setter for staffID")
    {
        REQUIRE(librarian.getStaffID() == 2601);

        librarian.setStaffID(2603);
        REQUIRE(librarian.getStaffID() == 2603);
    }
}

TEST_CASE("Testing methods of person class", "[Person]")
{
    Person person;

    SECTION("Testing getter and setter for name")
    {
        person.setName("Hafsah Joomun");
        REQUIRE(person.getName() == "Hafsah Joomun");
    }

    SECTION("Testing getter and setter for address")
    {
        person.setAddress("Royal road, Port louis");
        REQUIRE(person.getAddress() == "Royal road, Port louis");
    }

    SECTION("Testing getter and setter for email")
    {
        person.setEmail("hafsah@gmail.com");
        REQUIRE(person.getEmail() == "hafsah@gmail.com");
    }
}

TEST_CASE("Testing methods of book class", "[Book]")
{
    Book book(26, "tikoulou", "Paul", "Smith");

    SECTION("Testing getBookID()")
    {
        REQUIRE(book.getBookID() == "26");
    }

    SECTION("Testing getBookName() ")
    {
        REQUIRE(book.getBookName() == "tikoulou");
    }

    SECTION("Testing getAuthorFirstName() ")
    {
        REQUIRE(book.getAuthorFirstName() == "Paul");
    }

    SECTION("Testing getAuthorLastName() ")
    {
        REQUIRE(book.getAuthorLastName() == "Smith");
    }
}

TEST_CASE("Testing methods for member class", "[Member]")
{
    Member member(2601, "Rita", "portlouis", "Rita@hotmail.com");

    SECTION("Testing getter for memberID")
    {
        REQUIRE(member.getMemberID() == "2601");
    }

    SECTION("Testing getter for memberID")
    {
        REQUIRE(member.getMemberID() == "2601");
    }

    SECTION("Testing getBooksBorrowed and setBooksBorrowed")
    {
        Book book1(1, "HPOTTER", "JK", "MN");
        Book book2(2, "HPOTTER2", "KL", "OP");

        member.setBooksBorrowed(book1);
        member.setBooksBorrowed(book2);

        REQUIRE(member.getBooksBorrowed().size() == 2);
    }

}