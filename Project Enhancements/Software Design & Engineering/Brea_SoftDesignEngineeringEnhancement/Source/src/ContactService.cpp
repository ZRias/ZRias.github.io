#include "ContactService.h"
#include <stdexcept>

void ContactService::addContact(const std::string& id, const std::string& firstName, 
                               const std::string& lastName, const std::string& phone, 
                               const std::string& address) {
    //validate ID
    if (id.empty() || id.length() > 10) {
        throw std::invalid_argument("Invalid ID");
    }

    //add contact to map
    contacts.emplace(id, Contact(id, firstName, lastName, phone, address));
}

//finds and removes a contact from the map via its id
void ContactService::removeContact(const std::string& id) {
    contacts.erase(id);
}

//finds and updates the first name of a contact via its id using the given parameters
void ContactService::updateContactFirstName(const std::string& id, const std::string& firstName) {
    contacts.at(id).setFirstName(firstName);
}

//finds and updates the last name of a contact via its id using the given parameters
void ContactService::updateContactLastName(const std::string& id, const std::string& lastName) {
    contacts.at(id).setLastName(lastName);
}

//finds and updates the phone number of a contact via its id using the given parameters
void ContactService::updateContactPhone(const std::string& id, const std::string& phone) {
    contacts.at(id).setPhone(phone);
}

//finds and updates the address of a contact via its id using the given parameters
void ContactService::updateContactAddress(const std::string& id, const std::string& address) {
    contacts.at(id).setAddress(address);
}

//finds and returns a contact via its id
Contact ContactService::getContact(const std::string& id) {
    return contacts.at(id);
}