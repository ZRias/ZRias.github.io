#include "pch.h"
#include "CppUnitTest.h"
#include "Source/src/AppointmentService.h"
#include <ctime>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(AppointmentServiceTest) {
public:
    // Testing variables
    std::string testID = "APP123";
    std::time_t testDate;
    std::string testDesc = "Annual checkup";

    // Service instance
    AppointmentService service;

    // Initialize test date
    TEST_METHOD_INITIALIZE(initialize) {
        testDate = std::time(nullptr) + 86400; // Tomorrow
    }

    // Test Add Appointment Method
    TEST_METHOD(testAddAppointment) {
        service.addAppointment(testID, testDate, testDesc);
        
        Appointment appointment = service.getAppointment(testID);
        Assert::AreEqual(appointment.getAppID(), testID);
        Assert::AreEqual(appointment.getDate(), testDate);
        Assert::AreEqual(appointment.getDesc(), testDesc);
    }

    // Test Delete Appointment Method
    TEST_METHOD(testDeleteAppointment) {
        service.addAppointment(testID, testDate, testDesc);
        
        // Verify appointment exists
        try {
            Appointment appointment = service.getAppointment(testID);
            Assert::IsTrue(true);
        }
        catch (...) {
            Assert::Fail(L"Unexpected exception");
        }

        // Delete appointment
        service.deleteAppointment(testID);

        // Verify appointment was deleted
        try {
            service.getAppointment(testID);
            Assert::Fail(L"Should have thrown exception for deleted appointment");
        }
        catch (const std::out_of_range&) {
            Assert::IsTrue(true);
        }
        catch (...) {
            Assert::Fail(L"Unexpected exception");
        }
    }

    // Test Update Appointment Method
    TEST_METHOD(testUpdateAppointment) {
        std::time_t newDate = std::time(nullptr) + 172800; // 2 days from now
        std::string newDesc = "Follow-up visit";

        service.addAppointment(testID, testDate, testDesc);
        service.updateAppointment(testID, newDate, newDesc);

        Appointment appointment = service.getAppointment(testID);
        Assert::AreEqual(appointment.getDate(), newDate);
        Assert::AreEqual(appointment.getDesc(), newDesc);
    }

    // Test Add Appointment Throws for ID
    TEST_METHOD(testAddAppointmentThrowID) {
        auto emptyID = [this] { 
            service.addAppointment("", testDate, testDesc); 
        };
        Assert::ExpectException<std::invalid_argument>(emptyID);

        auto longID = [this] { 
            service.addAppointment("APP123456789", testDate, testDesc); 
        };
        Assert::ExpectException<std::invalid_argument>(longID);
    }

    // Test Add Appointment Throws for Date
    TEST_METHOD(testAddAppointmentThrowDate) {
        std::time_t pastDate = std::time(nullptr) - 86400; // Yesterday
        auto invalidDate = [this, pastDate] { 
            service.addAppointment(testID, pastDate, testDesc); 
        };
        Assert::ExpectException<std::invalid_argument>(invalidDate);
    }

    // Test Add Appointment Throws for Description
    TEST_METHOD(testAddAppointmentThrowDesc) {
        auto emptyDesc = [this] { 
            service.addAppointment(testID, testDate, ""); 
        };
        Assert::ExpectException<std::invalid_argument>(emptyDesc);

        auto longDesc = [this] { 
            service.addAppointment(testID, testDate, "This description is way too long for the appointment and should throw an exception"); 
        };
        Assert::ExpectException<std::invalid_argument>(longDesc);
    }
};