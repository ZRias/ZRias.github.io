//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Zachary Brea
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Project Two
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// define a structure to hold course information
struct Course {
    string courseId; // unique identifier
    string title;
    vector <string> prereq;
    Course() {

    }
};

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
    cout << course.courseId << ", " << course.title << endl << "Prerequisites: ";

    int len = course.prereq.size();
    if (len > 0) {
        for (int i = 0; i < len; i++) {
            cout << course.prereq[i];
            if (i != len - 1) {
                cout << ", ";
            }
        }
    } else {
        cout << "None";
    }

    cout << endl;

    return;
}

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // Define structures to hold courses
    struct Node {
        Course course;
        unsigned int key;
        Node *next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // initialize with a course
        Node(Course aCourse) : Node() {
            course = aCourse;
        }

        // initialize with a course and a key
        Node(Course aCourse, unsigned int aKey) : Node(aCourse) {
            key = aKey;
        }
    };

    vector<Node> nodes;

    vector<string> courseIDs;

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(string key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Course course);
    void PrintAll();
    Course Search(string courseId);
    int partition(vector<Course>& courses, int begin, int end);
    void quickSort(vector<Course>& courses, int begin, int end);
    void loadCourseIDs(string csvPath);
    vector<string> getCourseIDs();
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    // DONE: Implemented the structures used to hold courses
    // Initalize node structure by resizing tableSize
    nodes.resize(tableSize);
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
    // invoke local tableSize to size with this->
    // resize nodes size
    this->tableSize = size;
    nodes.resize(tableSize);
}


/**
 * Destructor
 */
HashTable::~HashTable() {
    // DONE: Implemented logic to free storage when class is destroyed
    // erase nodes beginning
    for (int i = 0; i < tableSize; i++) {
        Node* node = &nodes[i];
        while (node != nullptr) {
            Node* temp = node;
            node = node->next;
            delete temp;
        }
    }
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(string key) {
    // DONE: Implemented logic to calculate a hash value
    
    int sum = 0;

    //convert string to numerical value
    for (int i = 0; i < key.length(); i++) {
        sum = sum + int(key[i]);
    }

    // return sum modulo tableSize
    return sum % tableSize;
}

/**
 * Insert a course
 *
 * @param course The course to insert
 */
void HashTable::Insert(Course course) {
    // DONE: Implemented logic to insert a course
    // create the key for the given course
    unsigned int key = hash(course.courseId);
    // retrieve node using key
    Node* keyNode = &nodes[key];
    // if no entry found for the key
    if (keyNode == nullptr) {
        // assign this node to the key position
        keyNode = new Node(course, key);
        keyNode->next = nullptr;
    // else if node is not used
    } else if (keyNode->key == UINT_MAX) {
        // assing old node key to UNIT_MAX, set to key, set old node to course and old node next to null pointer
        keyNode->key = key;
        keyNode->course = course;
        keyNode->next = nullptr;

    // else find the next open node
    } else {
        // add new newNode to end
        while (keyNode->next != nullptr) {
            keyNode = keyNode->next;
        }
        keyNode->next = new Node(course, key);
    }
}

/**
 * Print all courses
 */
void HashTable::PrintAll() {
    // DONE: Implemented logic to print all courses
    vector <Course> sortedList;
    for (auto& node : nodes) {// for node begin to end iterate

        if (node.key != UINT_MAX) {//if key not equal to UINT_MAX

            //add to vector to be sorted
            sortedList.push_back(node.course);

            // node is equal to next iter
            Node* nextNode = node.next;

            while (nextNode != nullptr) {// while node not equal to nullptr
                //add to vector to be sorted
                sortedList.push_back(nextNode->course);
                // node is equal to next node
                nextNode = nextNode->next;
            }
        }
    }

    //sort list
    quickSort(sortedList, 0, sortedList.size() - 1);

    //print list
    for (int i = 0; i < sortedList.size(); i++) {
        cout << sortedList[i].courseId << ", " << sortedList[i].title << endl;
    }
}

/**
 * Search for the specified courseId
 *
 * @param courseId The course id to search for
 */
Course HashTable::Search(string courseId) {
    Course course;

    // DONE: Implemented logic to search for and return a course

    // create the key for the given course
    unsigned int key = hash(courseId);

    Node* node = &nodes[key];

    // if entry found for the key
    while (node != nullptr && node->key != UINT_MAX) {
        if (node->course.courseId == courseId) {
            //return node course
            return node->course;
        }
        
        node = node->next;
    }
         

    // if no entry found for the key
      // return course
    return course;
}

/**
 * Partition the vector of courses into two parts, low and high
 *
 * @param courses Address of the vector<Course> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int HashTable::partition(vector<Course>& courses, int begin, int end) {
    //set low and high equal to begin and end
    int low = begin;
    int high = end;
    // Calculate the middle element as middlePoint (int)
    // Set Pivot as middlePoint element courseId to compare (string)  
    int midpoint = low + (high - low) / 2;
    string pivot = courses[midpoint].courseId;

    bool done = false;
    // while not done 
    while (!done) {
        // keep incrementing low index while courses[low].courseId < Pivot
        while (courses[low].courseId < pivot) {
            low += 1;
        }
        // keep decrementing high index while Pivot < courses[high].courseId
        while (pivot < courses[high].courseId) {
            high -= 1;
        }
        /* If there are zero or one elements remaining,
        all courses are partitioned. Return high */
        // else swap the low and high courses (built in vector method)
        // move low and high closer ++low, --high
        if (low >= high) {
            done = true;
        }
        else {
            Course temp = courses[low];
            courses[low] = courses[high];
            courses[high] = temp;

            // Update lowIndex and highIndex
            low += 1;
            high -= 1;
        }
    }
    return high;
}

/**
 * Perform a quick sort on course ID
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param courses address of the vector<Courses> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void HashTable::quickSort(vector<Course>& courses, int begin, int end) {
    //set mid equal to 0
    int mid = 0;

    /* Base case: If there are 1 or zero courses to sort,
     partition is already sorted otherwise if begin is greater
     than or equal to end then return*/
    if (courses.size() <= 1 || begin >= end) {
        return;
    }

    /* Partition courses into low and high such that
     midpoint is location of last element in low */
    int midpoint = partition(courses, begin, end);
    // recursively sort low partition (begin to mid)
    quickSort(courses, begin, midpoint);
    // recursively sort high partition (mid+1 to end)
    quickSort(courses, midpoint + 1, end);
}

/*
 * Get first variable from csv file
 * and input into courseIDs vector
 * 
 * @param string csvPath path to get information
 */
void HashTable::loadCourseIDs(string csvPath) {
    ifstream iFile;
    string line;
    int comma;
    iFile.open(csvPath);

    // loop to read rows of a CSV file
    while (getline(iFile, line)) {
        
        //get courseID
        comma = line.find(',');
        courseIDs.push_back(line.substr(0, comma));
    }
    iFile.close();
}

/*
 * return courseIDs vector
 */
vector<string> HashTable::getCourseIDs() {
    return courseIDs;
}


/*
 * Validate that ID is equal an item
 * in courseIDs vector
 *
 * @param string ID courseID to validate
 * @param vector<string> courseIDs
 */
void checkPrereqs(string ID, vector<string> courseIDs) {
    //make sure prereq is an actual course
    try {

        bool confirmCourse = false;

        //for all IDs in courseIDs
        for (string s : courseIDs) {
            //if match found
            if (ID == s) {
                confirmCourse = true;
                break;
            }
        }

        // if prerequisite not found in courseIDs
        if (!confirmCourse) {
            throw std::invalid_argument("Prerequisite course cannot be found");
        }
    }
    catch (const std::invalid_argument& e) {
        // Handle the exception
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
}

/**
 * Load a CSV file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the courses read
 */
void loadCourses(string csvPath, HashTable* hashTable) {

    // file pointer
    ifstream iFile;
    string line;
    int comma;
    iFile.open(csvPath);

    cout << "Loading CSV file " << csvPath << endl;
    getline(iFile, line);
    vector<string> courseIDs = hashTable->getCourseIDs();
    // loop to read rows of a CSV file
    while (getline(iFile, line)) {
        // Create a data structure and add to the collection of courses
        Course course;


        //get courseID
        comma = line.find(',');
        course.courseId = line.substr(0, comma);
        line = line.substr(comma + 1, line.length());

        //get course title
        comma = line.find(',');
        course.title = line.substr(0, comma);
        line = line.substr(comma + 1, line.length());

        comma = line.find(',');

        string temp;

        //get prerequisites if applicable
        while (comma > 0) {
            //get current prerequisite
            temp = line.substr(0, comma);

            //check Prerequisites method call
            checkPrereqs(temp, courseIDs);
            
            //add to prereqs
            course.prereq.push_back(temp);
            line = line.substr(comma + 1, line.length());
            comma = line.find(',');

            if (line != "" && comma < 0) {
                temp = line;

                //check Prerequisites method call
                checkPrereqs(temp, courseIDs);

                //add to prereqs
                course.prereq.push_back(line);
            }
        }
        
        //print course and applicable prerequisites

        //displayCourse(course);

        // push this course to the end
        hashTable->Insert(course);
    }

    iFile.close();

    cout << "Successfully loaded input from " << csvPath << endl;
    
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, courseKey;
    
    //get valid file for input
    while (true) {

        //prompt user for file name
        cout << "Please input a valid file name: ";
        getline(cin, csvPath);

        ifstream file(csvPath);

        // Exit loop when a valid file is found
        if (file.good()) {
            cout << "File found: " << csvPath << endl;
            break;
        }
        else {
            std::cout << "File does not exist. Try again." << endl;
        }
        
    }



    // Define a hash table to hold all the courses
    HashTable* courseTable;

    Course course;
    courseTable = new HashTable();
    
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display All Courses" << endl;
        cout << "  3. Find Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        //verify numerical input given
        while (cin.fail()) {
            cout << "Please enter a number from the menu above: " << std::endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> choice;
        }


        switch (choice) {

        case 1:

            // Complete method call to load courseIDs to verify perequisite courses
            courseTable->loadCourseIDs(csvPath);

            // Complete the method call to load the courses
            loadCourses(csvPath, courseTable);

            break;

        case 2:

            // complete method call to print all courses in alphanumeric order based on course ID
            courseTable->PrintAll();
            break;

        case 3:

            //prompt user for course ID
            cout << "Please input the course ID you want to search (ex: CSCI100): " << endl;

            //get course ID from user
            cin >> courseKey;

            //set all letters uppercase
            transform(courseKey.begin(), courseKey.end(), courseKey.begin(), ::toupper);

            //search for course based on given course ID
            course = courseTable->Search(courseKey);

            //display result
            if (!course.courseId.empty()) {
                displayCourse(course);
            }
            else {
                cout << "Course Id " << courseKey << " not found." << endl;
            }

            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
        

    }

    return 0;
}