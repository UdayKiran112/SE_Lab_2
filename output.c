#include "output.h"

// Function to print the number of students in each Grade category
void printGradeCount(Grade grades[], int count, FILE *output)
{
    fprintf(output, "\n");

    int gradeCount[8];

    for (int i = 0; i < 8; i++)
    {
        gradeCount[i] = 0;
    }

    for (int i = 0; i < count; i++)
    {
        gradeCount[grades[i]]++;
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
        return "ND";
    }
}

// Function to print student data in tabular form
void printTabularForm(Student students[], int count, FILE *output)
{
    fprintf(output,
            "----------------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(output,
            "|    ID    |       Name         |   S1   |   S2   |   S3   |   S4   |   S5   | Total | %%     | Grade | CGPA |\n");
    fprintf(output,
            "----------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        fprintf(output, "| %-8s | %-18s | ",
                get_student_id(&students[i]),
                get_student_name(&students[i]));

        for (int j = 0; j < SUBS_COUNT; j++)
        {
            fprintf(output, "%5.0f | ",
                    get_student_subject_total_marks(&students[i], j));
        }

        fprintf(output, "%5.0f | %6.2f | %-5s | %4.1f |\n",
                get_student_total_marks(&students[i]),
                get_student_percentage(&students[i]),
                gradeToString(get_student_grade(&students[i])),
                get_student_cgpa(&students[i]));
    }

    fprintf(output,
            "----------------------------------------------------------------------------------------------------------------------------------------\n");
}
