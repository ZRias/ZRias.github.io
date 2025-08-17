#include "AppointmentService.h"
#include <stdexcept>

void AppointmentService::addAppointment(const std::string& id, std::time_t date, const std::string& desc) {
    
    //validate ID
    if (id.empty() || id.length() > 10) {
        throw std::invalid_argument("Invalid ID");
    }

    //add new appointment to map
    appointments.emplace(id, Appointment(id, date, desc));
}

//finds and deletes appointment from map via its id
void AppointmentService::deleteAppointment(const std::string& id) {
    appointments.erase(id);
}

//finds and updates appointment from map via its id and given parameters
void AppointmentService::updateAppointment(const std::string& id, std::time_t date, const std::string& desc) {
    auto it = appointments.find(id);
    if (it != appointments.end()) {
        it->second.setDate(date);
        it->second.setDesc(desc);
    }
}

//finds and returns appointment from map via its id
Appointment AppointmentService::getAppointment(const std::string& id) {
    return appointments.at(id);
}