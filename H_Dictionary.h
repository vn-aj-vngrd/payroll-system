#ifndef DATABASE_H
#define DATABASE_H

#define DICT_SIZE 10

#include "H_Model.h"

typedef int ID;
typedef int ElemPos;

// Linked List Node
// Datatype Format:
//      PSU = Pointer Schema User
//      PSA = Pointer Schema Attendance
//      etc

typedef struct node1
{
    Schema_Attendance data;
    struct node1 *next;
} NodeAttendance, *PSA;

typedef struct node2
{
    Schema_Bonus data;
    struct node2 *next;
} NodeBonus, *PSB;

typedef struct node3
{
    Schema_IssueSalary data;
    struct node3 *next;
} NodeIssueSalary, *PSIS;

typedef struct node4
{
    Schema_JobInformation data;
    struct node4 *next;
} NodeJobInformation, *PSJI;

typedef struct node5
{
    Schema_User data;
    struct node5 *next;
} NodeUser, *PSU;

// Dictionary
typedef struct
{
    PSA AttendanceD[DICT_SIZE];
    PSB BonusD[DICT_SIZE];
    PSIS IssueSalaryD[DICT_SIZE];
    PSJI JobInformationD[DICT_SIZE];
    PSU UserD[DICT_SIZE];
    int count[5];
} Dictionary, *dPtr;

#endif