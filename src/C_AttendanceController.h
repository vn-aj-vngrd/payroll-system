#ifndef ATTENDANCECONTROLLER_H
#define ATTENDANCECONTROLLER_H

#include "H_Libraries.h"
#include "H_Schema.h"
#include "H_Model.h"
#include "C_DictionaryController.h"

bool insertAttendance(Dictionary *D, Schema_Attendance data)
{
    PSA *trav;
    int hashVal = hash(data.attendanceID);

    for (trav = &(D->AttendanceD[hashVal]); *trav != NULL; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        trav = (PSA *)malloc(sizeof(Schema_Attendance));
        if (*trav != NULL)
        {
            (*trav)->data = data;
            (*trav)->next = NULL;
        }
        D->count[3]++;
        printf("Attendance Inserted Successfully\n");
    }
    else
    {
        printf("Attendance ID already exists\n");
        return false;
    }
}

bool updateAttendance(Dictionary *D, Schema_Attendance data, Schema_Attendance *pointer)
{
    if (data.attendanceID != pointer->attendanceID)
    {
        return false;
    }
    else
    {
        *pointer = data;
        return true;
    }
}

bool deleteAttendance(Dictionary *D, int ID)
{
    PSA *trav, temp;
    int hashVal = hash(ID);

    for (trav = &(D->AttendanceD[hashVal]); *trav != NULL && (*trav)->data.attendanceID != ID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        printf("Attendance ID not found\n");
        return false;
    }
    else
    {
        temp = *trav;
        *trav = (*trav)->next;
        free(temp);
        D->count[3]++;
        printf("Attendance Deleted Successfully\n");
        return true;
    }
}

Schema_Attendance *searchAttendance(Dictionary D, ID employeeID)
{
    PSA trav, temp;
    int hashVal = hash(employeeID);

    for (trav = D.AttendanceD[hashVal]; trav != NULL && trav->data.employeeID != employeeID; trav = trav->next)
    {
    }

    if (trav != NULL)
    {
        // Schema_Attendance *data = (Schema_Attendance *)malloc(sizeof(Schema_Attendance));
        // *data = trav->data;
        return &trav->data;
    }
    else
    {
        printf("Attendance ID not found\n");
        return NULL;
    }
}

void displayAllAttendance(Dictionary D)
{
    PSA trav;
    int i;

    printf("DICTIONARY ATTENDANCE\n");
    printf("%4s | %4s\n", "row", "ID");
    for (i = 0; i < DICT_SIZE; i++)
    {
        printf("%4d | ", i);
        for (trav = D.AttendanceD[i]; trav != NULL; trav = trav->next)
        {
            printf("%d -> ", trav->data.attendanceID);
        }
        printf("\n", i);
    }

    if (trav == NULL && i == DICT_SIZE - 1)
    {
        printf("End of Dictionary\n");
    }
}

// void setLeave(int employeeID, Dictionary *D)
// {
//     Schema_Attendance *sa = searchAttendance(*D, employeeID);
//     if (sa)
//     {
//         sa->excused += 1;

//         bool b = updateAttendance(D, *sa);
//         if (b)
//         {
//             printf("Leave has been recorded.");
//         }
//         else
//         {
//             printf("Database Error!");
//         }
//     }
//     else
//     {
//         printf("\n\tEmployee not found.");
//     }
// }

// void setAbsence(int employeeID, Dictionary *D)
// {
//     Schema_Attendance *sa = searchAttendance(*D, employeeID);
//     if (sa)
//     {
//         sa->absent += 1;

//         bool b = updateAttendance(D, *sa);
//         if (b)
//         {
//             printf("Absence has been recorded.");
//         }
//         else
//         {
//             printf("Database Error!");
//         }
//     }
//     else
//     {
//         printf("\n\tEmployee not found.");
//     }
// }

// void setOvertime(int employeeID, Dictionary *D)
// {
//     int otHours;
//     Schema_Attendance *sa = searchAttendance(*D, employeeID);
//     if (sa)
//     {
//         printf("Enter No. of Overtime Hours: ");
//         scanf("%d", &otHours);
//         sa->overtime += otHours;

//         bool b = updateAttendance(D, *sa);
//         if (b)
//         {
//             printf("Overtime hours has been recorded.");
//         }
//         else
//         {
//             printf("Database Error!");
//         }
//     }
//     else
//     {
//         printf("\n\tEmployee not found.");
//     }
// }

#endif