#ifndef PARSER_H
#define PARSER_H

#include "student.h"
#include "validation.h"

void parse_input(FILE *input, Student students[], int students_count, int *actual_count);

#endif