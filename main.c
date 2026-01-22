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

    // Open input file
    FILE *input = fopen(argv[2], "r");

    if (input == NULL)
    {
        fprintf(stderr, "Input file error\n");
        return 1;
    }

    Student students[studentCount];

    // Open output file
    FILE *output = fopen(argv[3], "w");

    if (output == NULL)
    {
        fprintf(stderr, "Output file error\n");
        fclose(input);
        return 1;
    }

    // Parse input and write to output
    //parse_input(studentCount, input, output);

    fclose(input);
    fclose(output);

    return 0;
}