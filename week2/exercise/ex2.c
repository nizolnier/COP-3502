#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee
{
    char *first; // Employee's first name.
    char *last;  // Employee's last name.
    int ID;      // Employee ID.
} Employee;

Employee *makeArray(char **firstNames, char **lastNames, int *IDs, int n)
{
    int i;
    Employee *array = (Employee *)malloc(n * sizeof(Employee));
    for (i = 0; i < n; i++)
    {
        array[i].first = malloc(sizeof(char) * (strlen(firstNames[i]) + 1));
        array[i].last = malloc(sizeof(char) * (strlen(lastNames[i]) + 1));
        strcpy(array[i].first, firstNames[i]);
        strcpy(array[i].last, lastNames[i]);
        array[i].ID = IDs[i];

        printf("%s %s - %d", array[i].first, array[i].last, array[i].ID);
    }
    return array;
}

void freeEmployeeArray(Employee *array, int n) {
    int i;
    for (i = 0; i < n; i++)
    {    
        free(array[i].first);
        free(array[i].last);
    }

    free(array);
}

int main(void)
{
    char *firstNames[] = {"jim", "dwight"};
    char *lastNames[] = {"halpert", "schrute"};
    int ids[] = {11, 22};
    int n = 2;

    Employee * employees = makeArray(firstNames, lastNames, ids, n);
    freeEmployeeArray(employees, n);



    return 0;
}