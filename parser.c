#include "parser.h"

static int isLineEmpty(const char *line)
{
    while (*line)
    {
        if (*line != ' ' && *line != '\t' && *line != '\n')
        {
            return 0;
        }
        line++;
    }
    return 1;
}

void parse_input(FILE *input, Student students[], int students_count, int *actual_count)
{
    char line[256]; // buffer to read lines
    int n = 0;

    char id_buffer[32];   // buffer to store ID
    char name_buffer[64]; // buffer to store Name

    while (n < students_count)
    {
        // Read ID from line
        while (1)
        {
            if (!fgets(line, sizeof(line), input))
            {
                goto finished;
            }

            if (isLineEmpty(line))
            {
                continue; // skip blank lines safely
            }

            line[strcspn(line, "\n")] = '\0'; // Remove newline character

            int idCheck = checkID(line, students, n);
            if (idCheck == 0)
            {
                break;
            }
            if (idCheck == -1)
            {
                printf("Invalid ID (%s).", line);
                printf("Enter valid alphanumeric ID: ");
            }
            else
            {
                printf("Duplicate ID (%s).", line);
                printf("Enter unique ID: ");
            }

            fgets(line, sizeof(line), stdin);
            line[strcspn(line, "\n")] = '\0';
        }

        strncpy(id_buffer, line, sizeof(id_buffer) - 1);
        id_buffer[sizeof(id_buffer) - 1] = '\0';

        // Read Name from line
        while (1)
        {
            if (!fgets(line, sizeof(line), input))
            {
                goto finished;
            }

            if (isLineEmpty(line))
            {
                continue; // skip blank lines safely
            }

            line[strcspn(line, "\n")] = '\0'; // Remove newline character

            if (checkName(line) == 0)
            {
                break;
            }
            printf("Invalid Name : %s", line);
            printf("Enter valid Name (alphabets and spaces only): ");
            fgets(line, sizeof(line), stdin);
            line[strcspn(line, "\n")] = '\0';
        }

        strncpy(name_buffer, line, sizeof(name_buffer) - 1);
        name_buffer[sizeof(name_buffer) - 1] = '\0';

        // Create Student
        Student *student_ptr = create_student(id_buffer, name_buffer);

        // Read Marks for each subject
        for (int i = 0; i < SUBS_COUNT; i++)
        {
            float minor, major;

            while (1)
            {
                if (!fgets(line, sizeof(line), input))
                {
                    printf("Missing marks for %s for subject %d. ", id_buffer, i + 1);
                    printf("Please enter Minor and Major marks: ");
                    fgets(line, sizeof(line), stdin);
                }

                if (sscanf(line, "%f %f", &minor, &major) != 2)
                {
                    printf("Invalid marks format. Please enter Minor and Major marks again: ");
                    fgets(line, sizeof(line), stdin);
                    continue;
                }

                if (checkMarks(minor, major) == 0)
                {
                    break;
                }
                printf("Marks out of range for %s for subject %d. ", id_buffer, i + 1);
                printf("Please enter valid Minor and Major marks: ");
                fgets(line, sizeof(line), stdin);
            }

            set_student_marks(student_ptr, i, minor, major);
        }

        // Store student in array
        students[n] = *student_ptr;
        free(student_ptr);
        n++;
    }

finished:
    *actual_count = n;
}

/*// read data from input file and write to output file
void parse_input(int count, FILE *input, FILE *output)
{
    Student students[count];

    int n = 0;

    char line[256];

    while (n < count && fgets(line, sizeof(line), input) != NULL)
    {
        if (strlen(line) <= 1)
        {
            continue; // skip empty lines
        }

        line[strcspn(line, "\n")] = 0; // Remove newline character

        int idCheck = checkID(line, students, n);

        if (idCheck == -1)
        {
            // Prompt user for correct ID
            fprintf(stderr, "Invalid ID: %s\n", line);
            fprintf(stderr, "Please enter a valid alphanumeric ID: ");
            fgets(line, sizeof(line), stdin);
            line[strcspn(line, "\n")] = 0; // Remove newline character
            checkID(line, students, n);
        }
        else if (idCheck == 1)
        {
            // Prompt user for unique ID
            fprintf(stderr, "Duplicate ID found: %s\n", line);
            fprintf(stderr, "Please enter a unique ID: ");
            fgets(line, sizeof(line), stdin);
            line[strcspn(line, "\n")] = 0; // Remove newline character
            checkID(line, students, n);
        }

        strcpy(students[n].id, line);

        fgets(line, sizeof(line), input);
        line[strcspn(line, "\n")] = 0; // Remove newline character

        int nameCheck = checkName(line);

        if (nameCheck == 1)
        {
            // Prompt user for correct Name
            fprintf(stderr, "Invalid Name: %s\n", line);
            fprintf(stderr, "Please enter a valid Name (alphabets and spaces only): ");
            fgets(line, sizeof(line), stdin);
            line[strcspn(line, "\n")] = 0; // Remove newline character
            checkName(line);
        }

        strcpy(students[n].name, line);

        for (int i = 0; i < SUBS_COUNT; i++)
        {
            fscanf(input, "%f %f", &students[n].minorScores[i], &students[n].majorScores[i]);

            int marksCheck = checkMarks(students[n].minorScores[i], students[n].majorScores[i]);

            if (marksCheck == 1)
            {
                // Prompt user for correct Minor Marks
                fprintf(stderr, "Student ID: %s, Name: %s\n", students[n].id, students[n].name);
                fprintf(stderr, "Please enter a valid Minor Marks for Subject %d: ", i + 1);
                scanf("%f", &students[n].minorScores[i]);
                checkMarks(students[n].minorScores[i], students[n].majorScores[i]);
            }
            else if (marksCheck == -1)
            {
                // Prompt user for correct Major Marks
                fprintf(stderr, "Please enter a valid Major Marks for Subject %d: ", i + 1);
                scanf("%f", &students[n].majorScores[i]);
                checkMarks(students[n].minorScores[i], students[n].majorScores[i]);
            }

            students[n].totalScores[i] = students[n].minorScores[i] + students[n].majorScores[i];
        }

        n++;
    }

    // Calculate total marks, percentage and grade for each student
    for (int i = 0; i < n; i++)
    {
        students[i].totalMarks = calculateTotalMarks(students[i].totalScores);
        students[i].totalPercentage = calculatePercentage(students[i].totalMarks);
        students[i].grade = calculateGrade(students[i].totalPercentage);
    }

    /*
    for (int i = 0; i < n; i++)
    {
        fprintf(output, "ID: %s\n", students[i].id);
        fprintf(output, "Name: %s\n", students[i].name);
        for (int j = 0; j < SUBS_COUNT; j++)
        {
            fprintf(output, "Subject %d: Minor Marks: %.2f, Major Marks: %.2f, Total Marks: %.2f\n",
                    j + 1,
                    students[i].minorScores[j],
                    students[i].majorScores[j],
                    students[i].totalScores[j]);
        }
        fprintf(output, "Total Marks: %.2f\n", students[i].totalMarks);
        fprintf(output, "Percentage: %.2f\n", students[i].totalPercentage);
        fprintf(output, "Grade: %s\n", gradeToString(students[i].grade));
        fprintf(output, "CGPA: %.2f\n", calculateCGPA(students[i]));
        fprintf(output, "\n");
    }

    // Print student data in tabular form
    printTabularForm(students, n, stdout);
    printTabularForm(students, n, output);

    // Calculate and print class average percentage
    float classAverage = calculateClassAveragePercentage(students, n);
    fprintf(output, "Class Average Percentage: %.2f\n", classAverage);
    fprintf(stdout, "Class Average Percentage: %.2f\n", classAverage);

    float maxPercentage = findMaxPercentage(students, n);
    fprintf(output, "Highest Percentage in Class: %.2f\n", maxPercentage);
    fprintf(stdout, "Highest Percentage in Class: %.2f\n", maxPercentage);

    float minPercentage = findMinPercentage(students, n);
    fprintf(output, "Lowest Percentage in Class: %.2f\n", minPercentage);
    fprintf(stdout, "Lowest Percentage in Class: %.2f\n", minPercentage);

    // Find grade count and print to output file
    printGradeCount(students, n, output);
    printGradeCount(students, n, stdout);
}*/
