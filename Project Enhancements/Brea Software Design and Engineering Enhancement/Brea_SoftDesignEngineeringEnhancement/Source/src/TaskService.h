#pragma once

#include <map>
#include <string>
#include "Task.h"

class TaskService {
private:
    std::map<std::string, Task> tasks;

public:
    void addTask(const std::string& id, const std::string& name, const std::string& description);
    void deleteTask(const std::string& id);
    void updateTask(const std::string& id, const std::string& name, const std::string& description);
    void updateTaskName(const std::string& id, const std::string& name);
    void updateTaskDescription(const std::string& id, const std::string& description);
    Task getTask(const std::string& id);
};

