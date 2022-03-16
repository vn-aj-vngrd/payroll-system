#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "H_Schema.h"
#include "H_Dictionary.h"

/*---------------------------------- Dictionary Function Headers ----------------------------------*/

void initDictionary(Dictionary *D);
ElemPos hash(ID id);
int getNewID(char DictionaryType[], Dictionary D);
bool pullDictionaries(Dictionary *D);
bool pushDictionaries(Dictionary D);

/*---------------------------------- Attendance Function Headers ----------------------------------*/

Schema_Attendance *searchAttendance(Dictionary D, ID employeeID);
Schema_Attendance createAttendance(Dictionary D);
bool insertAttendance(Dictionary *D, Schema_Attendance data);
bool updateAttendance(Dictionary *D, Schema_Attendance data, Schema_Attendance *pointer);
bool deleteAttendance(Dictionary *D, int ID);
bool displayAttendance(Dictionary *D, int employeeID);
bool setPresent(int employeeID, Dictionary *D);
bool setLeave(int employeeID, Dictionary *D);
bool setAbsent(int employeeID, Dictionary *D);
bool setOvertime(int employeeID, Dictionary *D);
void displayAllAttendance(Dictionary D);
void debugAttendance(Dictionary D);

/*----------------------------------- Bonus Function Headers -------------------------------------*/

Schema_Bonus createBonus(Dictionary D);
bool insertBonus(Dictionary *D, Schema_Bonus data);
bool updateBonus(Dictionary *D, Schema_Bonus data, Schema_Bonus *pointer);
bool deleteBonus(Dictionary *D, ID bonusID);
Schema_Bonus *searchBonus(Dictionary D, ID bonusID, char period[]);
bool debugBonus(Dictionary D);
bool displayAllBonus(Dictionary D);
bool displayBonus(int bonusID, Dictionary *D);

/*---------------------------------- Issue Salary Function Headers -----------------------------*/

Schema_IssueSalary createIssueSalary(Dictionary D, int employeeID, double balance, char period[]);
bool insertIssueSalary(Dictionary *D, Schema_IssueSalary data);
bool updateIssueSalary(Dictionary *D, Schema_IssueSalary data, Schema_IssueSalary *pointer);
bool deleteIssueSalary(Dictionary *D, ID issueID);
Schema_IssueSalary *searchIssueSalary(Dictionary D, ID userID, char period[]);
void debugSalary(Dictionary D);
bool displayAllSalary(Dictionary D);
bool displayIssueSalary(ID issueID, Dictionary *D);
bool issueSalary(int empID, Dictionary *D);
double calculateTax(double taxableIncome, double *pagibigDeposit);

/*---------------------------------- Job Information Function Headers -------------------------------------*/

Schema_JobInformation createJobInformation(Dictionary D, ID employeeID);
bool insertJobInformation(Dictionary *D, Schema_JobInformation data);
bool updateJobInformation(Dictionary *D, Schema_JobInformation data, Schema_JobInformation *pointer);
bool deleteJobInformation(Dictionary *D, ID employmentID);
Schema_JobInformation *searchJobInformation(Dictionary D, ID employmentID);
bool debugJobInformation(Dictionary D);
bool displayAllJobInformation(Dictionary D);
bool displayJobInformation(ID employeeID, Dictionary *D);

/*---------------------------------- User Function Headers ------------------------------------*/

Schema_User createUserInformation(Dictionary D);
bool insertUser(Dictionary *D, Schema_User data);
bool updateUser(Dictionary *D, Schema_User data, Schema_User *pointer);
bool deleteUser(Dictionary *D, ID userID);
Schema_User *searchUser(Dictionary D, ID userID);
bool debugUser(Dictionary D);
bool displayAllUser(Dictionary D);
bool displayUserInformation(ID userID, Dictionary *D);

/*-------------------------------- Start of Functions Definitions ----------------------------------*/

void initDictionary(Dictionary *D)
{
    int i;
    for (i = 0; i < DICT_SIZE; i++)
    {
        D->UserD[i] = NULL;
        D->JobInformationD[i] = NULL;
        D->AttendanceD[i] = NULL;
        D->IssueSalaryD[i] = NULL;
        D->BonusD[i] = NULL;
    }

    for (i = 0; i < 5; i++)
    {
        D->count[i] = 0;
    }
}

ElemPos hash(ID id)
{
    return id % 100;
}

int getNewID(char DictionaryType[], Dictionary D)
{
    int lastID;

    if (strcmp(DictionaryType, "Attendance") == 0)
    {
        lastID = D.count[0];
    }
    else if (strcmp(DictionaryType, "Bonus") == 0)
    {
        lastID = D.count[1];
    }
    else if (strcmp(DictionaryType, "IssueSalary") == 0)
    {
        lastID = D.count[2];
    }
    else if (strcmp(DictionaryType, "JobInformation") == 0)
    {
        lastID = D.count[3];
    }
    else if (strcmp(DictionaryType, "User") == 0)
    {
        lastID = D.count[4];
    }
    else
    {
        printf("Invalid Dictionary Type\n");
        return -1;
    }

    return lastID + 1;
}

bool pullDictionaries(Dictionary *D)
{
    // Attendance Information
    FILE *fp = fopen("Employee_Attendance.bin", "rb");
    Schema_Attendance attendance;

    if (fp)
    {
        while (fread(&attendance, sizeof(Schema_Attendance), 1, fp))
        {
            insertAttendance(D, attendance);
        }

        fclose(fp);
    }
    else
    {
        return false;
    }

    // Bonus Information
    fp = fopen("Employee_Bonus.bin", "rb");
    Schema_Bonus bonus;

    if (fp)
    {
        while (fread(&bonus, sizeof(Schema_Bonus), 1, fp))
        {
            insertBonus(D, bonus);
        }
        fclose(fp);
    }
    else
    {
        return false;
    }

    // Job Information
    fp = fopen("Employee_JobInformation.bin", "rb");
    Schema_JobInformation jobinfo;

    if (fp)
    {
        while (fread(&jobinfo, sizeof(Schema_JobInformation), 1, fp))
        {
            insertJobInformation(D, jobinfo);
        }
        fclose(fp);
    }
    else
    {
        return false;
    }

    // Salary Information
    fp = fopen("Employee_IssueSalary.bin", "rb");
    Schema_IssueSalary salary;

    if (fp)
    {
        while (fread(&salary, sizeof(Schema_IssueSalary), 1, fp))
        {
            insertIssueSalary(D, salary);
        }
        fclose(fp);
    }
    else
    {
        return false;
    }

    // Employee Information
    fp = fopen("Employee_Information.bin", "rb");
    Schema_User employee;

    if (fp)
    {
        while (fread(&employee, sizeof(Schema_User), 1, fp))
        {
            insertUser(D, employee);
        }
        fclose(fp);
    }
    else
    {
        return false;
    }

    return true;
}

bool pushDictionaries(Dictionary D)
{
    PSA ATrav;
    PSB BTrav;
    PSJI JITrav;
    PSIS STrav;
    PSU UTrav;
    int i, count;

    // Attendance Information
    FILE *fp = fopen("Employee_Attendance.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (ATrav = D.AttendanceD[i]; ATrav != NULL; ATrav = ATrav->next)
            {
                fwrite(&ATrav->data, sizeof(Schema_Attendance), 1, fp);
            }
        }

        fseek(fp, 0L, SEEK_END);
        count = ftell(fp) / sizeof(Schema_Attendance);
        if (count != D.count[0])
        {
            return false;
        }
        fclose(fp);
    }
    else
    {
        return false;
    }

    // Bonus Information
    fp = fopen("Employee_Bonus.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (BTrav = D.BonusD[i]; BTrav != NULL; BTrav = BTrav->next)
            {
                fwrite(&BTrav->data, sizeof(Schema_Bonus), 1, fp);
            }
        }

        fseek(fp, 0L, SEEK_END);
        count = ftell(fp) / sizeof(Schema_Bonus);
        if (count != D.count[1])
        {
            return false;
        }

        fclose(fp);
    }
    else
    {
        return false;
    }

    // Job Information
    fp = fopen("Employee_JobInformation.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (JITrav = D.JobInformationD[i]; JITrav != NULL; JITrav = JITrav->next)
            {
                fwrite(&JITrav->data, sizeof(Schema_JobInformation), 1, fp);
            }
        }

        fseek(fp, 0L, SEEK_END);
        count = ftell(fp) / sizeof(Schema_JobInformation);
        if (count != D.count[2])
        {
            return false;
        }

        fclose(fp);
    }
    else
    {
        return false;
    }

    // Salary Information
    fp = fopen("Employee_IssueSalary.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (STrav = D.IssueSalaryD[i]; STrav != NULL; STrav = STrav->next)
            {
                fwrite(&STrav->data, sizeof(Schema_IssueSalary), 1, fp);
            }
        }

        fseek(fp, 0L, SEEK_END);
        count = ftell(fp) / sizeof(Schema_IssueSalary);
        if (count != D.count[3])
        {
            return false;
        }

        fclose(fp);
    }
    else
    {
        return false;
    }

    // User Information
    fp = fopen("Employee_Information.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (UTrav = D.UserD[i]; UTrav != NULL; UTrav = UTrav->next)
            {
                fwrite(&UTrav->data, sizeof(Schema_User), 1, fp);
            }
        }

        fseek(fp, 0L, SEEK_END);
        count = ftell(fp) / sizeof(Schema_User);
        if (count != D.count[4])
        {
            return false;
        }

        fclose(fp);
    }
    else
    {
        return false;
    }

    return true;
}

/* End of Dictionary Controller */

/* Start of Attendance Controller */

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

Schema_Attendance createAttendance(Dictionary D)
{
    Schema_Attendance sa;
    int empID;

    printf("Create Employee Attendance");

    char dType[15] = "Attendance";
    sa.attendanceID = getNewID(dType, D);

    printf("Enter Employee ID: ");
    scanf("%d", &empID);

    Schema_Attendance *temp = searchAttendance(D, empID);
    if (temp)
    {
        printf("\nEmployee already exists");
        return sa;
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

bool displayAttendance(Dictionary *D, int employeeID)
{
    Schema_Attendance *emp = searchAttendance(*D, employeeID);
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

/* End of Attendance Controller */

/* Start of Bonus Controller */

Schema_Bonus createBonus(Dictionary D)
{
    Schema_Bonus bonus;

    printf("Create Employee Bonus");

    char dType[10] = "Bonus";
    bonus.bonusID = getNewID(dType, D);

    printf("\n\tEmployee ID: ");
    scanf("%s", &bonus.employeeID);
    fflush(stdin);

    printf("\n\tBonus Name: ");
    scanf("%s", &bonus.bonusName);
    fflush(stdin);

    printf("\n\tAmount: ");
    scanf("%f", &bonus.amount);
    fflush(stdin);

    printf("\n\tPeriod (mm/dd/yy): ");
    scanf("%s", &bonus.period);
    fflush(stdin);

    return bonus;
}

bool insertBonus(Dictionary *D, Schema_Bonus data)
{
    PSB *trav;
    int hashVal = hash(data.bonusID);

    for (trav = &(D->BonusD[hashVal]); strcmp(data.bonusName, (*trav)->data.bonusName) != 0 && *trav != NULL; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        trav = (PSB *)malloc(sizeof(Schema_Bonus));
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

bool updateBonus(Dictionary *D, Schema_Bonus data, Schema_Bonus *pointer)
{
    if (data.bonusID != pointer->bonusID)
    {
        return false;
    }
    else
    {
        *pointer = data;
        return true;
    }
}

bool deleteBonus(Dictionary *D, ID bonusID)
{
    PSB *trav, temp;
    int hashVal = hash(bonusID);

    for (trav = &(D->BonusD[hashVal]); *trav != NULL && (*trav)->data.bonusID != bonusID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        return false;
    }
    else
    {
        temp = *trav;
        *trav = (*trav)->next;
        free(temp);
        D->count[3]++;
        return true;
    }
}

Schema_Bonus *searchBonus(Dictionary D, ID bonusID, char period[])
{
    PSB trav, temp;
    int hashVal = hash(bonusID);

    for (trav = D.BonusD[hashVal]; trav != NULL && trav->data.bonusID != bonusID && strcmp(trav->data.period, period) != 0; trav = trav->next)
    {
    }

    if (trav != NULL)
    {
        // Schema_Bonus *data = (Schema_Bonus *)malloc(sizeof(Schema_Bonus));
        // *data = trav->data;
        return &trav->data;
    }
    else
    {
        printf("Bonus ID not found\n");
        return NULL;
    }
}

bool debugBonus(Dictionary D)
{
    PSB trav;
    int i;

    printf("DICTIONARY BONUS\n");
    printf("%4s | %4s\n", "row", "ID");
    for (i = 0; i < DICT_SIZE; i++)
    {
        printf("%4d | ", i);
        for (trav = D.BonusD[i]; trav != NULL; trav = trav->next)
        {
            printf("%d -> ", trav->data.bonusID);
        }
        printf("\n", i);
    }

    if (trav == NULL && i == DICT_SIZE - 1)
    {
        printf("End of Dictionary\n");
        return true;
    }
    else
    {
        return false;
    }
}

bool displayAllBonus(Dictionary D)
{
    PSB trav;
    int i;

    printf("%-4s | %-9s | %-12s | %-11s | %-7s | %-7s\n",
           "____",
           "_________",
           "____________",
           "___________",
           "_______",
           "_______");
    printf("BONUS\n");
    printf("%-4s | %-9s | %-12s | %-11s | %-7s | %-7s\n",
           "____",
           "_________",
           "____________",
           "___________",
           "_______",
           "_______");
    printf("%-4s | %-9s | %-12s | %-11s | %-7s | %-7s\n",
           "#",
           "BONUS ID",
           "EMPLOYEE ID",
           "BONUS NAME",
           "AMOUNT",
           "PERIOD");

    for (i = 0; i < DICT_SIZE; i++)
    {
        for (trav = D.BonusD[i]; trav != NULL; trav = trav->next)
        {
            printf("%4d | %14d | %12d | %8d | %7d | %8d | %9d | %-7s\n",
                   i,
                   trav->data.bonusID,
                   trav->data.employeeID,
                   trav->data.bonusName,
                   trav->data.amount,
                   trav->data.period);
        }
    }

    if (trav == NULL && i == DICT_SIZE - 1)
    {
        printf("%-4s | %-9s | %-12s | %-11s | %-7s | %-7s\n",
               "____",
               "_________",
               "____________",
               "___________",
               "_______",
               "_______");
        printf("End of Dictionary\n");
        return true;
    }
    else
    {
        return false;
    }
}

bool displayBonus(int bonusID, Dictionary *D)
{
    Schema_Bonus *emp = searchUser(*D, bonusID);
    if (emp)
    {
        printf("|  Bonus ID:       \t%d  |", emp->bonusID);
        printf("|  Employee ID:    \t%d  |", emp->employeeID);
        printf("|  Bonus Name:     \t%s  |", emp->bonusName);
        printf("|  Amount          \t%f  |", emp->amount);
        printf("|  Period:         \t%s  |", emp->period);
        return true;
    }
    else
    {
        return false;
    }
}

/* End of Bonus Controller */

/* Start of Issue Salary Controller */

Schema_IssueSalary createIssueSalary(Dictionary D, int employeeID, double balance, char period[])
{
    Schema_IssueSalary is;

    is.issueID = getNewID("IssueSalary", D);
    is.employeeID = employeeID;
    is.balance = balance;
    strcpy(is.period, period);

    return is;
}

bool insertIssueSalary(Dictionary *D, Schema_IssueSalary data)
{
    PSIS *trav;
    int hashVal = hash(data.issueID);

    for (trav = &(D->IssueSalaryD[hashVal]); *trav != NULL; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        trav = (PSIS *)malloc(sizeof(Schema_IssueSalary));
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

bool updateIssueSalary(Dictionary *D, Schema_IssueSalary data, Schema_IssueSalary *pointer)
{
    if (data.issueID != pointer->issueID)
    {
        return false;
    }
    else
    {
        *pointer = data;
        return true;
    }
}

bool deleteIssueSalary(Dictionary *D, ID issueID)
{
    PSIS *trav, temp;
    int hashVal = hash(issueID);

    for (trav = &(D->IssueSalaryD[hashVal]); *trav != NULL && (*trav)->data.issueID != issueID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        return false;
    }
    else
    {
        temp = *trav;
        *trav = (*trav)->next;
        free(temp);
        D->count[3]++;
        return true;
    }
}

Schema_IssueSalary *searchIssueSalary(Dictionary D, ID userID, char period[])
{
    PSIS trav, temp;
    int hashVal = hash(userID);

    for (trav = D.IssueSalaryD[hashVal]; trav != NULL && trav->data.issueID != userID && strcmp(trav->data.period, period) != 0; trav = trav->next)
    {
    }

    if (trav != NULL)
    {
        // Schema_IssueSalary *data = (Schema_IssueSalary *)malloc(sizeof(Schema_IssueSalary));
        // *data = trav->data;
        return &trav->data;
    }
    else
    {
        return NULL;
    }
}

void debugSalary(Dictionary D)
{
    PSIS trav;
    int i;

    printf("DICTIONARY SALARY\n");
    printf("%4s | %4s\n", "row", "ID");
    for (i = 0; i < DICT_SIZE; i++)
    {
        printf("%4d | ", i);
        for (trav = D.IssueSalaryD[i]; trav != NULL; trav = trav->next)
        {
            printf("%d -> ", trav->data.issueID);
        }
        printf("\n", i);
    }

    if (trav == NULL && i == DICT_SIZE - 1)
    {
        printf("End of Dictionary\n");
    }
}

bool displayAllSalary(Dictionary D)
{
    PSIS trav;
    int i;

    printf("%-4s | %-9s | %-12s | %-8s | %7s \n",
           "____",
           "_________",
           "____________",
           "________",
           "_______");
    printf("SALARY\n");
    printf("%-4s | %-9s | %-12s | %-9s | %-8s | %7s \n",
           "____",
           "_________",
           "____________",
           "________",
           "_______");
    printf("%-4s | %-9s | %-12s | %-8s | %7s \n",
           "#",
           "ISSUE ID",
           "EMPLOYEE ID",
           "BALANCE",
           "PERIOD");

    for (i = 0; i < DICT_SIZE; i++)
    {
        for (trav = D.IssueSalaryD[i]; trav != NULL; trav = trav->next)
        {
            printf("%-4s | %-9s | %-12s | %-8s | %7s \n",
                   i,
                   trav->data.issueID,
                   trav->data.employeeID,
                   trav->data.balance,
                   trav->data.period);
        }
    }

    if (trav == NULL && i == DICT_SIZE - 1)
    {
        printf("%-4s | %-9s | %-12s | %-8s | %7s \n",
               "____",
               "_________",
               "____________",
               "________",
               "_______");
        printf("End of Dictionary\n");
        return true;
    }
    else
    {
        return false;
    }
}

bool displayIssueSalary(ID issueID, Dictionary *D)
{
    Schema_IssueSalary *emp = searchUser(*D, issueID);
    if (emp)
    {
        printf("|  Employee ID:      \t%d  |", emp->issueID);
        printf("|  First Name:       \t%d  |", emp->employeeID);
        printf("|  Gender:           \t%f  |", emp->balance);
        printf("|  Date of Birth     \t%s  |", emp->period);
        return true;
    }
    else
    {
        return false;
    }
}

bool issueSalary(int empID, Dictionary *D)
{
    int temp;
    char period[MONTH];
    int leave;
    int absent;
    int overtime;
    double additions = 0;
    double deductions = 0;
    double basicSalary;
    double dailyRate;
    double hourlyRate;
    double pagibigDeposit;
    double income;
    double tax;

    printf("Enter period (mm/yy): ");
    scanf("%s", &period);

    Schema_Attendance *sa = searchAttendance(*D, empID);
    if (sa)
    {
        leave = sa->leave;
        absent = sa->absent;
        overtime = sa->overtime;
    }
    else
    {
        printf("Employee Attendance could not be found.\n");
        return false;
    }

    Schema_JobInformation *ji = searchJobInformation(*D, empID);
    if (ji)
    {
        basicSalary = ji->basicSalary;
        pagibigDeposit = ji->pagibigDeposit;
    }
    else
    {
        printf("Employee Job Information could not be found.\n");
        return false;
    }

    Schema_Bonus *b = searchBonus(*D, empID, period);
    // check is employee has bonus
    if (b)
    {
        additions += b->amount;
    }

    dailyRate = basicSalary / 30;
    hourlyRate = dailyRate / 8;

    // check if employee has absences
    if (leave != absent)
    {
        deductions += (dailyRate * absent);
    }

    // check if employee has overtime
    if (overtime > 0)
    {
        additions += ((hourlyRate * 1.25) * overtime);
    }

    Schema_IssueSalary *is = searchIssueSalary(*D, empID, period);
    if (!is)
    {
        income = ((basicSalary + additions) - deductions);

        printf("Taxable Income: P%.2f\n", income);

        tax = calculateTax(income, &pagibigDeposit);
        income -= tax;

        printf("Tax: P%.2f\n", tax);
        printf("Issue Salary: P%.2f\n", income);
        printf("Add Issue Salary to the employee's record for period %s?\n\n", period);
        printf("[1] Yes\n");
        printf("[2] No\n");
        scanf("%d", &temp);

        switch (temp)
        {
        case 1:
            // Create new issue salary
            *is = createIssueSalary(*D, empID, income, period);
            insertIssueSalary(D, *is);
            // Update pagibig deposit
            Schema_JobInformation *ji = searchJobInformation(*D, empID);
            ji->pagibigDeposit = pagibigDeposit;
            return true;
            break;

        case 2:
            return false;
            break;

        default:
            printf("Input not recognized!");
            return false;
            break;
        }
    }
    else
    {
        printf("Issue Salary for period %s already exists!", period);
        return false;
    }
}

double calculateTax(double taxableIncome, double *pagibigDeposit)
{
    double tax = 0;

    // SSS (4%)
    tax += taxableIncome - (taxableIncome * 0.04);

    // Pag-ibig (1% or 2%, max P24,300 per year)
    if (*pagibigDeposit < 24300)
    {
        // Calculate the Pagibig tax for current month
        double pagibigTax = taxableIncome < 1500 ? taxableIncome - (taxableIncome * 0.01) : taxableIncome - (taxableIncome * 0.02);

        // Add Pagibig tax such that Pagibig deposit doesn't exceed 24300
        if (*pagibigDeposit + pagibigTax > 24300)
        {
            tax += 24300 - *pagibigDeposit;
            *pagibigDeposit += 24300 - *pagibigDeposit;
        }
        else
        {
            tax += pagibigTax;
            *pagibigDeposit += pagibigTax;
        }
    }

    // PHIC (1.75%)
    tax += taxableIncome - (taxableIncome * 0.0175);

    // WISP (P225)
    tax += taxableIncome - 225;

    // Calculate annual tax based on monthly income
    double annualTax = 0;
    double annualSalary = (taxableIncome - tax) * 12;
    if (annualSalary > 250000 && annualSalary <= 400000)
    {
        // 20%
        annualTax += (annualSalary * 0.2);
    }
    else if (annualSalary <= 800000)
    {
        // P30,000 + 25%
        annualTax += 30000 + ((annualSalary - 30000) * 0.25);
    }
    else if (annualSalary <= 2000000)
    {
        // P130,000 + 30%
        annualTax += 130000 + ((annualSalary - 130000) * 0.30);
    }
    else if (annualSalary <= 8000000)
    {
        // P490,000 + 32%
        annualTax += 490000 + ((annualSalary - 490000) * 0.32);
    }
    else if (annualSalary > 8000000)
    {
        // P2,410,000 + 35%
        annualTax += 2410000 + ((annualSalary - 2410000) * 0.35);
    }

    // Convert annual tax to monthly
    tax += annualTax / 12;

    return tax;
}

/* End of Issue Salary Controller*/

/* Start of Job Information Controller */

Schema_JobInformation createJobInformation(Dictionary D, ID employeeID)
{
    Schema_JobInformation jobInfo;

    printf("Create Employee Job Information");

    char dType[15] = "JobInformation";
    jobInfo.employmentID = getNewID(dType, D);
    jobInfo.employeeID = employeeID;

    printf("\n\tJob Position: ");
    scanf("%s", &jobInfo.jobPosition);
    fflush(stdin);

    printf("\n\tJob Location: ");
    scanf("%s", &jobInfo.jobLocation);
    fflush(stdin);

    printf("\n\tJob Phone: ");
    scanf("%s", &jobInfo.jobPhone);
    fflush(stdin);

    printf("\n\tStart Date: ");
    scanf("%s", &jobInfo.startDate);
    fflush(stdin);

    printf("\n\tDepartment: ");
    scanf("%s", &jobInfo.department);
    fflush(stdin);

    printf("\n\tJob Email: ");
    scanf("%s", &jobInfo.jobEmail);
    fflush(stdin);

    printf("\n\tBasic Salary: ");
    scanf("%lf", &jobInfo.basicSalary);
    fflush(stdin);

    printf("\n\tPagibig Deposit: ");
    scanf("%lf", &jobInfo.pagibigDeposit);
    fflush(stdin);

    return jobInfo;
}

bool insertJobInformation(Dictionary *D, Schema_JobInformation data)
{
    PSJI *trav;
    int hashVal = hash(data.employmentID);

    for (trav = &(D->JobInformationD[hashVal]); *trav != NULL; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        trav = (PSJI *)malloc(sizeof(Schema_JobInformation));
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

bool updateJobInformation(Dictionary *D, Schema_JobInformation data, Schema_JobInformation *pointer)
{
    if (data.employmentID != pointer->employmentID)
    {
        return false;
    }
    else
    {
        *pointer = data;
        return true;
    }
}

bool deleteJobInformation(Dictionary *D, ID employmentID)
{
    PSJI *trav, temp;
    int hashVal = hash(employmentID);

    for (trav = &(D->JobInformationD[hashVal]); *trav != NULL && (*trav)->data.employmentID != employmentID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        return false;
    }
    else
    {
        temp = *trav;
        *trav = (*trav)->next;
        free(temp);
        D->count[3]--;
        return true;
    }
}

Schema_JobInformation *searchJobInformation(Dictionary D, ID employmentID)
{
    PSJI trav, temp;
    int hashVal = hash(employmentID);

    for (trav = D.JobInformationD[hashVal]; trav != NULL && trav->data.employmentID != employmentID; trav = trav->next)
    {
    }

    if (trav != NULL)
    {
        // UserSchema_JobInformation *data = (UserSchema_JobInformation *)malloc(sizeof(UserSchema_JobInformation));
        // *data = trav->data;
        return &trav->data;
    }
    else
    {
        return NULL;
    }
}

bool debugJobInformation(Dictionary D)
{
    PSJI trav;
    int i;

    printf("DICTIONARY JOB INFORMATION\n");
    printf("%4s | %4s\n", "row", "ID");
    for (i = 0; i < DICT_SIZE; i++)
    {
        printf("%4d | ", i);
        for (trav = D.JobInformationD[i]; trav != NULL; trav = trav->next)
        {
            printf("%d -> ", trav->data.employmentID);
        }
        printf("\n", i);
    }

    if (trav == NULL && i == DICT_SIZE - 1)
    {
        printf("End of Dictionary\n");
        return true;
    }
    else
    {
        return false;
    }
}

bool displayAllJobInformation(Dictionary D)
{
    PSJI trav;
    int i;

    printf("%-4s | %-14s | %-13s | %-13s | %-10s | %-11s | %-10s | %-13s | %-16s \n",
           "____",
           "______________",
           "_____________",
           "_____________",
           "__________",
           "___________",
           "__________",
           "______________",
           "_________________");
    printf("JOB INFORMATION\n");
    printf("%-4s | %-14s | %-13s | %-13s | %-10s | %-11s | %-10s | %-13s | %-16s \n",
           "____",
           "______________",
           "_____________",
           "_____________",
           "__________",
           "___________",
           "__________",
           "______________",
           "_________________");
    printf("%-4s | %-14s | %-13s | %-13s | %-10s | %-11s | %-10s | %-13s | %-16s \n",
           "#",
           "EMPLOYMENT ID",
           "JOB POSITION",
           "JOB LOCATION",
           "JOB PHONE",
           "DEPARTMENT",
           "JOB EMAIL",
           "BASIC SALARY",
           "PAGIBIG DEPOSIT");

    for (i = 0; i < DICT_SIZE; i++)
    {
        for (trav = D.JobInformationD[i]; trav != NULL; trav = trav->next)
        {
            printf("%-4s | %-9s | %-12s | %-9s | %-8s | %7s \n",
                   i,
                   trav->data.employmentID,
                   trav->data.employeeID,
                   trav->data.jobPosition,
                   trav->data.jobLocation,
                   trav->data.jobPhone,
                   trav->data.department,
                   trav->data.jobEmail,
                   trav->data.basicSalary,
                   trav->data.pagibigDeposit);
        }
    }

    if (trav == NULL && i == DICT_SIZE - 1)
    {
        printf("%-4s | %-14s | %-13s | %-13s | %-10s | %-11s | %-10s | %-13s | %-16s \n",
               "____",
               "______________",
               "_____________",
               "_____________",
               "__________",
               "___________",
               "__________",
               "______________",
               "_________________");
        printf("End of Dictionary\n");
        return true;
    }
    else
    {
        return false;
    }
}

bool displayJobInformation(ID employeeID, Dictionary *D)
{
    Schema_JobInformation *ji = searchJobInformation(*D, employeeID);
    if (ji)
    {
        printf("|  Employee ID:      \t%d   |", ji->employeeID);
        printf("|  Employment ID:    \t%d   |", ji->employmentID);
        printf("|  Job Position:     \t%s   |", ji->jobPosition);
        printf("|  Job Location:     \t%s   |", ji->jobLocation);
        printf("|  Job Phone:        \t%s   |", ji->jobPhone);
        printf("|  Job Email:        \t%s   |", ji->jobEmail);
        printf("|  Start Date:       \t%s   |", ji->startDate);
        printf("|  Department:       \t%s   |", ji->department);
        printf("|  Basic Salary:     \t%lf  |", ji->basicSalary);
        printf("|  Pag-ibig Deposit: \t%lf  |", ji->jobPosition);
        return true;
    }
    else
    {
        return false;
    }
}

/* End of Job Information Controller */

/*---------------------------------- Start of User Controller */

Schema_User createUserInformation(Dictionary D)
{
    Schema_User emp;

    printf("Create Employee Information");

    char dType[10] = "User";
    emp.userID = getNewID(dType, D);
    emp.userType = EMPLOYER;

    printf("\n\tFirst Name: ");
    scanf("%s", &emp.firstName);
    fflush(stdin);

    printf("\n\tLast Name: ");
    scanf("%s", &emp.lastName);
    fflush(stdin);

    printf("\n\tGender (MALE/FEMALE): ");
    scanf("%d", &emp.gender);
    fflush(stdin);

    printf("\n\tDate of Birth (mm/dd/yy): ");
    scanf("%s", &emp.dateOfBirth);
    fflush(stdin);

    printf("\n\tFilipino Citizen: ");
    scanf("%s", &emp.filipinoCitizen);
    fflush(stdin);

    printf("\n\tHome Phone: ");
    scanf("%s", &emp.homePhone);
    fflush(stdin);

    printf("\n\tMobile Phone: ");
    scanf("%s", &emp.mobilePhone);
    fflush(stdin);

    printf("\nEmail Address: ");
    scanf("%s", &emp.emailAddress);
    fflush(stdin);

    printf("\n\tAddress: ");
    scanf("%s", &emp.address);
    fflush(stdin);

    return emp;
}

bool insertUser(Dictionary *D, Schema_User data)
{
    PSU *trav;
    int hashVal = hash(data.userID);

    for (trav = &(D->UserD[hashVal]); strcmp(data.emailAddress, (*trav)->data.emailAddress) != 0 && *trav != NULL; trav = &(*trav)->next)
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
        D->count[4]++;
        return true;
    }
    else
    {
        return false;
    }
}

bool updateUser(Dictionary *D, Schema_User data, Schema_User *pointer)
{
    if (data.userID != pointer->userID)
    {
        return false;
    }
    else
    {
        *pointer = data;
        return true;
    }
}

bool deleteUser(Dictionary *D, ID userID)
{
    PSU *trav, temp;
    int hashVal = hash(userID);

    for (trav = &(D->UserD[hashVal]); *trav != NULL && (*trav)->data.userID != userID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        return false;
    }
    else
    {
        temp = *trav;
        *trav = (*trav)->next;
        free(temp);
        D->count[4]++;
        return true;
    }
}

Schema_User *searchUser(Dictionary D, ID userID)
{
    PSU trav, temp;
    int hashVal = hash(userID);

    for (trav = D.UserD[hashVal]; trav != NULL && trav->data.userID != userID; trav = trav->next)
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
        return NULL;
    }
}

bool debugUser(Dictionary D)
{
    PSU trav;
    int i;

    printf("DICTIONARY USER\n");
    printf("%4s | %4s\n", "row", "ID");
    for (i = 0; i < DICT_SIZE; i++)
    {
        printf("%4d | ", i);
        for (trav = D.UserD[i]; trav != NULL; trav = trav->next)
        {
            printf("%d -> ", trav->data.userID);
        }
        printf("\n", i);
    }

    if (trav == NULL && i == DICT_SIZE - 1)
    {
        printf("End of Dictionary\n");
        return true;
    }
    else
    {
        return false;
    }
}

bool displayAllUser(Dictionary D)
{
    PSU trav;
    int i;

    printf("%-4s | %-8s | %-11s | %-10s | %-7s | %-14s | %-17s | %-10s | %-13s | %-14s | %-8s | %-10s \n",
           "____",
           "________",
           "___________",
           "__________",
           "_______",
           "______________",
           "_________________",
           "__________",
           "_____________",
           "______________",
           "________",
           "__________");
    printf("USER\n");
    printf("%-4s | %-8s | %-11s | %-10s | %-7s | %-14s | %-17s | %-10s | %-13s | %-14s | %-8s | %-10s \n",
           "____",
           "________",
           "___________",
           "__________",
           "_______",
           "______________",
           "_________________",
           "__________",
           "_____________",
           "______________",
           "________",
           "__________");
    printf("%-4s | %-8s | %-11s | %-10s | %-7s | %-14s | %-17s | %-10s | %-13s | %-14s | %-8s | %-10s \n",
           "#",
           "USER ID",
           "FIRST NAME",
           "LAST NAME",
           "GENDER",
           "DATE OF BIRTH",
           "FILIPINO CITIZEN",
           "HOME PAGE",
           "MOBILE PHONE",
           "EMAIL ADDRESS",
           "ADDRESS",
           "USER TYPE");

    for (i = 0; i < DICT_SIZE; i++)
    {
        for (trav = D.UserD[i]; trav != NULL; trav = trav->next)
        {
            printf("%-4s | %-9s | %-12s | %-9s | %-8s | %7s \n",
                   i,
                   trav->data.userID,
                   trav->data.firstName,
                   trav->data.lastName,
                   trav->data.gender,
                   trav->data.dateOfBirth,
                   trav->data.filipinoCitizen,
                   trav->data.homePhone,
                   trav->data.mobilePhone,
                   trav->data.emailAddress,
                   trav->data.address,
                   trav->data.userType);
        }
    }

    if (trav == NULL && i == DICT_SIZE - 1)
    {
        printf("%-4s | %-8s | %-11s | %-10s | %-7s | %-14s | %-17s | %-10s | %-13s | %-14s | %-8s | %-10s \n",
               "____",
               "________",
               "___________",
               "__________",
               "_______",
               "______________",
               "_________________",
               "__________",
               "_____________",
               "______________",
               "________",
               "__________");
        printf("End of Dictionary\n");
        return true;
    }
    else
    {
        return false;
    }
}

bool displayUserInformation(ID userID, Dictionary *D)
{
    Schema_User *emp = searchUser(*D, userID);
    if (emp)
    {
        printf("|  Employee ID:      \t%d  |", emp->userID);
        printf("|  First Name:       \t%d  |", emp->firstName);
        printf("|  Last Name:        \t%s  |", emp->lastName);
        printf("|  Gender:           \t%s  |", emp->gender);
        printf("|  Date of Birth     \t%s  |", emp->dateOfBirth);
        printf("|  Filipino:         \t%s  |", emp->filipinoCitizen);
        printf("|  Home Phone:       \t%s  |", emp->homePhone);
        printf("|  Mobile Phone:     \t%d  |", emp->mobilePhone);
        printf("|  Email:            \t%d  |", emp->emailAddress);
        printf("|  Address           \t%s  |", emp->address);
        return true;
    }
    else
    {
        return false;
    }
}

/* End of User Controller */

/*---------------------------------- End of Functions ----------------------------------*/

#endif