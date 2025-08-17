#pragma once

#include <string>

class Task {
    private:
        const std::string id;
        std::string name;
        std::string description;

    public:
        Task(const std::string& id, const std::string& name, const std::string& description);
    
        // Getters
        std::string getID() const;
        std::string getName() const;
        std::string getDescription() const;
    
        // Setters
        void setName(const std::string& name);
        void setDescription(const std::string& description);

        //Validators
        void validateName(const std::string& name);
        void validateDescription(const std::string& description);
};