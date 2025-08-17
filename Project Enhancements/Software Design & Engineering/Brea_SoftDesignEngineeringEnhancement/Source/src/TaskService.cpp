#include "TaskService.h"
#include <stdexcept>

void TaskService::addTask(const std::string& id, const std::string& name, const std::string& description) {
    //validate ID
    if (id.empty() || id.length() > 10) {
        throw std::invalid_argument("Invalid ID");
    }

    //add new task to map
    tasks.emplace(id, Task(id, name, description));
}

//finds and removes a task from the map via its id
void TaskService::deleteTask(const std::string& id) {
    tasks.erase(id);
}

//finds and updates a task from the map via its id and given paramters
void TaskService::updateTask(const std::string& id, const std::string& name, const std::string& description) {
    auto it = tasks.find(id);
    if (it != tasks.end()) {
        it->second.setName(name);
        it->second.setDescription(description);
    }
}

//finds and updates a task's name from the map via its id and given parameters
void TaskService::updateTaskName(const std::string& id, const std::string& name) {
    tasks.at(id).setName(name);
}

//finds and updates a task's description from the map via its id and given parameters
void TaskService::updateTaskDescription(const std::string& id, const std::string& description) {
    tasks.at(id).setDescription(description);
}

//finds and returns a task from the map via its id
Task TaskService::getTask(const std::string& id) {
    return tasks.at(id);
}