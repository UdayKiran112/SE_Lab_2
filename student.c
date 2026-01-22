#include "student.h"

// Function to calculate total marks from total scores
float calculateTotalMarks(float totalScores[])
{
    float sum = 0.0;
    for (int i = 0; i < SUBS_COUNT; i++)
    {
        sum += totalScores[i];
    }
    return sum;
}

// Function to calculate percentage from total marks
float calculatePercentage(float totalMarks)
{
    return (totalMarks / (SUBS_COUNT));
}

// Function to calculate grade based on percentage
Grade calculateGrade(float percentage)
{
    if (percentage >= 90.0)
    {
        return O;
    }
    else if (percentage >= 85.0 && percentage < 90.0)
    {
        return A_PLUS;
    }
    else if (percentage >= 75.0 && percentage < 85.0)
    {
        return A;
    }
    else if (percentage >= 65.0 && percentage < 75.0)
    {
        return B_PLUS;
    }
    else if (percentage >= 60.0 && percentage < 65.0)
    {
        return B;
    }
    else if (percentage >= 55.0 && percentage < 60.0)
    {
        return C;
    }
    else if (percentage >= 50.0 && percentage < 55.0)
    {
        return D;
    }
    else
    {
        return F;
    }
}

// Function to convert Grade enum to string
char *gradeToString(Grade grade)
{
    switch (grade)
    {
    case O:
        return "O";
    case A_PLUS:
        return "A+";
    case A:
        return "A";
    case B_PLUS:
        return "B+";
    case B:
        return "B";
    case C:
        return "C";
    case D:
        return "D";
    case F:
        return "F";
    default:
        return "Unknown";
    }
}

// Function to calculate class average percentage
float calculateClassAveragePercentage(Student students[], int count)
{
    float avgPercentage = 0.0;
    for (int i = 0; i < count; i++)
    {
        avgPercentage += students[i].totalPercentage;
    }

    return avgPercentage / count;
}

// Function to find maximum percentage in the class
float findMaxPercentage(Student students[], int count)
{
    float maxPercentage = students[0].totalPercentage;
    for (int i = 1; i < count; i++)
    {
        if (students[i].totalPercentage > maxPercentage)
        {
            maxPercentage = students[i].totalPercentage;
        }
    }
    return maxPercentage;
}

// Function to find minimum percentage in the class
float findMinPercentage(Student students[], int count)
{
    float minPercentage = students[0].totalPercentage;
    for (int i = 1; i < count; i++)
    {
        if (students[i].totalPercentage < minPercentage)
        {
            minPercentage = students[i].totalPercentage;
        }
    }
    return minPercentage;
}

// Function to get grade point from Grade enum
int getGradePoint(Grade grade)
{
    switch (grade)
    {
    case O:
        return 10;
    case A_PLUS:
        return 9;
    case A:
        return 8;
    case B_PLUS:
        return 7;
    case B:
        return 6;
    case C:
        return 5;
    case D:
        return 4;
    case F:
        return 0;
    default:
        return -1;
    }
}

// Calculate CGPA of a student using total marks in each subject
float calculateCGPA(Student student)
{
    float cgpa = 0.0;
    for (int i = 0; i < SUBS_COUNT; i++)
    {
        Grade gr = calculateGrade(student.minorScores[i] + student.majorScores[i]);
        cgpa += getGradePoint(gr);
    }
    return cgpa / SUBS_COUNT;
}

// Function to print the number of students in each Grade category
void printGradeCount(Student students[], int count, FILE *output)
{
    fprintf(output, "\n");

    int gradeCount[8];

    for (int i = 0; i < 8; i++)
    {
        gradeCount[i] = 0;
    }

    for (int i = 0; i < count; i++)
    {
        gradeCount[students[i].grade]++;
    }

    fprintf(output, "Number of students in each grade:\n");
    fprintf(output, "O: %d\n", gradeCount[O]);
    fprintf(output, "A+: %d\n", gradeCount[A_PLUS]);
    fprintf(output, "A: %d\n", gradeCount[A]);
    fprintf(output, "B+: %d\n", gradeCount[B_PLUS]);
    fprintf(output, "B: %d\n", gradeCount[B]);
    fprintf(output, "C: %d\n", gradeCount[C]);
    fprintf(output, "D: %d\n", gradeCount[D]);
    fprintf(output, "F: %d\n", gradeCount[F]);
}

// Function to print student data in tabular form
void printTabularForm(Student students[], int count, FILE *output)
{
    fprintf(output,
            "----------------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(output,
            "|    ID    |       Name         |   S1   |    S2   |    S3   |    S4   |    S5   | Total | %%     | Grade | CGPA |\n");
    fprintf(output,
            "----------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        fprintf(output, "| %-8s | %-18s | ", students[i].id, students[i].name);

        for (int j = 0; j < SUBS_COUNT; j++)
        {
            fprintf(output, "%2.0f | %2.0f | ",
                    students[i].minorScores[j],
                    students[i].majorScores[j]);
        }
        fprintf(output, "%5.0f | %5.2f | %-5s | %4.1f |\n",
                students[i].totalMarks,
                students[i].totalPercentage,
                gradeToString(students[i].grade),
                calculateCGPA(students[i]));
    }

    fprintf(output,
            "------------------------------------------------------------------------------------------------------------------------------------------\n");
}
