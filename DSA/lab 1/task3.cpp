#include <iostream>
#include <string>
using namespace std;

class Course {
private:
    string courseCode;
    string courseName;

public:
    void inputCourse() {
        cout << "Enter course code: ";
        cin >> courseCode;
        cout << "Enter course name: ";
        cin.ignore();
        getline(cin, courseName);
    }

    void displayCourse() const {
        cout << "Course: " << courseCode << " - " << courseName << endl;
    }
};

class Grade {
private:
    int mark;
    char theGrade;
    bool finalized;

    void calculateGrade() {
        if (mark > 69) theGrade = 'A';
        else if (mark > 59) theGrade = 'B';
        else if (mark > 49) theGrade = 'C';
        else if (mark > 39) theGrade = 'D';
        else theGrade = 'E';
    }

public:
    Grade() : mark(0), theGrade('F'), finalized(false) {}

    void inputMark() {
        if (finalized) {
            cout << "Grade already finalized. Cannot modify.\n";
            return;
        }
        cout << "Enter mark (0–100): ";
        cin >> mark;
        calculateGrade();
        finalized = true;
    }

    void displayGrade() const {
        if (finalized)
            cout << "Mark: " << mark << ", Grade: " << theGrade << endl;
        else
            cout << "Grade not entered yet.\n";
    }

    bool isFinalized() const {
        return finalized;
    }
};

class Student {
private:
    string regNo;
    string name;
    int age;
    Course course;
    Grade grade;

public:
    void inputDetails() {
        cout << "Enter registration number: ";
        cin >> regNo;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        course.inputCourse();
    }

    void editDetails() {
        cout << "Edit name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Edit age: ";
        cin >> age;
    }

    void addMark() {
        grade.inputMark();
    }

    void displayStudent() const {
        cout << "Reg No: " << regNo << ", Name: " << name << ", Age: " << age << endl;
        course.displayCourse();
        grade.displayGrade();
    }

    string getRegNo() const {
        return regNo;
    }
};

class StudentSystem {
private:
    Student students[40];
    int count;

public:
    StudentSystem() : count(0) {}

    void addStudent() {
        if (count >= 40) {
            cout << "Student limit reached!\n";
            return;
        }
        students[count].inputDetails();
        count++;
        cout << "Student added successfully.\n";
    }

    void editStudent() {
        string reg;
        cout << "Enter reg no to edit: ";
        cin >> reg;
        for (int i = 0; i < count; i++) {
            if (students[i].getRegNo() == reg) {
                students[i].editDetails();
                cout << "Student updated.\n";
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void enterMarks() {
        string reg;
        cout << "Enter reg no to add marks: ";
        cin >> reg;
        for (int i = 0; i < count; i++) {
            if (students[i].getRegNo() == reg) {
                students[i].addMark();
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void listStudents() {
        if (count == 0) {
            cout << "No students available.\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            cout << "\n--- Student " << i + 1 << " ---\n";
            students[i].displayStudent();
        }
    }
};

int main() {
    StudentSystem system;
    int choice;

    do {
        cout << "\n--- STUDENT MANAGEMENT SYSTEM ---\n";
        cout << "1. Add student\n";
        cout << "2. Edit student details\n";
        cout << "3. Enter marks and calculate grade\n";
        cout << "4. List all students\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: system.addStudent(); break;
            case 2: system.editStudent(); break;
            case 3: system.enterMarks(); break;
            case 4: system.listStudents(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
