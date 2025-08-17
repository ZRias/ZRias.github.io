#pragma once

#include <map>
#include <string>
#include "Contact.h"

class ContactService {
private:
    std::map<std::string, Contact> contacts;

public:
    void addContact(const std::string& id, const std::string& firstName, 
                   const std::string& lastName, const std::string& phone, 
                   const std::string& address);
    void removeContact(const std::string& id);
    void updateContactFirstName(const std::string& id, const std::string& firstName);
    void updateContactLastName(const std::string& id, const std::string& lastName);
    void updateContactPhone(const std::string& id, const std::string& phone);
    void updateContactAddress(const std::string& id, const std::string& address);
    Contact getContact(const std::string& id);
};
