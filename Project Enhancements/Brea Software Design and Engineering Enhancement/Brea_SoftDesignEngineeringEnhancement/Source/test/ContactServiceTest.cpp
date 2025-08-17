#include "pch.h"
#include "CppUnitTest.h"
#include "Source/src/ContactService.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(ContactServiceTest) {
public:
    // Testing variables
    std::string testID = "12345";
    std::string testFirstName = "John";
    std::string testLastName = "Doe";
    std::string testPhone = "1234567890";
    std::string testAddress = "123 Main St";

    // Service instance
    ContactService service;

    // Test Add Contact Method
    TEST_METHOD(testAddContact) {
        service.addContact(testID, testFirstName, testLastName, testPhone, testAddress);
        
        Contact contact = service.getContact(testID);
        Assert::AreEqual(contact.getID(), testID);
        Assert::AreEqual(contact.getFirstName(), testFirstName);
        Assert::AreEqual(contact.getLastName(), testLastName);
        Assert::AreEqual(contact.getPhone(), testPhone);
        Assert::AreEqual(contact.getAddress(), testAddress);
    }

    // Test Remove Contact Method
    TEST_METHOD(testRemoveContact) {
        service.addContact(testID, testFirstName, testLastName, testPhone, testAddress);
        
        // Verify contact exists
        try {
            Contact contact = service.getContact(testID);
            Assert::IsTrue(true);
        }
        catch (...) {
            Assert::Fail(L"Unexpected exception");
        }

        // Remove contact
        service.removeContact(testID);

        // Verify contact was removed
        try {
            service.getContact(testID);
            Assert::Fail(L"Should have thrown exception for removed contact");
        }
        catch (const std::out_of_range&) {
            Assert::IsTrue(true);
        }
        catch (...) {
            Assert::Fail(L"Unexpected exception");
        }
    }

    // Test Update Methods
    TEST_METHOD(testUpdateMethods) {
        std::string newFirstName = "Jane";
        std::string newLastName = "Smith";
        std::string newPhone = "0987654321";
        std::string newAddress = "456 Oak Ave";

        service.addContact(testID, testFirstName, testLastName, testPhone, testAddress);
        
        service.updateContactFirstName(testID, newFirstName);
        service.updateContactLastName(testID, newLastName);
        service.updateContactPhone(testID, newPhone);
        service.updateContactAddress(testID, newAddress);

        Contact contact = service.getContact(testID);
        Assert::AreEqual(contact.getFirstName(), newFirstName);
        Assert::AreEqual(contact.getLastName(), newLastName);
        Assert::AreEqual(contact.getPhone(), newPhone);
        Assert::AreEqual(contact.getAddress(), newAddress);
    }

    // Test Add Contact Throws for ID
    TEST_METHOD(testAddContactThrowID) {
        auto emptyID = [this] { service.addContact("", "John", "Doe", "1234567890", "123 Main St"); };
        Assert::ExpectException<std::invalid_argument>(emptyID);

        auto longID = [this] { service.addContact("12345678901", "John", "Doe", "1234567890", "123 Main St"); };
        Assert::ExpectException<std::invalid_argument>(longID);
    }
};