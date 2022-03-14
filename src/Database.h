#ifndef DATABASE_H
#define DATABASE_H

#include <Schema.h>

#define SIZE 100

typedef int ID;
typedef int Elempos;

typedef struct
{
    typedef PSU Dictionary[SIZE];
} User;

typedef struct
{
    typedef PSJI Dictionary[SIZE];
} JobInformation;

typedef struct
{
    typedef PSA Dictionary[SIZE];
} Attendance;

typedef struct
{
    typedef PSIS Dictionary[SIZE];
} IssueSalary;

typedef struct
{
    typedef PSB Dictionary[SIZE];
} Bonus;

void init(Dictionary D)
{
    int i;
    for(i=0; i<SIZE; i++){
        D[i]=NULL;
    }
}

Elempos hashFunc(ID id)
{
    return id % 100;
}



#endif