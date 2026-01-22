#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUBS_COUNT 5

typedef enum
{
    O,
    A_PLUS,
    A,
    B_PLUS,
    B,
    C,
    D,
    F,
    ND
} Grade;

typedef struct
{
    char id[10];
    char name[50];
    float minorScores[SUBS_COUNT];
    float majorScores[SUBS_COUNT];
    float totalScores[SUBS_COUNT];
    Grade subject_grades[SUBS_COUNT];
    float totalMarks;
    float totalPercentage;
    Grade totalGrade;
    float CGPA;
} Student;

Student *create_student(const char *id, const char *name);
void set_student_marks(Student *student, int subject_index, float minor_marks, float major_marks);
void set_student_subject_grade(Student *student, int subject_index, Grade grade);
void set_student_grade(Student *student, Grade grade);
void set_student_total_marks(Student *student, float total_marks);
void set_student_percentage(Student *student, float percentage);
void set_student_cgpa(Student *student, float cgpa);

const char *get_student_id(const Student *student);
const char *get_student_name(const Student *student);
float get_student_total_marks(const Student *student);
float get_student_percentage(const Student *student);
Grade get_student_grade(const Student *student);
Grade get_student_subject_grade(const Student *student, int subject_index);
float get_student_subject_total_marks(const Student *student, int subject_index);
float get_student_cgpa(const Student *student);

void delete_student(Student *student);

#endif