#ifndef _PERSON_H_
#define _PERSON_H_

/* 
   person.cpp
   Author: M00952394
   Created: 30/12/2023
   Updated: 11/01/2024
*/

#include <string>

/*
  The Person class provides methods to get and set the name,
  address, and email of a person.
*/
class Person {
private:
    std::string name;
    std::string address;
    std::string email;

public:
    /*
      Getter for the name of the person.
      @return The name of the person.
    */
    std::string getName();

    /*
      Setter for the name of the person.
      @param name The name to be set.
    */
    void setName(std::string name);

    /*
      Getter for the address of the person.
      @return The address of the person.
    */
    std::string getAddress();

    /*
      Setter for the address of the person.
      @param address The address to be set.
    */
    void setAddress(std::string address);

    /*
      Getter for the email of the person.
      @return The email of the person.
    */
    std::string getEmail();

    /*
      Setter for the email of the person.
      @param email The email to be set.
    */
    void setEmail(std::string email);
};

#endif 
