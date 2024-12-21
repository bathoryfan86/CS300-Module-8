
#include <algorithm>
#include <iostream>
#include <time.h>
# include <string>
# include <vector>
# include <list>
# include <sstream>
# include <fstream>


using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

struct Course {
    string courseNumber; 
    string courseName;
    vector<string> prerequisite;
};

//============================================================================
// Static methods used for testing
//============================================================================


/**
 * Method to help parse information from the file
 */
void parseLine(vector<string> &line, vector<Course> &courses)
{
    // If the vector of strings only hold 2, there are no prerequisites
    if (line.size() == 2)
    {
        Course temp = { line[0], line[1] };
        courses.push_back(temp);
    }
    else
    {
        // Pushes the prerequisites into a vector of strings that is a member of the struct Course
        vector<string> tempPrerequisites;
        for (int i = 2; i < line.size(); i++)
        {
            tempPrerequisites.push_back(line[i]);
        }
        Course temp = { line[0],line[1], tempPrerequisites };
        courses.push_back(temp);
    }
}

/**
 * Sorts the vector by alphanumeric
 */
void sortAlphanumeric(vector<Course> &courses)
{
    Course temp;
    // Uses bubble sort to sort alphanumeric, also uses substrings to sort the characters with higher priority than numbers
    for (int i = 0; i < courses.size(); i++)
    {
        for (int j = i + 1; j < courses.size(); j++)
        {
            if (courses.at(j).courseNumber.substr(0,3) < courses.at(i).courseNumber.substr(0,3))
            {
                temp = courses.at(i);
                courses.at(i) = courses.at(j);
                courses.at(j) = temp;
            }
            else if (courses.at(j).courseNumber.substr(4, 7) < courses.at(i).courseNumber.substr(4, 7))
            {
                temp = courses.at(i);
                courses.at(i) = courses.at(j);
                courses.at(j) = temp; 
            }
        }
    }
}

/**
 * Searches through the course list that matches up with user input and prints out its information
 */
void search(vector<Course>& courses, string courseNum)
{
    bool courseExist = false; // boolean for error handling
    for (int i = 0; i < courses.size(); i++)  // iterates through vector of courses until a match is found
    {
        if (courses.at(i).courseNumber == courseNum)
        {
            courseExist = true;
            // Prints out course information alongside any prerequisites it has
            cout << endl << courses.at(i).courseNumber << ", " << courses.at(i).courseName << endl;
            if (courses.at(i).prerequisite.size() > 0)
            {
                cout << "Prerequisites: ";
                for (int j = 0; j < courses.at(i).prerequisite.size(); j++)
                {
                    cout << courses.at(i).prerequisite.at(j) << ", ";
                }
                cout << endl << endl;
            }
        }
    }
    if (courseExist == false)
    {
        cout << "Course does not exist." << endl << endl;
    }
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string filePath;
    switch (argc) {
    case 2:
        filePath = argv[1];
        break;
    default:
        filePath = "courseInformation.txt";
    }

    vector<Course> courses; // Holds all the courses information
    vector<string> temp; // Temporary vector of strings to help parse the file lines
    string line; // String to hold the information from one line in a file
    ifstream inFile;
    string input;

    int choice = 0;
    cout << "Welcome to the course planner." << endl << endl;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "What would you like to do?  ";
        cin >> choice;

        switch (choice) {

        case 1:
            if (courses.size() == 0)
            {
                inFile.open(filePath); // Opens file
                while (getline(inFile, line)) // Reads each line
                {
                    stringstream ss(line);
                    while (ss.good())
                    {
                        string substr;
                        getline(ss, substr, ','); // Splits the string by ","
                        temp.push_back(substr); // Pushes the substrings into a vector string
                    }
                    parseLine(temp, courses); // Reads the line and pushes the information into the courses vector
                    temp.clear(); // Clears the line
                }
                sortAlphanumeric(courses); // Sorts the courses vector alphanumerically
            }
            else
            {
                cout << "Data already loaded" << endl << endl;
            }
            break;

        case 2:
            if (courses.size() > 0)
            {
                cout << "Here is a sample schedule:" << endl << endl;
                // Iterates through the already sorted courses and prints out its information
                for (int i = 0; i < courses.size(); i++)
                {
                    cout << courses.at(i).courseNumber << ", " << courses.at(i).courseName << endl;
                }
                cout << endl;
            }
            else
            {
                cout << "Data not loaded" << endl << endl;
            }
            break;

        case 3:
            if (courses.size() > 0)
            {
                cout << "What course do you want to know about?" << endl;
                cin >> input;
                for (auto& c : input) c = toupper(c); // Converts input to all uppercase to help with searching
                search(courses, input); // Searches through courses for a match 
            }
            else
            {
                cout << "Data not loaded" << endl << endl;;
            }
            break;
        default: 
            cout << "Invalid input." << endl; // Error handling
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    cout << "Thank you for using the course planner!" << endl;

    return 0;
}
