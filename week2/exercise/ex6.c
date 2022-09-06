#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int student_id;
    float *quizzes;
};

struct Student * AllocateStudents(int N, int Q) {
    struct Student * students = (struct Student *)malloc(sizeof(struct Student) * N);
    for(int i = 0; i < N; i++) {
        students[i].quizzes = (float *)malloc(sizeof(float) * Q);
        printf("Enter student id\n");
        scanf("%d", &students[i].student_id);
        for(int j = 0; j < Q; j++) {
             printf("Enter quiz %d\n", (j+1));
             scanf("%f", &students[i].quizzes[j]);
        }
        printf("%d %f\n", students[i].student_id, students[i].quizzes[0]);
    }

    return students;
}

void free_up_memory(struct Student* students, int N) {
    for(int i = 0; i < N; i++) {
        free(students[i].quizzes);
    }

    free(students);
}

int main(void) {
    struct Student *students = AllocateStudents(5, 2);
    free_up_memory(students, 5);

    return 0;
}