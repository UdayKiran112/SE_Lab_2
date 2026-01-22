#include "validation.h"

// Function to check validity of student ID --> returns 0 if valid, -1 if invalid(not alphanumeric), 1 if duplicate
int checkID(char id[], Student students[], int count)
{
    // Alphanumeric check
    for (int i = 0; id[i] != '\0'; i++)
    {
        if (!isalnum(id[i]))
        {
            fprintf(stderr, "Invalid ID: %s\n", id);
            return -1;
        }
    }

    // Duplicate ID check
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].id, id) == 0)
        {
            fprintf(stderr, "Duplicate ID found: %s\n", id);
            return 1;
        }
    }

    return 0;
}

// Function to check validity of student Name --> returns 0 if valid, 1 if invalid
int checkName(char name[])
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i]) && !isspace(name[i]))
        {
            fprintf(stderr, "Invalid Name: %s\n", name);
            return 1;
        }
    }

    return 0;
}

// Function to check validity of Marks --> returns 0 if valid, 1 if minor marks invalid, -1 if major marks invalid, 2 if total marks invalid
int checkMarks(float minorMarks, float majorMarks)
{
    if (minorMarks < 0.0 || minorMarks > 40.0)
    {
        fprintf(stderr, "Invalid Minor Marks: %.2f\n", minorMarks);
        return 1;
    }
    else if (majorMarks < 0.0 || majorMarks > 60.0)
    {
        fprintf(stderr, "Invalid Major Marks: %.2f\n", majorMarks);
        return -1;
    }

    return 0;
}