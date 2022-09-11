/* COP 3502C Assignment 1
This program is written by: Nicole Nascimento */

// pre-processor directives
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "leak_detector_c.h"

// constant for the maximum length of the string
#define STRINGMAX 51

// structs provided :)
typedef struct monster
{
    char *name;
    char *element;
    int population;
} monster;

typedef struct region
{
    char *name;
    int nmonsters;
    int total_population;
    monster **monsters;
} region;

typedef struct itinerary
{
    int nregions;
    region **regions;
    int captures;
} itinerary;

typedef struct trainer
{
    char *name;
    itinerary *visits;
} trainer;

/* function that receives a name, element, population and returns a dma monster */
monster *makeMonster(char *name, char *element, int population)
{
    // allocating space for the monster
    monster *monst = (monster *)malloc(sizeof(monster));

    // allocating space for the two strings in the struct
    monst->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    monst->element = (char *)malloc(sizeof(char) * (strlen(element) + 1));

    // using strcpy to set the value of the string
    strcpy(monst->name, name);
    strcpy(monst->element, element);
    // setting the population
    monst->population = population;

    // return the monster
    return monst;
}

// function that receives a name, number of monsters, total population and an array of monster pointers
// returns a dma region
region *makeRegion(char *name, int nmonsters, int total_population, monster **monsters)
{
    // allocating space for region
    region *regi = (region *)malloc(sizeof(region));

    // allocating space for the string and using strcpy to set the value
    regi->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(regi->name, name);

    // setting the rest of the integers
    regi->nmonsters = nmonsters;
    regi->total_population = total_population;
    // setting the array of monster pointers
    regi->monsters = monsters;

    // returning the region
    return regi;
}

/* function that receives a number of monsters as pointers, allocates memory for an array of monster pointers,
fills it with the information and returns the array of monster pointers */
monster **readMonsters(int *monsterCount)
{
    // declaring the temp variables
    // a garbage string for when i scan the "8 monsters" in the in.txt file the "monsters" go in there
    char garbage[STRINGMAX];
    char name[STRINGMAX];
    char element[STRINGMAX];
    int population;
    // scanning the monsters count and saving it
    scanf("%d %s", monsterCount, garbage);
    // allocating space for monsters array by using monsters count
    monster **monstersArray = (monster **)malloc(sizeof(monster *) * *monsterCount);

    // for each monster, i scan the name, element and population
    // then i create the monsters by using the makeMonster function
    for (int i = 0; i < *monsterCount; i++)
    {
        scanf("%s %s %d", name, element, &population);
        monstersArray[i] = makeMonster(name, element, population);
    }

    // return the monsters array at the end
    return monstersArray;
}

/* function that receives a count for the regions, a monsters list and the monster count,
allocates memory for an array of region pointers, fills the info and returns the array */
region **readRegions(int *countRegions, monster **monsterList, int monsterCount)
{
    // declaring the temp variables and the garbage (which i already explained the purpose)
    char garbage[STRINGMAX];
    char name[STRINGMAX];
    char monstName[STRINGMAX];

    // scanning the amount of regions
    scanf("%d %s", countRegions, garbage);

    // allocating memory for the regions by using the count
    region **regions = (region **)malloc(sizeof(region *) * *countRegions);

    // for each region, i scan the name, the amount of monsters in that region and then the fun begins
    for (int i = 0; i < *countRegions; i++)
    {
        int nmonsts = 0;
        int total_population = 0;
        scanf("%s", name);
        scanf("%d %s", &nmonsts, garbage);
        // once i have the amount of monsters in the region, i allocate memory for a region monster list
        monster **regionMonsterList = (monster **)malloc(sizeof(monster *) * nmonsts);

        // then for each element of the region monster list
        for (int j = 0; j < nmonsts; j++)
        {
            // i scan the name
            scanf("%s", monstName);
            // but having the name is not enough! i need the entire struct sooo
            // bang! another loop
            // this time, i loop through the original array of monster pointers
            for (int k = 0; k < monsterCount; k++)
            {
                // if the name i just scanned and the name that is on the original array is a match,
                // i copy that monster into the region monster list
                if (strcmp(monsterList[k]->name, monstName) == 0)
                {
                    regionMonsterList[j] = monsterList[k];
                }
            }
            // then i just sum up all the populations
            total_population += regionMonsterList[j]->population;
        }

        // then call the makeRegion to make a beautiful region
        regions[i] = makeRegion(name, nmonsts, total_population, regionMonsterList);

        printf("total pop: %d", regions[i]->total_population);
    }

    return regions;
}

/* function that receives a count for trainers, the array of region pointers and the count for regions
returns an array of trainers */
trainer *loadTrainers(int *trainerCount, region **regionList, int countRegions)
{
    // declaring the temp variables i will need
    char garbage[STRINGMAX];
    char name[STRINGMAX];
    char regionName[STRINGMAX];
    int captures, nRegions;
    // scanning trainer count
    scanf("%d %s", trainerCount, garbage);

    // allocating memory for trainers by using trainers count
    trainer *trainers = (trainer *)malloc(sizeof(trainer) * *trainerCount);

    // for each trainer, i
    for (int i = 0; i < *trainerCount; i++)
    {
        // allocate memory for the visits
        trainers[i].visits = (itinerary *)malloc(sizeof(itinerary));

        // scan the name, allocate memory for the name, set the name
        scanf("%s", name);
        trainers[i].name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
        strcpy(trainers[i].name, name);

        // scan the number of captures
        scanf("%d %s", &captures, garbage);
        trainers[i].visits->captures = captures;

        // scan the number of regions and allocate memory for the trainers regions
        // each trainer has its own array of region pointers
        scanf("%d %s", &nRegions, garbage);
        trainers[i].visits->nregions = nRegions;
        region **trainersRegions = (region **)malloc(sizeof(region *) * nRegions);

        // for each region in the trainers regions
        for (int j = 0; j < nRegions; j++)
        {
            /// i scan the name
            scanf("%s", regionName);

            // then i do the same thing as in readRegions but this time is for regions
            // so i loop through the original array of region pointers, then if the name is a match, i save the region
            for (int k = 0; k < countRegions; k++)
            {
                if (strcmp(regionList[k]->name, regionName) == 0)
                {
                    trainersRegions[j] = regionList[k];
                }
            }
        }

        // then i set the regions as the array i just created
        trainers[i].visits->regions = trainersRegions;
    }

    // then i return the array of trainers
    return trainers;
}

/* function that receives the three arrays and their lengths and prints with the correct output */
void processInputs(monster **monsterList, int monsterCount, region **regionList, int regionCount,
                   trainer *trainerList, int trainerCount)
{
    // for each trainer
    for (int i = 0; i < trainerCount; i++)
    {
        // i print their name
        printf("%s\n", trainerList[i].name);
        // loop through the regions
        for (int j = 0; j < trainerList[i].visits->nregions; j++)
        {
            // print the name of the region
            printf("%s\n", trainerList[i].visits->regions[j]->name);
            // then for each monster in the region, the fun begins!
            for (int k = 0; k < trainerList[i].visits->regions[j]->nmonsters; k++)
            {
                // (pop M / total pop R) * (captures) = coefficient
                // this is the formula, so i just get all the variables i need and calculate it
                // i do need to cast one of them to doubles for me to round it later
                // i broke everything into multiple variables so it is easier to see
                double mPopOverTotalPop = trainerList[i].visits->regions[j]->monsters[k]->population / (double)trainerList[i].visits->regions[j]->total_population;

                double coefficient = mPopOverTotalPop * trainerList[i].visits->captures;

                // here i round the coefficient and if it is bigger than 0, i print it + the name of the monster
                int roundCoefficient = round(coefficient);
                if (roundCoefficient > 0)
                {
                    printf("%d#%s\n", roundCoefficient, trainerList[i].visits->regions[j]->monsters[k]->name);
                }
            }
        }
        printf("\n");
    }
}

/* function that receives the three arrays, their length and frees the memory of each malloc */
void releaseMemory(monster **monsterList, int monsterCount, region **regionList, int regionCount,
                   trainer *trainerList, int trainerCount)
{
    // counter that i use for all three loops
    int i;
    // so 3 loops, 3 things inside each loop + 1 thing at the end

    // in trainers, i need to free the name, the regions in visits and the visits
    for (i = 0; i < trainerCount; i++)
    {
        free(trainerList[i].name);
        free(trainerList[i].visits->regions);
        free(trainerList[i].visits);
    }

    // once that is done, i can free trainers
    free(trainerList);

    // in the array of region pointers, i need to free the name, the array of monster pointers and the region
    for (i = 0; i < regionCount; i++)
    {
        free(regionList[i]->name);
        free(regionList[i]->monsters);
        free(regionList[i]);
    }

    // once that is done, i can free the array of region pointers
    free(regionList);

    // in the array of monster pointers, i need to free the name, the element and the region
    for (int i = 0; i < monsterCount; i++)
    {
        free(monsterList[i]->name);
        free(monsterList[i]->element);
        free((monsterList[i]));
    }

    // once that is done, i can free the array of monster pointers
    free(monsterList);
}

int main(void)
{
    // leak report
    atexit(report_mem_leak);

    // declaring variables for the count
    int mcount, rcount, tcount;
    // calling all the functions and saving the returns in appropriate variables
    monster **slayMonsters = readMonsters(&mcount);
    region **slayRegions = readRegions(&rcount, slayMonsters, mcount);
    trainer *slayTrainers = loadTrainers(&tcount, slayRegions, rcount);

    // here is where i print everything, a lot of paramaters oof
    processInputs(slayMonsters, mcount, slayRegions, rcount, slayTrainers, tcount);

    // then i call release memory because leaks are not fun
    releaseMemory(slayMonsters, mcount, slayRegions, rcount, slayTrainers, tcount);

    // and that's it folks :)
    return 0;
}