#include "student.h"

// Function to create a new student
Student *create_student(const char *id, const char *name)
{
    Student *new_student = (Student *)malloc(sizeof(Student));

    strncpy(new_student->id, id, sizeof(new_student->id));
    strncpy(new_student->name, name, sizeof(new_student->name));
    
    return new_student;
}

void set_student_marks(Student *student, int subject_index, float minor_marks, float major_marks)
{
    if (subject_index < 0 || subject_index >= SUBS_COUNT)
    {
        fprintf(stderr, "Invalid subject index\n");
        return;
    }

    student->minorScores[subject_index] = minor_marks;
    student->majorScores[subject_index] = major_marks;
}

void set_student_subject_grade(Student *student, int subject_index, Grade grade)
{
    if (subject_index < 0 || subject_index >= SUBS_COUNT)
    {
        fprintf(stderr, "Invalid subject index\n");
        return;
    }

    student->subject_grades[subject_index] = grade;
}

void set_student_grade(Student *student, Grade grade)
{
    student->totalGrade = grade;
}

const char *get_student_id(const Student *student)
{
    return student->id;
}

const char *get_student_name(const Student *student)
{
    return student->name;
}

float get_student_total_marks(const Student *student)
{
    return student->totalMarks;
}

float get_student_percentage(const Student *student)
{
    return student->totalPercentage;
}

Grade get_student_grade(const Student *student)
{
    return student->totalGrade;
}

Grade get_student_subject_grade(const Student *student, int subject_index)
{
    if (subject_index < 0 || subject_index >= SUBS_COUNT)
    {
        fprintf(stderr, "Invalid subject index\n");
        return ND;
    }

    return student->subject_grades[subject_index];
}

void delete_student(Student *student)
{
    free(student);
}
