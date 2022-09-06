// Lab 1 - COP3502 - Nicole Nascimento

#include <stdio.h>
#include "main.h"

// function that receives an empty array and a reference to an int and fill them up with the data from the input
void readData(struct Student *students, int *c)
{
    // scanning the number of lines/students
    scanf("%d", c);

    // for each student, i scan the id, grade 1, grade 2, grade 3 and store it
    for (int i = 0; i < *c; i++)
    {
        scanf("%d", &students[i].student_ID);

        scanf("%d %d %d", &students[i].g1, &students[i].g2, &students[i].g3);

        // then i calculate the average using 3.0 to give the result in float and store it
        students[i].average = (students[i].g1 + students[i].g2 + students[i].g3) / 3.0;

        // then display the information with the appropriate formatting
        printf("%d %d %d %d %.2f\n", students[i].student_ID, students[i].g1, students[i].g2, students[i].g3, students[i].average);
    }
}

// function that receives an array of students and an int and returns the student with the maximum average
struct Student getMaxAverageStudent(struct Student *s, int n)
{
    // setting the maximum average as -1 because the student can have an average of 0
    float max = -1;

    // declaring a counter and a maximum index
    int i, max_idx = 0;

    // for each student, i analyze the average
    // if the average is bigger than the max, then i save the index and that average becomes the new max
    for (i = 0; i < n; i++)
    {
        if (s[i].average > max)
        {
            max = s[i].average;
            max_idx = i;
        }
    }

    // then i just return the student with the maximum average
    return s[max_idx];
}

// driver function
int main(void)
{
    // declaring the students array and n, the number of lines/iterations/students
    struct Student students[MAXSIZE];
    int n;

    // calling readData and passing students and the address of n
    readData(students, &n);

    // getting the student with the best average
    struct Student maxStudent = getMaxAverageStudent(students, n);

    // printting with the appropriate formatting
    printf("\nMaximum Average is %.2f and the student is %d\n", maxStudent.average, maxStudent.student_ID);

    return 0;
}
