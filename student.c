#include "student.h"

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
