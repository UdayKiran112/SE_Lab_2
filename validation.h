#ifndef VALIDATION_H
#define VALIDATION_H

#include "student.h"

// Methods
int checkID(char id[], Student students[], int count); // change inputs to reduce coupling
int checkName(char name[]);
int checkMarks(float minorMarks, float majorMarks);

#endif