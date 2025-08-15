#include <iostream>
#include <fstream>  // for file handling
using namespace std;

const int MAX_COURSES = 100;
const int MAX_SEMESTERS = 12;

// Function to validate and input a float (grade)
float inputValidGrade(int courseIndex) {
    float grade;
    while (true) {
        cout << "  Course " << courseIndex + 1 << " grade (0.0 to 4.0): ";
        cin >> grade;
        if (cin.fail() || grade < 0.0 || grade > 4.0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  Invalid grade! Try again.\n";
        } else {
            break;
        }
    }
    return grade;
}

// Function to validate and input a positive integer (credits or courses)
int inputPositiveInt(string prompt, int maxValue = 1000) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0 || value > maxValue) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  Invalid input! Try again.\n";
        } else {
            break;
        }
    }
    return value;
}

// Function to input one semester's data and return total grade points and credits
void inputSemesterData(int semesterIndex, float &semesterPoints, int &semesterCredits) {
    float grades[MAX_COURSES];
    int credits[MAX_COURSES];

    cout << "\n--- Semester " << semesterIndex + 1 << " ---\n";
    int numCourses = inputPositiveInt("Enter number of courses: ", MAX_COURSES);

    semesterPoints = 0;
    semesterCredits = 0;

    for (int i = 0; i < numCourses; i++) {
        grades[i] = inputValidGrade(i);
        credits[i] = inputPositiveInt("  Course " + to_string(i + 1) + " credit hours: ");
        semesterPoints += grades[i] * credits[i];
        semesterCredits += credits[i];
    }

    float gpa = (semesterCredits == 0) ? 0 : semesterPoints / semesterCredits;
    cout << "Semester GPA: " << gpa << "\n";
}

// Function to write the results to a file
void saveToFile(const float semesterPoints[], const int semesterCredits[], int totalSemesters, float finalCGPA) {
    ofstream fout("cgpa_report.txt");

    if (!fout) {
        cout << "\nError: Unable to create file.\n";
        return;
    }

    fout << "========= CGPA Report =========\n";
    for (int i = 0; i < totalSemesters; i++) {
        float gpa = (semesterCredits[i] == 0) ? 0 : semesterPoints[i] / semesterCredits[i];
        fout << "Semester " << i + 1 << ": GPA = " << gpa << endl;
    }
    fout << "\nOverall CGPA: " << finalCGPA << endl;

    fout.close();
    cout << "\nReport saved to file: cgpa_report.txt\n";
}

// Main function
int main() {
    int totalSemesters = inputPositiveInt("Enter number of semesters: ", MAX_SEMESTERS);

    float allSemesterPoints[MAX_SEMESTERS];
    int allSemesterCredits[MAX_SEMESTERS];

    float grandTotalPoints = 0;
    int grandTotalCredits = 0;

    for (int i = 0; i < totalSemesters; i++) {
        float points;
        int credits;
        inputSemesterData(i, points, credits);
        allSemesterPoints[i] = points;
        allSemesterCredits[i] = credits;
        grandTotalPoints += points;
        grandTotalCredits += credits;
    }

    float cgpa = (grandTotalCredits == 0) ? 0 : grandTotalPoints / grandTotalCredits;

    cout << "\n=========== Final Summary ===========\n";
    for (int i = 0; i < totalSemesters; i++) {
        float gpa = (allSemesterCredits[i] == 0) ? 0 : allSemesterPoints[i] / allSemesterCredits[i];
        cout << "Semester " << i + 1 << ": GPA = " << gpa << endl;
    }
    cout << "\nOverall CGPA: " << cgpa << endl;

    // Save to file
    saveToFile(allSemesterPoints, allSemesterCredits, totalSemesters, cgpa);

    return 0;
}
