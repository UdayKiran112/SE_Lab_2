#ifndef OUTPUT_H
#define OUTPUT_H

#include "student.h"

void printGradeCount(Grade grades[], int count, FILE *output);
char *gradeToString(Grade grade);
void printTabularForm(Student students[], int count, FILE *output);

#endif