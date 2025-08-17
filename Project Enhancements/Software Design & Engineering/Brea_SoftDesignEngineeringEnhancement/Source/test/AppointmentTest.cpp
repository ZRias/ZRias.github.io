#include "pch.h"
#include "CppUnitTest.h"
#include "Source/src/Appointment.h"
#include <ctime>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(AppointmentTest) {
public:
    // Testing variables
    std::string testID = "APP123";
    std::time_t testDate;
    std::string testDesc = "Annual checkup";

    // Sample object for testing
    Appointment* appointment;

    // Initialize appointment object
    TEST_METHOD_INITIALIZE(initializeObject) {
        testDate = std::time(nullptr) + 86400; // Tomorrow
        appointment = new Appointment(testID, testDate, testDesc);
    }

    // Test Object Initialization
    TEST_METHOD(testObjectCreation) {
        Assert::AreEqual(appointment->getAppID(), testID);
        Assert::AreEqual(appointment->getDate(), testDate);
        Assert::AreEqual(appointment->getDesc(), testDesc);
    }

    // Test Object Constructor Throws for ID
    TEST_METHOD(testObjectThrowID) {
        auto emptyID = [] { 
            std::time_t date = std::time(nullptr) + 86400;
            Appointment("", date, "Annual checkup"); 
        };
        Assert::ExpectException<std::invalid_argument>(emptyID);

        auto longID = [] { 
            std::time_t date = std::time(nullptr) + 86400;
            Appointment("APP123456789", date, "Annual checkup"); 
        };
        Assert::ExpectException<std::invalid_argument>(longID);
    }

    // Test Object Constructor Throws for Date
    TEST_METHOD(testObjectThrowDate) {
        auto pastDate = [] { 
            std::time_t date = std::time(nullptr) - 86400; // Yesterday
            Appointment("APP123", date, "Annual checkup"); 
        };
        Assert::ExpectException<std::invalid_argument>(pastDate);
    }

    // Test Object Constructor Throws for Description
    TEST_METHOD(testObjectThrowDesc) {
        auto emptyDesc = [] { 
            std::time_t date = std::time(nullptr) + 86400;
            Appointment("APP123", date, ""); 
        };
        Assert::ExpectException<std::invalid_argument>(emptyDesc);

        auto longDesc = [] { 
            std::time_t date = std::time(nullptr) + 86400;
            Appointment("APP123", date, "This description is way too long for the appointment and should throw an exception"); 
        };
        Assert::ExpectException<std::invalid_argument>(longDesc);
    }

    // Test Object Setters
    TEST_METHOD(testObjectSetters) {
        std::time_t newDate = std::time(nullptr) + 172800; // 2 days from now
        std::string newDesc = "Follow-up visit";

        appointment->setDate(newDate);
        appointment->setDesc(newDesc);

        Assert::AreEqual(appointment->getDate(), newDate);
        Assert::AreEqual(appointment->getDesc(), newDesc);
    }

    // Test Date Setter Throws
    TEST_METHOD(testDateSetterThrow) {
        std::time_t pastDate = std::time(nullptr) - 86400; // Yesterday
        Assert::ExpectException<std::invalid_argument>([this, pastDate]() { 
            appointment->setDate(pastDate); 
        });
    }

    // Test Description Setter Throws
    TEST_METHOD(testDescSetterThrow) {
        Assert::ExpectException<std::invalid_argument>([this]() { 
            appointment->setDesc(""); 
        });
        Assert::ExpectException<std::invalid_argument>([this]() { 
            appointment->setDesc("This description is way too long for the appointment and should throw an exception"); 
        });
    }

    // Clean up
    TEST_METHOD_CLEANUP(cleanup) {
        delete appointment;
    }
};