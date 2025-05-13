#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_CODE 20
#define MAX_STUDENTS 100

// ----------------------- Data Structures -----------------------
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

typedef struct {
    int size;
    Student students[MAX_STUDENTS];
} StudentList;

// ----------------------- Grade Calculation -----------------------
void calculateGrade(Grade* g) {
    if (g->mark > 69) g->grade = 'A';
    else if (g->mark > 59) g->grade = 'B';
    else if (g->mark > 49) g->grade = 'C';
    else if (g->mark > 39) g->grade = 'D';
    else g->grade = 'E';
}

// ----------------------- Student Operations -----------------------
void createStudent(Student* s, const char* reg, const char* name, int age, const char* code, const char* cname, int mark) {
    strcpy(s->reg_no, reg);
    strcpy(s->name, name);
    s->age = age;
    strcpy(s->course.course_code, code);
    strcpy(s->course.course_name, cname);
    s->grade.mark = mark;
    calculateGrade(&s->grade);
}

// ----------------------- List Operations -----------------------
void initList(StudentList* list) {
    list->size = 0;
}

void addStudent(StudentList* list, Student s) {
    if (list->size < MAX_STUDENTS) {
        list->students[list->size++] = s;
    }
}

void addStudentAt(StudentList* list, Student s, int pos) {
    if (list->size < MAX_STUDENTS && pos >= 0 && pos <= list->size) {
        for (int i = list->size; i > pos; i--)
            list->students[i] = list->students[i - 1];
        list->students[pos] = s;
        list->size++;
    }
}

void removeStudent(StudentList* list, Student s) {
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->students[i].reg_no, s.reg_no) == 0) {
            for (int j = i; j < list->size - 1; j++)
                list->students[j] = list->students[j + 1];
            list->size--;
            break;
        }
    }
}

void removeStudentAt(StudentList* list, int pos) {
    if (pos >= 0 && pos < list->size) {
        for (int i = pos; i < list->size - 1; i++)
            list->students[i] = list->students[i + 1];
        list->size--;
    }
}

int getSize(StudentList* list) {
    return list->size;
}

void destroyList(StudentList* list) {
    list->size = 0;
}

// ----------------------- Display -----------------------
void displayStudents(StudentList* list) {
    for (int i = 0; i < list->size; i++) {
        Student* s = &list->students[i];
        printf("RegNo: %s, Name: %s, Age: %d, Course: %s (%s), Mark: %d, Grade: %c\n",
               s->reg_no, s->name, s->age,
               s->course.course_name, s->course.course_code,
               s->grade.mark, s->grade.grade);
    }
}

// ----------------------- Driver Code -----------------------
int main() {
    StudentList list;
    initList(&list);

    // Add 15 students
    for (int i = 0; i < 15; i++) {
        Student s;
        char reg[20];
        sprintf(reg, "REG%02d", i + 1);

        char name[50];
        sprintf(name, "Student_%02d", i + 1);

        int age = 18 + (i % 5);
        int mark = 40 + (i * 3) % 61;  // marks between 40–100

        createStudent(&s, reg, name, age, "ICS2105", "DSA", mark);
        addStudent(&list, s);
    }

    printf("\n=== STUDENT LIST ===\n");
    displayStudents(&list);

    printf("\nTotal Students: %d\n", getSize(&list));

    return 0;
}
