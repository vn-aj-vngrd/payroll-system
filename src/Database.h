#ifndef DATABASE_H
#define DATABASE_H

#define SIZE 100

#include "Libraries.h"
#include "Schema.h"

typedef int ID;
typedef int Elempos;

// Linked Lists
typedef struct node1
{
    Schema_User data;
    struct node1 *next;
} ListUser, *PSU;

typedef struct node2
{
    Schema_JobInformation data;
    struct node2 *next;
} ListJobInformation, *PSJI;

typedef struct node3
{
    Schema_Attendance data;
    struct node3 *next;
} ListAttendance, *PSA;

typedef struct node4
{
    Schema_IssueSalary data;
    struct node4 *next;
} ListIssueSalary, *PSIS;

typedef struct node5
{
    Schema_Bonus data;
    struct node5 *next;
} ListBonus, *PSB;

// Dictionary
typedef struct
{
    PSU UserD[SIZE];
    PSJI JobInformationD[SIZE];
    PSA AttendanceD[SIZE];
    PSIS IssueSalaryD[SIZE];
    PSB BonusD[SIZE];
} Dictionary;

void initDictionary(Dictionary D)
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        D.UserD[i] = NULL;
        D.JobInformationD[i] = NULL;
        D.AttendanceD[i] = NULL;
        D.IssueSalaryD[i] = NULL;
        D.BonusD[i] = NULL;
    }
}

Elempos hashFunc(ID id)
{
    return id % 100;
}

// D = Database
// Set D = First letter of Database Name
int getNewID(char fileName[], int D)
{
    int lastID, size;
    FILE *fp = fopen(fileName, "rb");
    if (fp != NULL)
    {
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        if (size > 0)
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
            printf("File is Empty\n");
        }
    }
}

/*
 *  Employee Information Controller
 **/

void insertEmployeeInformation(Dictionary D, Schema_User data)
{
    PSU *trav;
    int hashVal = hashFunc(data.userID);

    for (trav = &(D.UserD[hashVal]); *trav != NULL; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        trav = (PSU *)malloc(sizeof(Schema_User));
        if (*trav != NULL)
        {
            (*trav)->data = data;
            (*trav)->next = NULL;
        }
        printf("Employee Inserted Successfully\n");
    }
}

void updateEmployeeInformation(Dictionary D, Schema_User data)
{
    PSU *trav;
    int hashVal = hashFunc(data.userID);

    for (trav = &(D.UserD[hashVal]); *trav != NULL && (*trav)->data.userID != data.userID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        printf("Employee ID not found\n");
    }
    else
    {
        (*trav)->data = data;
        printf("Employee Updated Successfully\n");
    }
}

void deleteEmployeeInformation(Dictionary D, Schema_User data)
{
    PSU *trav, temp;
    int hashVal = hashFunc(data.userID);

    for (trav = &(D.UserD[hashVal]); *trav != NULL && (*trav)->data.userID != data.userID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        printf("Employee ID not found\n");
    }
    else
    {
        temp = *trav;
        *trav = (*trav)->next;
        free(temp);
        printf("Employee Deleted Successfully\n");
    }
}

Schema_User *searchEmployeeInformation(Dictionary D, Schema_User data)
{
    PSU trav, temp;
    int hashVal = hashFunc(data.userID);

    for (trav = D.UserD[hashVal]; trav != NULL && trav->data.userID != data.userID; trav = trav->next)
    {
    }

    if (trav != NULL)
    {
        // Schema_User *data = (Schema_User *)malloc(sizeof(Schema_User));
        // *data = trav->data;
        return &trav->data;
    }
    else
    {
        printf("Employee ID not found\n");
        return NULL;
    }
}

#endif