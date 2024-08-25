#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Course {                     // These will be the datatypes I will be using to find the course
    string courseId;
    string courseName;
    vector<string> prerequisits;

};


void loadCourses(string csvPath, vector<Course>& courses) {
    ifstream file;                                    // In order for me to load the course have to use line as a string so that file will read the each line
    string prerequisit;                             // When using the cvsPath the ABCU file have to be the same name in order for the system to pull the courses.
    string line;

    file.open(csvPath);
    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;  //If file is not found then a error message will display
        return;
    }

    while (getline(file, line)) {
        Course course;
        stringstream ss(line);

        if (!getline(ss, course.courseId, ',')) {       // The loop will help the system cycle the course and chose from either courseId, courseName, etc
            cout << "Course ID is missing" << endl;
            continue;
        }
        if (!getline(ss, course.courseName, ',')) {
            cout << "Course Name is missing" << endl;
            continue;
        }
        while (getline(ss, prerequisit, ',')) {
            course.prerequisits.push_back(prerequisit);
        }
        courses.push_back(course);
    }
    cout << courses.size() << " course are loaded" << endl;     // This will display the total number of courses
    file.close();
}





void displayCourse(const Course& course) {   // This is be our option 3 where it will display the course start with courseId and if showing any prerequisits
    cout << "Course ID: " << course.courseId << ", Course Name: " << course.courseName;
    cout << "Prerequisits:";
    for (const auto& prerequisit : course.prerequisits) {
        cout << " " << prerequisit;
    }
    cout << endl;
}

int main() {
    string csvPath = "ABCU.csv";  // System will pull from the ABCU file that we have in our project.
    vector<Course> courses;
    string courseid;
    int choice = 0;

    while (choice != 9) {    // Menu Loop
        cout << "Menu:" << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {           // Load number of courses
        case 1:
            loadCourses(csvPath, courses);
            break;
        case 2:                             // Display all eight courses
            cout << "COURSES:" << endl;
            for (const auto& course : courses) {
                displayCourse(course);
            }
            break;
        case 3:                             // Print which ever course user chooses
            cout << "Enter a course id you are looking for: ";
            cin >> courseid;
            for (const auto& course : courses) {
                if (courseid == course.courseId) {
                    displayCourse(course);
                   
                }
            }
        
            break;
        case 9:
            cout << "Goodbye!" << endl;     // Exit program
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}


