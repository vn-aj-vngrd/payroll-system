#ifndef DATABASE_H
#define DATABASE_H

#include <Schema.h>

#define SIZE 100

typedef int ID;
typedef int Elempos;

union dictionary
{
    PSU UserD[SIZE];
} User;

typedef struct
{
    PSJI JobInformationD[SIZE];
} JobInformation;

typedef struct
{
    PSA AttendanceD[SIZE];
} Attendance;

typedef struct
{
    PSIS IssueSalaryD[SIZE];
} IssueSalary;

typedef struct
{
    PSB BonusD[SIZE];
} Bonus;

void initDictionary(Dictdatatype D)
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        D[i] = NULL;
    }
}

Elempos hashFunc(ID id)
{
    return id % 100;
}

// D = Database
// Set D = First letter of Database Name
int getNewID(char fileName[], char D)
{
    int lastID, size;
    FILE *fp = fopen(fileName, "rb");
    if(fp != NULL)
    {
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        if(size > 0)
        {
            switch (D)
            {
                case 'U':
                    lastID = size / sizeof(Schema_User);
                    break;
                case 'J':
                    lastID = size / sizeof(Schema_JobInformation);
                    break;
                case 'A':
                    lastID = size / sizeof(Schema_Attendance);
                    break;
                case 'I':
                    lastID = size / sizeof(Schema_IssueSalary);
                    break;
                case 'B':
                    lastID = size / sizeof(Schema_Bonus);
                    break;
            }
            return lastID + 1;  
        }
        else
        {
            printf("File is Empty");
        }
    }
}

// User CRUD
// Returns node
void getUser(ID id)
{
}

#endif