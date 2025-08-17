#pragma once

#include <map>
#include <string>
#include "Appointment.h"

class AppointmentService {
private:
    std::map<std::string, Appointment> appointments;

public:
    void addAppointment(const std::string& id, std::time_t date, const std::string& desc);
    void deleteAppointment(const std::string& id);
    void updateAppointment(const std::string& id, std::time_t date, const std::string& desc);
    Appointment getAppointment(const std::string& id);
};

