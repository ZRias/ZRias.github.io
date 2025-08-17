//============================================================================
// Name        : Brea_AlgorithmsDataStructures.cpp
// Author      : Zachary Brea
// Version     : 2.0 
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const unsigned int DEFAULT_SIZE = 179;

struct Course {
    string courseId;
    string title;
    vector<string> prereq;
};

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
    cout << course.courseId << ", " << course.title << endl << "Prerequisites: ";
    if (course.prereq.empty()) {
        cout << "None";
    }
    else {
        for (int i = 0; i < course.prereq.size(); ++i) {
            cout << course.prereq[i];
            if (i < course.prereq.size() - 1) cout << ", ";
        }
    }
    cout << endl;
}

/**
 * Define a class containing data members and methods to
 * implement a hash table with open addressing
 */
class HashTable {
private:
    vector<Course> table;
    vector<string> courseIDs;
    unsigned int tableSize = DEFAULT_SIZE;
    unsigned int hash(string key);

public:
    HashTable();
    HashTable(unsigned int size);
    void Insert(Course course);
    Course Search(string courseId);
    void PrintAll();
    void loadCourseIDs(string csvPath);
    vector<string> getCourseIDs();
};


/**
 * Default constructor
 */
HashTable::HashTable() {
    table.resize(tableSize);
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
    tableSize = size;
    table.resize(tableSize);
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
    unsigned int sum = 0;
    for (char ch : key) {
        sum += static_cast<unsigned int>(ch);
    }
    return sum % tableSize;
}

/**
 * Insert a course
 *
 * @param course The course to insert
 */
void HashTable::Insert(Course course) {
    unsigned int key = hash(course.courseId);
    unsigned int start = key;
    while (!table[key].courseId.empty()) {
        key = (key + 1) % tableSize;
        if (key == start) return; // table full
    }
    table[key] = course;
}

/**
 * Search for the specified courseId
 *
 * @param courseId The course id to search for
 */
Course HashTable::Search(string courseId) {
    unsigned int key = hash(courseId);
    unsigned int start = key;
    while (!table[key].courseId.empty()) {
        if (table[key].courseId == courseId) {
            return table[key];
        }
        key = (key + 1) % tableSize;
        if (key == start) break;
    }
    return Course();
}

//determines the length of the longest course ID in the list
static int getMaxCourseIdLength(const vector<Course>& courses) {
    int maxLen = 0;
    for (const auto& course : courses) {
        if (course.courseId.length() > maxLen) {
            maxLen = course.courseId.length();
        }
    }
    return maxLen;
}

//pads courseId strings to equal length using leading spaces for proper radix sorting
void padCourseIds(vector<Course>& courses, int maxLen) {
    for (auto& course : courses) {
        while (course.courseId.length() < maxLen) {
            course.courseId = " " + course.courseId;
        }
    }
}

//performs a counting sort based on a single character index in courseId
void countingSortByChar(vector<Course>& courses, int index) {
    vector<vector<Course>> buckets(256);
    for (const auto& course : courses) {
        unsigned char ch = (index < course.courseId.length()) ? course.courseId[index] : ' ';
        buckets[ch].push_back(course);
    }
    courses.clear();
    for (const auto& bucket : buckets) {
        for (const auto& course : bucket) {
            courses.push_back(course);
        }
    }
}

//radix sort for course ids using character by character sorting
void radixSortByCourseId(vector<Course>& courses) {
    int maxLen = getMaxCourseIdLength(courses);
    padCourseIds(courses, maxLen);
    for (int i = maxLen - 1; i >= 0; --i) {
        countingSortByChar(courses, i);
    }
    // Remove leading padding spaces from courseId
    for (auto& course : courses) {
        course.courseId.erase(0, course.courseId.find_first_not_of(' '));
    }
}

//prints all courses in alphanumeric order by course ID using radix sort for strings
void HashTable::PrintAll() {
    vector<Course> sortedCourses;
    for (const auto& course : table) {
        if (!course.courseId.empty()) {
            sortedCourses.push_back(course);
        }
    }
    radixSortByCourseId(sortedCourses);

    cout << "CourseID, Title" << endl;

    for (const auto& course : sortedCourses) {
        cout << course.courseId << ", " << course.title << endl;
    }
}

/*
 * Get first variable from csv file
 * and input into courseIDs vector
 *
 * @param string csvPath path to get information
 */
void HashTable::loadCourseIDs(string csvPath) {
    ifstream iFile(csvPath);
    string line;
    while (getline(iFile, line)) {
        int comma = line.find(',');
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

    //skip title line in csv file
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