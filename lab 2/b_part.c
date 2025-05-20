#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_CODE 20

// ------------------------ DATA STRUCTURES ------------------------
typedef struct {
    char course_code[MAX_CODE];
    char course_name[MAX_NAME];
} Course;

typedef struct {
    int mark;
    char grade;
} Grade;

typedef struct {
    char reg_no[MAX_CODE];
    char name[MAX_NAME];
    int age;
    Course course;
    Grade grade;
} Student;

typedef struct StudentNode {
    Student student;
    struct StudentNode* next;
} StudentNode;

typedef struct {
    StudentNode* head;
    int size;
} LinkedStudentList;

// ------------------------ GRADE CALCULATION ------------------------
void calculateGrade(Grade* g) {
    if (g->mark > 69) g->grade = 'A';
    else if (g->mark > 59) g->grade = 'B';
    else if (g->mark > 49) g->grade = 'C';
    else if (g->mark > 39) g->grade = 'D';
    else g->grade = 'E';
}

// ------------------------ STUDENT UTILITY ------------------------
void createStudent(Student* s, const char* reg, const char* name, int age, const char* code, const char* cname, int mark) {
    strcpy(s->reg_no, reg);
    strcpy(s->name, name);
    s->age = age;
    strcpy(s->course.course_code, code);
    strcpy(s->course.course_name, cname);
    s->grade.mark = mark;
    calculateGrade(&s->grade);
}

// ------------------------ LINKED LIST OPERATIONS ------------------------
void initList(LinkedStudentList* list) {
    list->head = NULL;
    list->size = 0;
}

void insertAtEnd(LinkedStudentList* list, Student s) {
    StudentNode* newNode = (StudentNode*)malloc(sizeof(StudentNode));
    newNode->student = s;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        StudentNode* current = list->head;
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
    }
    list->size++;
}

void deleteByRegNo(LinkedStudentList* list, const char* regNo) {
    StudentNode* current = list->head;
    StudentNode* prev = NULL;

    while (current != NULL && strcmp(current->student.reg_no, regNo) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return;

    if (prev == NULL)
        list->head = current->next;
    else
        prev->next = current->next;

    free(current);
    list->size--;
}

void displayList(const LinkedStudentList* list) {
    StudentNode* current = list->head;
    int index = 1;

    while (current != NULL) {
        Student* s = &current->student;
        printf("%02d) RegNo: %s, Name: %s, Age: %d, Course: %s (%s), Mark: %d, Grade: %c\n",
               index++, s->reg_no, s->name, s->age,
               s->course.course_name, s->course.course_code,
               s->grade.mark, s->grade.grade);
        current = current->next;
    }
}

void destroyList(LinkedStudentList* list) {
    StudentNode* current = list->head;
    while (current != NULL) {
        StudentNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}

int getSize(const LinkedStudentList* list) {
    return list->size;
}

// ------------------------ MAIN DRIVER ------------------------
int main() {
    LinkedStudentList list;
    initList(&list);

    // Add 15 students
    for (int i = 0; i < 15; i++) {
        Student s;
        char reg[20], name[50];
        sprintf(reg, "REG%02d", i + 1);
        sprintf(name, "Student_%02d", i + 1);
        int age = 18 + (i % 5);
        int mark = 40 + (i * 4) % 61;  // marks between 40–100

        createStudent(&s, reg, name, age, "ICS2105", "DSA", mark);
        insertAtEnd(&list, s);
    }

    printf("\n=== LINKED LIST OF STUDENTS ===\n");
    displayList(&list);

    printf("\nTotal Students: %d\n", getSize(&list));

    // Optional: test deletion
    deleteByRegNo(&list, "REG05");
    printf("\nAfter deleting REG05:\n");
    displayList(&list);
    printf("Total Students: %d\n", getSize(&list));

    // Clean up
    destroyList(&list);
    return 0;
}
