#ifndef CALCULATION_H
#define CALCULATION_H

#include "student.h"

float calculateTotalMarks(float totalScores[]);
float calculatePercentage(float totalMarks);
Grade calculateGrade(float percentage);
char *gradeToString(Grade grade);
float calculateClassAveragePercentage(Student students[], int count);
float findMaxPercentage(Student students[], int count);
float findMinPercentage(Student students[], int count);
int getGradePoint(Grade grade);
float calculateCGPA(Grade sub_grades[]);

#endif
