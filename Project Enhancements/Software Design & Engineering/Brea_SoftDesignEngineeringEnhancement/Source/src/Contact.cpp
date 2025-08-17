#include "Contact.h"
#include <stdexcept>

Contact::Contact(const std::string& id, const std::string& firstName, 
                 const std::string& lastName, const std::string& phone, 
                 const std::string& address)
    : id(id), firstName(firstName), lastName(lastName), phone(phone), address(address) {
    
    //validate ID
    if (id.empty() || id.length() > 10) {
        throw std::invalid_argument("Invalid ID");
    }
    
    //validate other member variables
    validateFirstName(firstName);
    validateLastName(lastName);
    validatePhone(phone);
    validateAddress(address);
}

//return contact id
std::string Contact::getID() const {
    return id;
}

//return contact first name
std::string Contact::getFirstName() const {
    return firstName;
}

//return contact last name
std::string Contact::getLastName() const {
    return lastName;
}

//return contact phone number
std::string Contact::getPhone() const {
    return phone;
}

//return contact address
std::string Contact::getAddress() const {
    return address;
}

//set new first name
void Contact::setFirstName(const std::string& firstName) {

    validateFirstName(firstName);

    this->firstName = firstName;
}

//set new last name
void Contact::setLastName(const std::string& lastName) {

    validateLastName(lastName);

    this->lastName = lastName;
}

//set new phone number
void Contact::setPhone(const std::string& phone) {

    validatePhone(phone);

    this->phone = phone;
}

//set new address
void Contact::setAddress(const std::string& address) {

    validateAddress(address);

    this->address = address;
}

//makes sure first name meets required input guidelines
void Contact::validateFirstName(const std::string& firstName) {
    if (firstName.empty() || firstName.length() > 10) {
        throw std::invalid_argument("Invalid First Name");
    }
}

//makes sure last name meets required input guidelines
void Contact::validateLastName(const std::string& lastName) {
    if (lastName.empty() || lastName.length() > 10) {
        throw std::invalid_argument("Invalid Last Name");
    }
}

//makes sure phone number meets required input guidelines
void Contact::validatePhone(const std::string& phone) {
    if (phone.empty() || phone.length() != 10) {
        throw std::invalid_argument("Invalid Phone Number");
    }
}

//makes sure address meets required input guidelines
void Contact::validateAddress(const std::string& address) {
    if (address.empty() || address.length() > 30) {
        throw std::invalid_argument("Invalid Address");
    }
}