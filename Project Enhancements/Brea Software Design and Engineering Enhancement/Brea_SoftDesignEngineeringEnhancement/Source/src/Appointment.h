#pragma once

#include <string>
#include <ctime>

class Appointment {
private:
    const std::string appID;
    std::time_t date;
    std::string desc;

public:
    Appointment(const std::string& appID, std::time_t date, const std::string& desc);
    
    // Getters
    std::string getAppID() const;
    std::time_t getDate() const;
    std::string getDesc() const;
    
    // Setters
    void setDate(std::time_t date);
    void setDesc(const std::string& desc);

    //validators
    void validateDate(std::time_t date);
    void validateDesc(const std::string& desc);
};
