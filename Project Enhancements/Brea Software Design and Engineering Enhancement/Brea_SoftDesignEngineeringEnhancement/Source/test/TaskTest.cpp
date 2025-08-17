
#include "pch.h"
#include "CppUnitTest.h"
#include "Source/src/Task.h"

#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Test class
TEST_CLASS(TaskTest) {
public:

    //testing variables
    std::string testID = "12345";
    std::string testName = "Task Name";
    std::string testDescription = "This is the description for the task";
    
    //sample object for testing
    Task* task;
    
    //Initialize task object
    TEST_METHOD_INITIALIZE(initializeObject)
    {
        
        task = new Task(testID, testName, testDescription);
    }

    //Test Object Initialization Equal
    TEST_METHOD(testObjectCreation) {

        //Test all 3 Object Variables
        Assert::AreEqual(task->getID(), testID);
        Assert::AreEqual(task->getName(), testName);
        Assert::AreEqual(task->getDescription(), testDescription);

    }

    //Test Object Constructor Throw ID
    TEST_METHOD(testObjectThrowID) {

        //get result of creating new object using empty ID
        auto noIDGiven = [] {Task emptyID("", "Task Name", "This is the description for the task");};
        
        //test if result threw invalid argument

        Assert::ExpectException<std::invalid_argument>(noIDGiven);

        //get result of creating new object using too long ID
        auto tooLongIDGiven = [] {Task tooLongID("12345678901", "Task Name", "This is the description for the task");};
        
        //test if result threw invalid argument

        Assert::ExpectException<std::invalid_argument>(tooLongIDGiven);
    }

    //Test Object Constructor Throw Name
    TEST_METHOD(testObjectThrowName) {
        
        //get result of creating new object using empty name
        auto noNameGiven = [] {Task emptyID("12345", "", "This is the description for the task");};
        
        //test if result threw invalid argument
        Assert::ExpectException<std::invalid_argument>(noNameGiven);
        
        //get result of creating new object too long name
        auto tooLongNameGiven = [] {Task tooLongID("123451", "Task Name is way too long for this test", "This is the description for the task");};
        
        //test if result threw invalid argument
        Assert::ExpectException<std::invalid_argument>(tooLongNameGiven);
    }

    //Test Object Constructor Throw Description
    TEST_METHOD(testObjectThrowDescription) {
        
        //get result of creating new object using empty Description
        auto noDescriptionGiven = [] {Task emptyID("12345", "Task Name", "");};
        
        //test if result threw invalid argument
        Assert::ExpectException<std::invalid_argument>(noDescriptionGiven);
        
        //get result of creating new object too long Description
        auto tooLongDescriptionGiven = [] {Task tooLongID("123451", "Task Name", "This task description is too long for the description for the task for this test");};
        
        //test if result threw invalid argument
        Assert::ExpectException<std::invalid_argument>(tooLongDescriptionGiven);
    }

    //Test Object Setters Equal
    TEST_METHOD(testObjectSetters) {

        //Create new variables
        std::string newName = "New Task Name";
        std::string newDescription = "New description";

        //Set new variables
        task->setName(newName);
        task->setDescription(newDescription);

        //Should both be equal
        Assert::AreEqual(task->getName(), newName);
        Assert::AreEqual(task->getDescription(), newDescription);
    }

    //Test Object Name Setter Invalid Argument Result
    TEST_METHOD(testNameSetterThrow) {

        //No task name given
        Assert::ExpectException<std::invalid_argument>(
            [this]() {task->setName(""); }
        );

        //Task Name is way too long
        Assert::ExpectException<std::invalid_argument>(
            [this]() {task->setName("Task Name is way too long for this test"); }
        );
    }

    //Test Object Description Setter Invalid Argument Result
    TEST_METHOD(testDescriptionSetterThrow) {

        //No description given
        Assert::ExpectException<std::invalid_argument>(
            [this]() {task->setDescription(""); }
        );

        //Description is way too long
        Assert::ExpectException<std::invalid_argument>(
            [this]() {task->setName("This task description is too long for the description for the task for this test"); }
        );
    }

    //test ID getter
    TEST_METHOD(testGetterID) {

        Assert::AreEqual(task->getID(), testID);
    }

    //test name getter
    TEST_METHOD(testGetterName) {

        Assert::AreEqual(task->getName(), testName);
    }

    //test description getter
    TEST_METHOD(testGetterDescription) {

        Assert::AreEqual(task->getDescription(), testDescription);
    }
};