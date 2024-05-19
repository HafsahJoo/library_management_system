/* 
   person.cpp
   Author: M00952394
   Created: 30/12/2023
   Updated: 12/01/2024
*/

#include "person.h"

std::string Person::getName() {
    return name;
}

void Person::setName(std::string name) {
    this->name = name;
}

std::string Person::getAddress() {
    return address;
}

void Person::setAddress(std::string address) {
    this->address = address;
}

std::string Person::getEmail() {
    return email;
}

void Person::setEmail(std::string email) {
    this->email =email;
}
