# Student Result Processing System (C)

Software Engineering Lab – M.Tech (CS, AI)<br>
Semester: Jan–May 2026<br>
School of Computer and Information Sciences<br>
University of Hyderabad<br>

## Project Description

This project implements a **Student Result Processing System** in C that:

- Reads student data from a file
- Validates ID, Name, Minor & Major marks
- Computes totals, percentages, grades and CGPA
- Displays results in a structured tabular report
- Computes class statistics such as average, highest, lowest and grade distribution

## Input File Format

File name: `info.txt`

Each student record is written in **block format**:

```text
25MCMI15
Gedela Uday Kiran
30 45
32 50
35 55
28 48
36 52

25MCMT12
Ram Krishna
15 20
18 25
21 30
24 35
27 47
```

### Field Meaning

| Line         | Data                                   |
| ------------ | -------------------------------------- |
| 1            | Student ID (alphanumeric, unique)      |
| 2            | Student Name (alphabets & spaces only) |
| Next 5 lines | `Minor Major` marks for 5 subjects     |

- Minor range: 0 – 40
- Major range: 0 – 60
- Total per subject ≤ 100

## Compilation

```bash
make
```

## Execution

```bash
./result
```

## Output

- Student-wise:

  - Minor, Major, Total Marks per subject
  - Overall Total, Percentage, Grade, CGPA

- Class-wise:

  - Class Average Percentage
  - Highest Percentage
  - Lowest Percentage
  - Number of students in each grade category

## Grading Scheme

| Percentage | Grade |
| ---------- | ----- |
| ≥ 90       | O     |
| 85 – 90    | A+    |
| 75 – 85    | A     |
| 65 – 75    | B+    |
| 60 – 65    | B     |
| 55 – 60    | C     |
| 50 – 55    | D     |
| < 50       | F     |

## Validation Rules

| Field       | Validation              |
| ----------- | ----------------------- |
| Student ID  | Alphanumeric & unique   |
| Name        | Alphabets & spaces only |
| Minor Marks | 0 – 40                  |
| Major Marks | 0 – 60                  |
| Total       | ≤ 100                   |

Invalid records are prompted for correction.

## Project Structure

```bash
Student-Result-Processing-System/
├── main.c
├── parser.c
├── student.c
├── parser.h
├── student.h
├── info.txt
├── out.txt
├── Makefile
├── obj/
└── README.md
```

## Author

**Gedela Uday Kiran**<br>
M.Tech AI<br>
University of Hyderabad<br>
