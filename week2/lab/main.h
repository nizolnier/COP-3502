// Lab 1 - COP3502 - Nicole Nascimento

// pre-processor directives
#include <stdio.h>

// constant
#define MAXSIZE 500

// struct 
struct Student
{
    int student_ID;
    int g1, g2, g3;
    float average;
};

// function prototypes
void readData(struct Student *students, int *c);

struct Student getMaxAverageStudent(struct Student *s, int n);
