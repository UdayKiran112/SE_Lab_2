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
    F
} Grade;

typedef struct
{
    char id[10];
    char name[50];
    float minorScores[SUBS_COUNT];
    float majorScores[SUBS_COUNT];
    float totalScores[SUBS_COUNT];
    float totalMarks;
    float totalPercentage;
    Grade grade;
} Student;

float calculateTotalMarks(float totalScores[]);
float calculatePercentage(float totalMarks);
Grade calculateGrade(float percentage);
char *gradeToString(Grade grade);
float calculateClassAveragePercentage(Student students[], int count);
float findMaxPercentage(Student students[], int count);
float findMinPercentage(Student students[], int count);
int getGradePoint(Grade grade);
float calculateCGPA(Student student);
void printGradeCount(Student students[], int count, FILE *output);
void printTabularForm(Student students[], int count, FILE *output);

#endif