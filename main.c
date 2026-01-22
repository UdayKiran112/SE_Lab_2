#include "parser.h"
#include "student.h"
#include "validation.h"
#include "calculation.h"
#include "output.h"

int main(int argc, char *argv[])
{
    // Argument check
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <count_no_of_students> <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    // Get student count
    int studentCount = atoi(argv[1]);

    // Open input file and output file
    FILE *input = fopen(argv[2], "r");
    FILE *output = fopen(argv[3], "w");

    if (input == NULL)
    {
        fprintf(stderr, "Input file error\n");
        return 1;
    }

    if (output == NULL)
    {
        fprintf(stderr, "Output file error\n");
        fclose(input);
        return 1;
    }

    Student students[studentCount];

    // Parse input file and store data in students array
    int actualCount = 0;
    parse_input(input, students, studentCount, &actualCount);

    // TODO: Calculation part
    // Calculate total marks, percentage and grade for each student
    for (int i = 0; i < actualCount; i++)
    {
        float totalMarks = calculateTotalMarks(students[i].totalScores);
        set_student_total_marks(&students[i], totalMarks);
        float percentage = calculatePercentage(totalMarks);
        set_student_percentage(&students[i], percentage);
        Grade grade = calculateGrade(percentage);
        set_student_grade(&students[i], grade);
    }

    // Calculate individual subject grades and CGPA for each student
    for (int i = 0; i < actualCount; i++)
    {
        for (int j = 0; j < SUBS_COUNT; j++)
        {
            float total_score = get_student_subject_total_marks(&students[i], j);
            Grade subjectGrade = calculateGrade(total_score);
            set_student_subject_grade(&students[i], j, subjectGrade);
        }
    }

    // Calculate CGPA for each student
    for (int i = 0; i < actualCount; i++)
    {
        Grade sub_grades[SUBS_COUNT];
        for (int j = 0; j < SUBS_COUNT; j++)
        {
            sub_grades[j] = get_student_subject_grade(&students[i], j);
        }
        float cgpa = calculateCGPA(sub_grades);
        set_student_cgpa(&students[i], cgpa);
    }

    float classAverage = calculateClassAveragePercentage(students, actualCount);
    float maxPercentage = findMaxPercentage(students, actualCount);
    float minPercentage = findMinPercentage(students, actualCount);

    // TODO: Output part

    printTabularForm(students, actualCount, output);
    printTabularForm(students, actualCount, stdout);

    fprintf(output, "Class Average Percentage: %.2f\n", classAverage);
    fprintf(stdout, "Class Average Percentage: %.2f\n", classAverage);

    fprintf(output, "Highest Percentage in Class: %.2f\n", maxPercentage);
    fprintf(stdout, "Highest Percentage in Class: %.2f\n", maxPercentage);

    fprintf(output, "Lowest Percentage in Class: %.2f\n", minPercentage);
    fprintf(stdout, "Lowest Percentage in Class: %.2f\n", minPercentage);

    Grade grades[actualCount];
    for (int i = 0; i < actualCount; i++)
    {
        grades[i] = get_student_grade(&students[i]);
    }

    printGradeCount(grades, actualCount, stdout);

    fclose(input);
    fclose(output);

    return 0;
}