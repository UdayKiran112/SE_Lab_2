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
        if (!fgets(line, sizeof(line), input))
        {
            break;
        }

        while (isLineEmpty(line))
        {
            if (!fgets(line, sizeof(line), input))
            {
                goto finished;
            }
        }

        line[strcspn(line, "\n")] = '\0';

        while (checkID(line, students, n) != 0)
        {
            if (checkID(line, students, n) == -1)
            {
                printf("Invalid ID: %s\n", line);
            }
            else
            {
                printf("Duplicate ID: %s\n", line);
            }

            printf("Enter valid unique alphanumeric ID: ");

            if (!fgets(line, sizeof(line), stdin))
            {
                goto finished;
            }

            line[strcspn(line, "\n")] = '\0';
        }

        strncpy(id_buffer, line, sizeof(id_buffer) - 1);
        id_buffer[sizeof(id_buffer) - 1] = '\0';

        // Read Name from line
        if (!fgets(line, sizeof(line), input))
        {
            goto finished;
        }

        while (isLineEmpty(line))
        {
            if (!fgets(line, sizeof(line), input))
            {
                goto finished;
            }
        }

        line[strcspn(line, "\n")] = '\0';

        while (checkName(line) != 0)
        {
            printf("Invalid Name: %s\n", line);
            printf("Enter valid Name (alphabets and spaces only): ");

            if (!fgets(line, sizeof(line), stdin))
            {
                goto finished;
            }

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

            if (!fgets(line, sizeof(line), input))
            {
                printf("Missing marks for %s (Subject %d)\n",
                       id_buffer, i + 1);
                printf("Enter Minor and Major marks: ");

                if (!fgets(line, sizeof(line), stdin))
                {
                    goto finished;
                }
            }

            // Validate marks input if not in correct format
            while (sscanf(line, "%f %f", &minor, &major) != 2)
            {
                printf("Invalid format for %s (Subject %d)\n",
                       id_buffer, i + 1);
                printf("Enter Minor and Major marks: ");

                if (!fgets(line, sizeof(line), stdin))
                {
                    goto finished;
                }
            }

            // Validate marks values and prompt until valid
            while (1)
            {
                int status = checkMarks(minor, major);

                if (status == 0)
                {
                    break; // both valid
                }

                if (status == 1)
                {
                    printf("Invalid Minor marks (%.2f) for %s (Subject %d)\n",
                           minor, id_buffer, i + 1);
                    printf("Enter valid Minor marks: ");

                    if (!fgets(line, sizeof(line), stdin))
                    {
                        goto finished;
                    }

                    if (sscanf(line, "%f", &minor) != 1)
                    {
                        continue;
                    }
                }
                else if (status == -1)
                {
                    printf("Invalid Major marks (%.2f) for %s (Subject %d)\n",
                           major, id_buffer, i + 1);
                    printf("Enter valid Major marks: ");

                    if (!fgets(line, sizeof(line), stdin))
                    {
                        goto finished;
                    }

                    if (sscanf(line, "%f", &major) != 1)
                    {
                        continue;
                    }
                }
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