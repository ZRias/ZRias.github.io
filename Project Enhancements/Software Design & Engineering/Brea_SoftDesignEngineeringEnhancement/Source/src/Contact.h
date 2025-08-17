#pragma once

#include <string>

class Contact {
private:
    const std::string id;
    std::string firstName;
    std::string lastName;
    std::string phone;
    std::string address;

public:
    Contact(const std::string& id, const std::string& firstName, 
            const std::string& lastName, const std::string& phone, 
            const std::string& address);
    
    // Getters
    std::string getID() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPhone() const;
    std::string getAddress() const;
    
    // Setters
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setPhone(const std::string& phone);
    void setAddress(const std::string& address);

    // Validators
    void validateFirstName(const std::string& firstName);
    void validateLastName(const std::string& lastName);
    void validatePhone(const std::string& phone);
    void validateAddress(const std::string& address);
};
