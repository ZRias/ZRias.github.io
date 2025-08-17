#include "pch.h"
#include "CppUnitTest.h"
#include "Source/src/TaskService.h"

#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Test class
TEST_CLASS(TaskServiceTest) {
public:

    //testing variables
    std::string testID = "12345";
    std::string testName = "Task Name";
    std::string testDescription = "This is the description for the task";

    //map of tasks
    TaskService tasks;

    //Test Add Task Method
    TEST_METHOD(testAddTask) {

        //add sample task
        tasks.addTask(testID, testName, testDescription);

        //test if ID name and description are correct
        Assert::AreEqual(tasks.getTask(testID).getID(), testID);
        Assert::AreEqual(tasks.getTask(testID).getName(), testName);
        Assert::AreEqual(tasks.getTask(testID).getDescription(), testDescription);
    }

    //Test Delete Task Method
    TEST_METHOD(testDeleteTask) {

        //add sample task
        tasks.addTask(testID, testName, testDescription);

        //ensure task is added
        try {
            Task test = tasks.getTask(testID);
            Assert::IsTrue(true);
        }
        catch (...) {
            Assert::Fail(L"Threw unexepected exception");
        }

        //delete task using ID
        tasks.deleteTask(testID);

        //ensure task is deleted if not fail test
        try {
            tasks.getTask(testID);
            Assert::Fail(L"Should have thrown exception for deleted task");
        } 
        catch (const std::out_of_range&) {
            Assert::IsTrue(true);
        }
        catch (...) {
            Assert::Fail(L"Threw unexepected exception");
        }
        
    }


    //Test Update Task Method
    TEST_METHOD(testUpdateTask) {

        //new sample test variables
        std::string newName = "New Task Name";
        std::string newDescription = "New Task Description";


        //add sample task
        tasks.addTask(testID, testName, testDescription);

        //update sample task
        tasks.updateTask(testID, newName, newDescription);

        //test if name and description are correct
        Assert::AreEqual(tasks.getTask(testID).getName(), newName);
        Assert::AreEqual(tasks.getTask(testID).getDescription(), newDescription);
    }

    //test Name and Description Setters
    TEST_METHOD(testTaskSetters) {

        //new sample test variables
        std::string newName = "New Task Name";
        std::string newDescription = "New Task Description";

        //add sample task
        tasks.addTask(testID, testName, testDescription);

        //update sample task name and description using setters
        tasks.updateTaskName(testID, newName);
        tasks.updateTaskDescription(testID, newDescription);

        //test if name and description are correct
        Assert::AreEqual(tasks.getTask(testID).getName(), newName);
        Assert::AreEqual(tasks.getTask(testID).getDescription(), newDescription);

    }

    //Test Add Task Throw ID both cases
    TEST_METHOD(testAddTaskThrowID) {
        
        //get result of add task using empty ID
        auto noIDGiven = [this] {tasks.addTask("", "Task Name", "This is the description for the task");};
        
        //test if result threw invalid argument
        Assert::ExpectException<std::invalid_argument>(noIDGiven);

        //get result of add task using too long ID
        auto tooLongIDGiven = [this] {tasks.addTask("12345678901", "Task Name", "This is the description for the task");};
        
        //test if result threw invalid argument
        Assert::ExpectException<std::invalid_argument>(tooLongIDGiven);
    }
};