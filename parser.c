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