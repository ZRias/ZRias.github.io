#include "Task.h"
#include <stdexcept>

Task::Task(const std::string& id, const std::string& name, const std::string& description)
    : id(id), name(name), description(description) {

    //validate ID
    if (id.empty() || id.length() > 10) {
        throw std::invalid_argument("Invalid ID");
    }

    //validate other member variables
    validateName(name);
    validateDescription(description);
}


//return task id
std::string Task::getID() const {
    return id;
}

//return task name
std::string Task::getName() const {
    return name;
}

//return task description
std::string Task::getDescription() const {
    return description;
}

//set new task name
void Task::setName(const std::string& name) {
    validateName(name);
    this->name = name;
}

//set new description
void Task::setDescription(const std::string& description) {
    validateDescription(description);
    this->description = description;
}

//make sure name meets required input guidelines
void Task::validateName(const std::string& name) {
    if (name.empty() || name.length() > 20) {
        throw std::invalid_argument("Invalid Name");
    }
}

//make sure description meets required input guidelines
void Task::validateDescription(const std::string& description) {
    if (description.empty() || description.length() > 50) {
        throw std::invalid_argument("Invalid Description");
    }
}