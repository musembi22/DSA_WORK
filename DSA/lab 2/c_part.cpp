#include <iostream>
#include <cstring>
using namespace std;

// ------------------------ Course Class ------------------------
class Course {
private:
    string courseCode;
    string courseName;
public:
    Course() {}
    Course(string code, string name) : courseCode(code), courseName(name) {}

    void setCourse(string code, string name) {
        courseCode = code;
        courseName = name;
    }

    string getCourseCode() const { return courseCode; }
    string getCourseName() const { return courseName; }
};

// ------------------------ Grade Class ------------------------
class Grade {
private:
    int mark;
    char grade;
public:
    Grade() : mark(0), grade('F') {}

    void setMark(int m) {
        mark = m;
        calculateGrade();
    }

    int getMark() const { return mark; }
    char getGrade() const { return grade; }

private:
    void calculateGrade() {
        if (mark > 69) grade = 'A';
        else if (mark > 59) grade = 'B';
        else if (mark > 49) grade = 'C';
        else if (mark > 39) grade = 'D';
        else grade = 'E';
    }
};

// ------------------------ Student Class ------------------------
class Student {
private:
    string regNo;
    string name;
    int age;
    Course course;
    Grade grade;
public:
    Student() {}

    Student(string reg, string nm, int ag, Course crs, int mark) {
        regNo = reg;
        name = nm;
        age = ag;
        course = crs;
        grade.setMark(mark);
    }

    void setRegNo(string r) { regNo = r; }
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setCourse(Course c) { course = c; }
    void setGrade(Grade g) { grade = g; }

    string getRegNo() const { return regNo; }
    string getName() const { return name; }
    int getAge() const { return age; }
    Course getCourse() const { return course; }
    Grade getGrade() const { return grade; }

    void display() const {
        cout << "RegNo: " << regNo
             << ", Name: " << name
             << ", Age: " << age
             << ", Course: " << course.getCourseName() << " (" << course.getCourseCode() << ")"
             << ", Mark: " << grade.getMark()
             << ", Grade: " << grade.getGrade()
             << endl;
    }
};

// ------------------------ Node & Linked List ------------------------
class Node {
public:
    Student student;
    Node* next;
    Node(Student s) : student(s), next(nullptr) {}
};

class StudentList {
private:
    Node* head;
    int size;
public:
    StudentList() : head(nullptr), size(0) {}

    ~StudentList() {
        destroy();
    }

    void insertEnd(Student s) {
        Node* newNode = new Node(s);
        if (!head)
            head = newNode;
        else {
            Node* current = head;
            while (current->next)
                current = current->next;
            current->next = newNode;
        }
        size++;
    }

    void deleteByRegNo(string reg) {
        Node* current = head;
        Node* prev = nullptr;

        while (current && current->student.getRegNo() != reg) {
            prev = current;
            current = current->next;
        }

        if (!current) return;  // not found

        if (!prev)
            head = current->next;
        else
            prev->next = current->next;

        delete current;
        size--;
    }

    void display() const {
        Node* current = head;
        int index = 1;
        while (current) {
            cout << index++ << ") ";
            current->student.display();
            current = current->next;
        }
    }

    int getSize() const {
        return size;
    }

    void destroy() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        size = 0;
    }
};

// ------------------------ Main Driver ------------------------
int main() {
    StudentList list;

    // Add 15 students
    for (int i = 0; i < 15; i++) {
        string reg = "REG" + to_string(i + 1);
        string name = "Student_" + to_string(i + 1);
        int age = 18 + (i % 5);
        int mark = 40 + (i * 4) % 61;  // marks between 40 and 100
        Course course("ICS2105", "DSA");

        Student s(reg, name, age, course, mark);
        list.insertEnd(s);
    }

    cout << "\n=== LINKED LIST OF STUDENTS ===\n";
    list.display();

    cout << "\nTotal Students: " << list.getSize() << endl;

    // Optional: delete one student
    list.deleteByRegNo("REG5");
    cout << "\nAfter deleting REG5:\n";
    list.display();
    cout << "Total Students: " << list.getSize() << endl;

    return 0;
}
