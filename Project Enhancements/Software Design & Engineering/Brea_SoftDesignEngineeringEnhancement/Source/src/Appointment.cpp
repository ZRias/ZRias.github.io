#include "Appointment.h"
#include <ctime>
#include <stdexcept>

Appointment::Appointment(const std::string& appID, std::time_t date, const std::string& desc) 
    : appID(appID), date(date), desc(desc) {

    //validate ID
    if (appID.empty() || appID.length() > 10) {
        throw std::invalid_argument("Invalid ID");
    }

    //validate other member variables
    validateDate(date);
    validateDesc(desc);
}

//return appointment ID
std::string Appointment::getAppID() const {
    return appID;
}

//return appointment date
std::time_t Appointment::getDate() const {
    return date;
}

//return appointment description
std::string Appointment::getDesc() const {
    return desc;
}

//set new date for appointment
void Appointment::setDate(std::time_t date) {
    validateDate(date);
    this->date = date;
}

//set new description for appointment
void Appointment::setDesc(const std::string& desc) {
    validateDesc(desc);
    this->desc = desc;
}

//makes sure date meets required input guidelines
void Appointment::validateDate(std::time_t date) {
    if (date < std::time(nullptr)) {
        throw std::invalid_argument("Invalid Date");
    }
}

//makes sure description meets required input guidelines
void Appointment::validateDesc(const std::string& desc) {
    if (desc.empty() || desc.length() > 50) {
        throw std::invalid_argument("Invalid Description");
    }
}