#ifndef ATTENDANCECONTROLLER_H
#define ATTENDANCECONTROLLER_H

#include "H_Libraries.h"
#include "H_Schema.h"
#include "H_Model.h"
#include "C_DictionaryController.h"

Schema_Attendance createAttendance(Dictionary D)
{
    Schema_Attendance sa;
    int empID;

    printf("Create Employee Attendance");

    char dType[10] = "Attendance";
    sa.attendanceID = getNewID(dType, D);

    printf("Enter Employee ID: ");
    scanf("%d", &empID);

    Schema_Attendance *temp = searchAttendance(D, empID);
    if (temp)
    {
        printf("\nEmployee already exists");
        return;
    }
    else
    {
        sa.employeeID = empID;
        sa.present = 0;
        sa.absent = 0;
        sa.leave = 0;
        sa.overtime = 0;
        printf("Enter current month [MM/YY]: ");
        scanf("%s", sa.period);

        return sa;
    }
}

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
        return true;
    }
    else
    {
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
        return NULL;
    }
}

bool displayAttendance(Dictionary *D, int employeeID)
{
    Schema_Attendance *emp = searchUser(*D, employeeID);
    if (emp)
    {
        printf("|  Attendance ID:       \t%d  |", emp->attendanceID);
        printf("|  Employee ID:         \t%d  |", emp->employeeID);
        printf("|  Present:             \t%s  |", emp->present);
        printf("|  Absent               \t%s  |", emp->absent);
        printf("|  Leave:               \t%s  |", emp->leave);
        printf("|  Overtime:            \t%s  |", emp->overtime);
        printf("|  Period:              \t%d  |", emp->period);
        return true;
    }
    else
    {
        return false;
    }
}

bool setPresent(int employeeID, Dictionary *D)
{
    int presentNum;
    Schema_Attendance *sa = searchAttendance(*D, employeeID);
    if (sa)
    {
        printf("Enter No. of Present Days: ");
        scanf("%d", &presentNum);
        sa->present += presentNum;
        return true;
    }
    else
    {
        return false;
    }
}

bool setLeave(int employeeID, Dictionary *D)
{
    int leaveNum;
    Schema_Attendance *sa = searchAttendance(*D, employeeID);
    if (sa)
    {
        printf("Enter No. of Leave Days: ");
        scanf("%d", &leaveNum);
        sa->leave += leaveNum;
        return true;
    }
    else
    {
        return false;
    }
}

bool setAbsent(int employeeID, Dictionary *D)
{
    int absentNum;
    Schema_Attendance *sa = searchAttendance(*D, employeeID);
    if (sa)
    {
        printf("Enter No. of Absent Days: ");
        scanf("%d", &absentNum);
        sa->absent += absentNum;

        return true;
    }
    else
    {
        return false;
    }
}

bool setOvertime(int employeeID, Dictionary *D)
{
    int otHours;
    Schema_Attendance *sa = searchAttendance(*D, employeeID);
    if (sa)
    {
        printf("Enter No. of Overtime Hours: ");
        scanf("%d", &otHours);
        sa->overtime += otHours;

        return true;
    }
    else
    {
        return false;
    }
}

void displayAllAttendance(Dictionary D)
{
    PSA trav;
    int i;

    printf("%4s_|_%14s_|_%12s_|_%8s_|_%7s_|_%8s_|_%9s_|_%7s\n",
           "____",
           "______________",
           "____________",
           "________",
           "_______",
           "________",
           "_________",
           "_______");
    printf("ATTENDANCE\n");
    printf("%4s_|_%14s_|_%12s_|_%8s_|_%7s_|_%8s_|_%9s_|_%7s\n",
           "____",
           "______________",
           "____________",
           "________",
           "_______",
           "________",
           "_________",
           "_______");
    printf("%-4s | %-14s | %-12s | %-8s | %-7s | %-8s | %-9s | %-7s\n",
           "#",
           "ATTENDANCE ID",
           "EMPLOYEE ID",
           "PRESENT",
           "ABSENT",
           "LEAVE",
           "OVERTIME",
           "PERIOD");

    for (i = 0; i < DICT_SIZE; i++)
    {
        for (trav = D.AttendanceD[i]; trav != NULL; trav = trav->next)
        {
            printf("%4d | %14d | %12d | %8d | %7d | %8d | %9d | %-7s\n",
                   i,
                   trav->data.attendanceID,
                   trav->data.employeeID,
                   trav->data.present,
                   trav->data.absent,
                   trav->data.leave,
                   trav->data.overtime,
                   trav->data.period);
        }
    }

    if (trav == NULL && i == DICT_SIZE - 1)
    {
        printf("%4s_|_%14s_|_%12s_|_%8s_|_%7s_|_%8s_|_%9s_|_%7s\n",
               "____",
               "______________",
               "____________",
               "________",
               "_______",
               "________",
               "_________",
               "_______");
        printf("End of Dictionary\n");
    }
}

void debugAttendance(Dictionary D)
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

#endif