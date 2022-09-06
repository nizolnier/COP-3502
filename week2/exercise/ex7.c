#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
    int student_id;
    float *quizzes;
} Student;

Student** AllocateCourse_Students(int C, int N, int Q){
    Student** courses = (Student**)malloc(C * sizeof(Student *));

    for(int i = 0; i < C; i++) {
        courses[i] = (Student *)malloc(N * sizeof(Student));

        for(int j = 0; j < N; j++) {
            courses[i][j].quizzes = (float *)malloc(Q * sizeof(float));
        }
        
    }

    return courses;
}
void FreeCourse_Students(Student** courses, int N, int Q) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < Q; j++) {
            free(courses[i][j].quizzes);
        }
        free(courses[i]);
    }

    free(courses);
}

int main(void) {


    return 0;
}