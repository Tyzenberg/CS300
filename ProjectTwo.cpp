// ProjectTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

// build course structure
struct course {
    double key;
    string courseID;
    string Name;
    vector<string> prerequisites;

    course() {}
};

// vector to hold courses
vector<course> courses;

// function to turn courseID into a key
// used for sorting
double getKey(string courseID) {
    double newKey = 0;
    int tmp;

    // input size validation
    if (courseID.size() != 7) {
        cout << endl << "CourseID is incorrect length" << endl;
        return 0;                       // return key as 0 for error handling
    }

    // convert subject string into an ASCII string
    for (int i = 0; i < courseID.size(); i++) {
        tmp = courseID.at(i) - 0;

        // input validation (0-9 or uppercase A-Z)
        if (!(tmp > 47 && tmp < 58) && !(tmp > 64 && tmp < 91)) {
            cout << endl << "Invalid character in course ID" << endl;
            return 0;                   // return key as 0 for error handling
        }

        // attach tmp value to end of newKey
        newKey = newKey * 100;
        newKey = newKey + tmp;

    }

    return newKey;
}

// create a new course
course newCourse(vector<string> details) {
    course newCourse;
    newCourse.courseID = details.at(0);
    newCourse.Name = details.at(1);
    newCourse.key = getKey(newCourse.courseID);

    // add prerequisites
    int i = 2;
    for (i; i < details.size(); i++) {
        newCourse.prerequisites.push_back(details.at(i));
    }
    return newCourse;
}

// add a course to the main array
// takes concept of binary search, but checks min and max instead of mid
void insertCourse(course course) {

    // if there are no courses, add course
    if (courses.size() == 0) {
        courses.push_back(course);
        return;
    }

    // if course key is smaller than first course, insert at begining
    else if (course.key < courses.at(0).key) {
        courses.insert(courses.begin(), course);
        return;
    }

    // if course is larger than last course, insert at end
    else if (course.key > courses.at(courses.size() - 1).key) {
        courses.push_back(course);
        return;
    }

    // course is larger than min and smaller than max
    // run through algorithm
    else {
        int min = 1;                            // start at second index as first was already checked
        int max = courses.size() - 2;           // start at second to last as last was already checked
        int mid = min + (max - min) / 2;

        // "outer binary insert" while array segment is large
        while (max - min > 4) {
            // if course is bigger than max, place course after max
            if (course.key > courses.at(max).key) {
                courses.insert(courses.begin() + max + 1, course);
                return;
            }
            // if course is smaller than min, place before min
            else if (course.key < courses.at(min).key) {
                courses.insert(courses.begin() + min, course);
                return;
            }
            // else, split array and repeat
            else {
                if (course.key > courses.at(mid).key) {
                    min = mid+1;            // if bigger than mid, we don't need to compare to mid again
                    max--;                  // if smaller than max, we don't need to check max again
                }
                else {
                    min++;                  // if larger than min, we don't need to check min again
                    max = mid-1;            // if smaller than mid, we don't need to check mid again
                }
            }
            mid = min + (max - min) / 2;
        }

        // array is now small enough for a "linear sort insert"
        while (course.key > courses.at(min).key) {
            min++;
        }

        courses.insert(courses.begin() + min, course);
        return;
    }

    cout << endl << "!! code logic is broke. Course " << course.courseID << " was not added, blame developer !!" << endl;
    return;
}

// recursive binary search function
int binarySearch(double searchKey, int min, int max) {

    // is search key min
    if (searchKey == courses.at(min).key) {
        return min;
    }

    // is search key max
    else if (searchKey == courses.at(max).key) {
        return max;
    }

    // if there are 2 or less elements and min/max didn't match, course was not found
    else if (max - min < 2) {
        return -1;
    }

    // get mid and compare
    int mid = min + (max - min) / 2;
    if (searchKey == courses.at(mid).key) {
        return mid;
    }
    else if (searchKey < courses.at(mid).key) {
        return binarySearch(searchKey, min+1, mid);     // we know course isn't min, no need to double check
    }
    else {
        return binarySearch(searchKey, mid, max-1);     // we know course isn't max, no need to double check
    }

}

// function to split a string into an array
vector<string> splitString(const string& line) {
    string segment;
    stringstream streamLine(line);
    vector<string> parsedLine;

    while (getline(streamLine, segment, ',')) {
        if (segment.compare("") != 0) {
            parsedLine.push_back(segment);
        }
    }

    return parsedLine;
}

// parse csv file and import to courses vector
void readFile(string fName) {
    string fLine = "";
    vector<string> parsedLine = {};

    // check for  and remove qutation marks
    if (fName.at(0) == 34) {
        fName.erase(fName.begin());
    }
    if (fName.at(fName.size()-1) == 34) {
        fName.erase(fName.begin() + fName.size()-1);
    }
    
    // check if filename is too small
    if (fName.size() < 4) {
        cout << endl << "!!! invalid input !!!" << endl;
        return;
    }

    // verify file is a csv
    else if (fName.substr(fName.size() - 4) != ".csv") {
        cout << endl << "!!! input file must be a CSV !!!" << endl;
        return;
    }

    // open file and verify 
    ifstream file(fName);
    if (!file.is_open()) {
        cout << "An unexpected error occured while opening " << fName << endl;
        return;
    }

    // parse each line and convert to a course
    while (getline(file, fLine, '\n')) {
        parsedLine = splitString(fLine);

        if (parsedLine.size() < 2) {
            cout << endl << "At least one course is not formatted correctly." << endl;
            cout << "Please check format of file." << endl;
            cout << "Ending import, some courses may have been imported successfully." << endl;
            cout << "Use 'Display all courses' to see which courses were imported." << endl;
            return;
        }

        course newcourse = newCourse(parsedLine);
        // error handling if courseID was incorrect
        if (newcourse.key == 0) {
            cout << endl << "At least one course is not formatted correctly." << endl;
            cout << "Please check format of file." << endl;
            cout << "Ending import, some courses may have been imported successfully." << endl;
            cout << "Use 'Display all courses' to see which courses were imported." << endl;
            return;
        }
        
        // file format seems okay
        insertCourse(newcourse);
    }
}

// template for displaying course information
void displayCourse(course course) {
    cout << course.courseID << " - " << course.Name;
    if (course.prerequisites.size() > 0) {
        cout << " - Prerequisites:";
        for (int i = 0; i < course.prerequisites.size(); i++) {
            cout << " " << course.prerequisites.at(i);
        }
    }
    cout << endl;
}

// display all courses
void displayAll() {
    for (int i = 0; i < courses.size(); i++) {
        displayCourse(courses.at(i));
    }
}

// find a course
void findCourse(string searchID) {
    double searchKey = getKey(searchID);
    // cancel if course ID format is incorrect
    if (searchKey == 0) {
        return;
    }
    else {
        int courseIndex = binarySearch(searchKey, 0, courses.size() - 1);
        if (courseIndex < 0) {
            cout << endl << searchID << " was not found." << endl;
        }
        else {
            displayCourse(courses.at(courseIndex));
        }
        return;
    }
}

int main()
{
    int userChoice = 0;
    string fileName = "";
    string courseID;

    // intro to application
    cout << endl << "Welcome to ABCU's course database";
    cout << endl << "Please select an option below:";
    cout << endl << endl;

    while (userChoice != 9) {
        
        // Menu UI
        cout << endl;
        cout << "1) Load Data" << endl;
        cout << "2) Display all courses" << endl;
        cout << "3) Get course information" << endl;
        cout << "9) Exit" << endl;
        cout << endl;

        // Handle user's choice
        cin >> userChoice;

        // validate user input
        if (!userChoice) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << endl << "!!! invalid input !!!" << endl << endl;
        }

        else {
            switch (userChoice) {
            case 1:
                // load csv
                cout << endl << "Specify CSV file to import. File must be a CSV. Must include file path" << endl;
                cout << "File to import:" << endl;
                cin.ignore();
                getline(cin, fileName);
                readFile(fileName);
                break;

            case 2:
                // display all bids
                // alert if no courses exist
                if (courses.size() == 0) {
                    cout << endl << "No courses have been entered" << endl;
                }
                else {
                    displayAll();
                }
                break;

            case 3:
                // search course
                // alert if no courses exist
                if (courses.size() == 0) {
                    cout << endl << "No courses have been entered" << endl;
                }
                else {
                    cout << endl << "Enter Course ID:" << endl;
                    cin >> courseID;
                    findCourse(courseID);
                }
                break;

            case 9:
                //exit
                break;

            default:
                cout << endl << "!!! " << userChoice << " is not a valid option !!!" << endl << endl;
            }
        }

    }

    // always be polite
    cout << endl << "Goodbye." << endl;
}