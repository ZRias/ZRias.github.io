#include "CppUnitTest.h"
#include "Source/src/Contact.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(ContactTest) {
public:
    // Testing variables
    std::string testID = "12345";
    std::string testFirstName = "John";
    std::string testLastName = "Doe";
    std::string testPhone = "1234567890";
    std::string testAddress = "123 Main St";

    // Sample object for testing
    Contact* contact;

    // Initialize contact object
    TEST_METHOD_INITIALIZE(initializeObject) {
        contact = new Contact(testID, testFirstName, testLastName, testPhone, testAddress);
    }

    // Test Object Initialization
    TEST_METHOD(testObjectCreation) {
        Assert::AreEqual(contact->getID(), testID);
        Assert::AreEqual(contact->getFirstName(), testFirstName);
        Assert::AreEqual(contact->getLastName(), testLastName);
        Assert::AreEqual(contact->getPhone(), testPhone);
        Assert::AreEqual(contact->getAddress(), testAddress);
    }

    // Test Object Constructor Throws for ID
    TEST_METHOD(testObjectThrowID) {
        auto emptyID = [] { Contact noID("", "John", "Doe", "1234567890", "123 Main St"); };
        Assert::ExpectException<std::invalid_argument>(emptyID);

        auto longID = [] { Contact tooLongID("12345678901", "John", "Doe", "1234567890", "123 Main St"); };
        Assert::ExpectException<std::invalid_argument>(longID);
    }

    // Test Object Constructor Throws for First Name
    TEST_METHOD(testObjectThrowFirstName) {
        auto emptyFirstName = [] { Contact noFirstName("12345", "", "Doe", "1234567890", "123 Main St"); };
        Assert::ExpectException<std::invalid_argument>(emptyFirstName);

        auto longFirstName = [] { Contact tooLongFirstName("12345", "JohnathanDoe", "Doe", "1234567890", "123 Main St"); };
        Assert::ExpectException<std::invalid_argument>(longFirstName);
    }

    // Test Object Constructor Throws for Last Name
    TEST_METHOD(testObjectThrowLastName) {
        auto emptyLastName = [] { Contact noLastName("12345", "John", "", "1234567890", "123 Main St"); };
        Assert::ExpectException<std::invalid_argument>(emptyLastName);

        auto longLastName = [] { Contact tooLongLastName("12345", "John", "DoeDoeDoeDoe", "1234567890", "123 Main St"); };
        Assert::ExpectException<std::invalid_argument>(longLastName);
    }

    // Test Object Constructor Throws for Phone
    TEST_METHOD(testObjectThrowPhone) {
        auto emptyPhone = [] { Contact noPhone("12345", "John", "Doe", "", "123 Main St"); };
        Assert::ExpectException<std::invalid_argument>(emptyPhone);

        auto invalidPhone = [] { Contact not10Phone("12345", "John", "Doe", "12345", "123 Main St"); };
        Assert::ExpectException<std::invalid_argument>(invalidPhone);
    }

    // Test Object Constructor Throws for Address
    TEST_METHOD(testObjectThrowAddress) {
        auto emptyAddress = [] { Contact noAddress("12345", "John", "Doe", "1234567890", ""); };
        Assert::ExpectException<std::invalid_argument>(emptyAddress);

        auto longAddress = [] { Contact tooLongAddress("12345", "John", "Doe", "1234567890", "123 Main Street, Apartment 456, City, State 12345"); };
        Assert::ExpectException<std::invalid_argument>(longAddress);
    }

    // Test Object Setters
    TEST_METHOD(testObjectSetters) {
        std::string newFirstName = "Jane";
        std::string newLastName = "Smith";
        std::string newPhone = "0987654321";
        std::string newAddress = "456 Oak Ave";

        contact->setFirstName(newFirstName);
        contact->setLastName(newLastName);
        contact->setPhone(newPhone);
        contact->setAddress(newAddress);

        Assert::AreEqual(contact->getFirstName(), newFirstName);
        Assert::AreEqual(contact->getLastName(), newLastName);
        Assert::AreEqual(contact->getPhone(), newPhone);
        Assert::AreEqual(contact->getAddress(), newAddress);
    }

    // Test First Name Setter Throws
    TEST_METHOD(testFirstNameSetterThrow) {
        Assert::ExpectException<std::invalid_argument>([this]() { contact->setFirstName(""); });
        Assert::ExpectException<std::invalid_argument>([this]() { contact->setFirstName("JohnathanDoe"); });
    }

    // Test Last Name Setter Throws
    TEST_METHOD(testLastNameSetterThrow) {
        Assert::ExpectException<std::invalid_argument>([this]() { contact->setLastName(""); });
        Assert::ExpectException<std::invalid_argument>([this]() { contact->setLastName("DoeDoeDoeDoe"); });
    }

    // Test Phone Setter Throws
    TEST_METHOD(testPhoneSetterThrow) {
        Assert::ExpectException<std::invalid_argument>([this]() { contact->setPhone(""); });
        Assert::ExpectException<std::invalid_argument>([this]() { contact->setPhone("12345"); });
    }

    // Test Address Setter Throws
    TEST_METHOD(testAddressSetterThrow) {
        Assert::ExpectException<std::invalid_argument>([this]() { contact->setAddress(""); });
        Assert::ExpectException<std::invalid_argument>([this]() { contact->setAddress("123 Main Street, Apartment 456, City, State 12345"); });
    }

    // Clean up
    TEST_METHOD_CLEANUP(cleanup) {
        delete contact;
    }
};