// Lab 2 - COP3502c - Using Dynamic Memory Allocation
// Author: Nicole Nascimento

/*

    PUT A SUMMARY OF THE PURPOSE OF THE CODE (just a few lines will do and DO
   NOT EXCEED 100 char Per line for clarity)

    My Own As Sample:

    => read a set of students data and their grading information from a file and
   then process them and then write the requested data to another file.

*/

// pre-processor directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // whenever you have string, you will need strcopy e strlen
#include "leak_detector_c.h"

// declare a global constant
// this constant will represent the max size that student name can have
// It was specified that it's 50 character why do we have an extra 1??? hmmmm
#define NAMEMAX 51

// declare a struct to hold the characteristics of each student
typedef struct student {

  // variables declaration:
  char *lname; // last name with a length of 50 characters acceptable [DMA
               // needed here!]

  // declare variables to hold the multiple set of activities(grades mainly)
  int assignment;
  int finalExam;
  int total;
  int *quizzes; // use the number of quizzes to help us when we allocated memory
                // for the quizzes [DMA needed here!]

} student;

/*
    Take input for all the scores for quizzes, assignments, and final exams for
   all the students. Calculate the total scores for each student and store it in
   the corresponding structure.
*/

// returns a 2d array of courses (check explanation I left in main if needed
// regarding why it's a 2d array)
student **readCourses(int *C, int *N, int *M) {

  // variables declaration
  int cn, sn, qn;
  student ** courses;
  int i,j;
  char lastName[NAMEMAX];

  scanf("%d %d %d", C,N,M);
  // Allocates the memory for C number of courses
  // Array of arrays of students aka 2D array of students.
  // so courses is an array of students pointers
  courses = (student **)malloc(*C * sizeof(student *));

  // allocate memory for the list of students for each course
  for (cn = 0; cn < *C; cn++) {
    courses[cn] = (student *)malloc(*N * sizeof(student));
    // Array of students for cnth course

    // now access each students of course[cn]
    for (sn = 0; sn < *N; sn++) {

      // total for the student
      int total = 0;
      // read name and get the length of the name
      scanf("%s", lastName);

      int length = strlen(lastName) + 1;

      courses[cn][sn].lname = malloc(length * sizeof(char));

      strcpy(courses[cn][sn].lname, lastName);
      // take assignment score
      scanf("%d", &courses[cn][sn].assignment);
      total += courses[cn][sn].assignment;
      // allocate memory for M number of quizzes for that particular student
      courses[cn][sn].quizzes = malloc(*M * sizeof(int));
      // take all quiz scores
      for (qn = 0; qn < *M; qn++) {
        scanf("%d", &courses[cn][sn].quizzes[qn]);
        total += courses[cn][sn].quizzes[qn];
      }

      // input the final exam score
      scanf("%d", &courses[cn][sn].finalExam);
      total += courses[cn][sn].finalExam;

      courses[cn][sn].total = total;
    }
  }

  // end of the function return the 2d array
  return courses;
}

/*

    Display the student’s details who achieved the highest total score across
   all the courses. You do not have to consider if a student with same name is
   available in multiple courses.

*/

// the function determines the highest scoring student for each course and
// prints his/her details following the assignment's format
void printHighestTotal(student **courses, int C, int N, int M) {
  // variables declaration
  int maxStudentIdx = 0;
  int maxCourseIdx = 0;
  int maxVal = -1;

  for(int cn = 0; cn < C; cn++) {
    for(int sn = 0; sn < N; sn++) {
      if(courses[cn][sn].total > maxVal) {
        maxVal = courses[cn][sn].total;
        maxStudentIdx = sn;
        maxCourseIdx = cn;
      }
    }
  }

  //--------------To Be Done By You-- ----------------------------
              // print the name, then the assignment and then the quizzes adn
              // their grades both to the console and to the terminal
              // sample
              printf("Name: %s\n", courses[maxCourseIdx][maxStudentIdx].lname);

  // do the same for the Assignment here in the next two lines
  printf("Assignment: %d\n", courses[maxCourseIdx][maxStudentIdx].assignment);
  // print the quizzes
  printf("Quizzes: ");
  for (int q = 0; q < M; q++) {
    printf("%d ", courses[maxCourseIdx][maxStudentIdx].quizzes[q]);
  }

  // Use the same strategy (without a loop) to build the rest of the printf and
  // fprintf statements for -> final exam / total / course number

  printf("\nFinal exam: %d\n", courses[maxCourseIdx][maxStudentIdx].finalExam);
  printf("Total: %d\n", courses[maxCourseIdx][maxStudentIdx].total);
  printf("Course number: %d\n", (maxCourseIdx+1));
}

// function that takes the array of courses that is a 2d array and then frees
// all the memory allocated within it then frees the whole array afterwards
// ->the function takes the number of courses, students and quizzes along with
// the array of courses
void release_memroy(student **st, int C, int N, int M) {

  /*
      strategy:
          free the most inner elements first then backtrack to free the
     containers
  */

  // In other words: we need to release each quizzes array for each student,
  // their name and then release the students and then courses.
  for (int cn = 0; cn < C; cn++) {

    for (int sn = 0; sn < N; sn++) {

      free(st[cn][sn].lname);
      free(st[cn][sn].quizzes);
    }

    // releasing the students in that course
    free(st[cn]);
  }

  // releasing the array of courses at the end
  free(st);
}

// driver function
int main() {

  // Important!!
  atexit(report_mem_leak); // for memory leak detector.

  // we need to create a 2d array that represents an array of arrays
  // to hold the courses and each course has an array of students
  student **courseList;

  /*
      number of Courses -> C
      number of students -> N
      number of quizzes -> M

      -> these are inputs from the first line of the input file.
  */
  int C, N, M;

  // passing reference of C, N, and M so that we get to know what we have in the
  // file
  courseList = readCourses(&C, &N, &M);

  // print the data
  printHighestTotal(courseList, C, N, M);

  // good habit: for C programming it is better to either free the memory
  // straight after you use it or have a function that does all the freeing
  // process for you at the end such as this one
  release_memroy(courseList, C, N, M);

  // end of the main file
  return 0;
}