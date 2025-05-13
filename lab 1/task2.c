#include <stdio.h>
#include <string.h>

struct Course {
    char course_code[10];
    char course_name[50];
};

struct Grade {
    int mark;
    char the_grade;
};

struct Student {
    char reg_no[20];
    char name[50];
    int age;
    struct Course course;
    struct Grade grade;
    int gradeFinalized;
};

struct Student students[40];
int count = 0;

void calculateGrade(struct Student* s) {
    int m = s->grade.mark;
    if (m > 69) s->grade.the_grade = 'A';
    else if (m > 59) s->grade.the_grade = 'B';
    else if (m > 49) s->grade.the_grade = 'C';
    else if (m > 39) s->grade.the_grade = 'D';
    else s->grade.the_grade = 'E';
}

void addStudent() {
    if (count >= 40) return;
    struct Student* s = &students[count];
    printf("Enter reg no: ");
    scanf("%s", s->reg_no);
    printf("Enter name: ");
    scanf(" %[^\n]", s->name);
    printf("Enter age: ");
    scanf("%d", &s->age);
    printf("Enter course code: ");
    scanf("%s", s->course.course_code);
    printf("Enter course name: ");
    scanf(" %[^\n]", s->course.course_name);
    s->gradeFinalized = 0;
    count++;
}

void addMarks() {
    char reg[20];
    printf("Enter reg no: ");
    scanf("%s", reg);
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].reg_no, reg) == 0) {
            if (students[i].gradeFinalized) {
                printf("Grade finalized.\n");
                return;
            }
            printf("Enter mark: ");
            scanf("%d", &students[i].grade.mark);
            calculateGrade(&students[i]);
            students[i].gradeFinalized = 1;
            return;
        }
    }
    printf("Student not found.\n");
}
