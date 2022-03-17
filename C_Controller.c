#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "H_Schema.h"
#include "H_Dictionary.h"

/*---------------------------------- Dictionary Function Headers ----------------------------------*/

void initDictionary(Dictionary *D);
ElemPos hash(ID id);
int getNewID(char DictionaryType[], Dictionary D);
bool pullDictionaries(Dictionary *D);
bool pushDictionaries(Dictionary D);
void displayDictionariesCount(Dictionary D);

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

/*----------------------------------- Bonus Function Headers --------------------------------------*/

Schema_Bonus createBonus(Dictionary D);
bool insertBonus(Dictionary *D, Schema_Bonus data);
bool updateBonus(Dictionary *D, Schema_Bonus data, Schema_Bonus *pointer);
bool deleteBonus(Dictionary *D, ID bonusID);
Schema_Bonus *searchBonus(Dictionary D, ID bonusID, char period[]);
void debugBonus(Dictionary D);
bool displayAllBonus(Dictionary D);
bool displayBonus(int bonusID, Dictionary *D, char period[]);

/*-------------------------------- Issue Salary Function Headers ----------------------------------*/

Schema_IssueSalary createIssueSalary(Dictionary D, int employeeID, double balance, char period[]);
bool insertIssueSalary(Dictionary *D, Schema_IssueSalary data);
bool updateIssueSalary(Dictionary *D, Schema_IssueSalary data, Schema_IssueSalary *pointer);
bool deleteIssueSalary(Dictionary *D, ID issueID);
Schema_IssueSalary *searchIssueSalary(Dictionary D, ID userID, char period[]);
void debugSalary(Dictionary D);
bool displayAllSalary(Dictionary D);
bool displayIssueSalary(ID issueID, Dictionary *D, char period[]);
bool issueSalary(int empID, Dictionary *D);
double calculateTax(double taxableIncome, double *pagibigDeposit);

/*-------------------------------- Job Information Function Headers -------------------------------*/

Schema_JobInformation createJobInformation(Dictionary D, ID employeeID);
bool insertJobInformation(Dictionary *D, Schema_JobInformation data);
bool updateJobInformation(Dictionary *D, Schema_JobInformation data, Schema_JobInformation *pointer);
bool deleteJobInformation(Dictionary *D, ID employmentID);
Schema_JobInformation *searchJobInformation(Dictionary D, ID employmentID);
void debugJobInformation(Dictionary D);
bool displayAllJobInformation(Dictionary D);
bool displayJobInformation(ID employeeID, Dictionary *D);

/*------------------------------------- User Function Headers -------------------------------------*/

Schema_User createUserInformation(Dictionary D);
bool insertUser(Dictionary *D, Schema_User data);
bool updateUser(Dictionary *D, Schema_User data, Schema_User *pointer);
bool deleteUser(Dictionary *D, ID userID);
Schema_User *searchUser(Dictionary D, ID userID);
void debugUser(Dictionary D);
bool displayAllUser(Dictionary D);
bool displayUserInformation(ID userID, Dictionary *D);

/*--------------------------------- Default --------------------------------*/

void insertDefault(Dictionary *D);

/*--------------------------------- Start of Dictionary Controller --------------------------------*/

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

    D->count[0] = 0;
    D->count[1] = 0;
    D->count[2] = 0;
    D->count[3] = 0;
    D->count[4] = 0;
}

ElemPos hash(ID id)
{
    return id % 10;
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

bool pushUserD(Dictionary D)
{
    PSU UTrav;
    int i, count;
    FILE *fp;

    // User Information
    fp = fopen("Emp_Info.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (UTrav = D.UserD[i]; UTrav != NULL; UTrav = UTrav->next)
            {
                fwrite(&UTrav->data, sizeof(Schema_User), 1, fp);
            }
        }

        // fseek(fp, 0L, SEEK_END);
        // if (ftell(fp) == -1)
        // {
        //     count = 0;
        // }
        // else
        // {
        //     count = ftell(fp) / sizeof(Schema_User);
        // }

        // if (count != D.count[4])
        // {
        //     return false;
        // }

        fclose(fp);
    }
    else
    {
        printf("\nFailed to create");
        return false;
    }

    return true;
}

bool pushJobInformationD(Dictionary D)
{
    PSJI JITrav;
    int i, count;
    FILE *fp;

    // Job Information
    fp = fopen("Emp_JobInformation.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (JITrav = D.JobInformationD[i]; JITrav != NULL; JITrav = JITrav->next)
            {
                fwrite(&JITrav->data, sizeof(Schema_JobInformation), 1, fp);
            }
        }

        // fseek(fp, 0L, SEEK_END);
        // if (ftell(fp) == -1)
        // {
        //     count = 0;
        // }
        // else
        // {
        //     count = ftell(fp) / sizeof(Schema_JobInformation);
        // }

        // if (count != D.count[3])
        // {
        //     return false;
        // }

        fclose(fp);
    }
    else
    {
        return false;
    }

    return true;
}

bool pushIssueSalaryD(Dictionary D)
{
    PSIS STrav;
    int i, count;
    FILE *fp;

    // Issue Salary
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

        // fseek(fp, 0L, SEEK_END);
        // if (ftell(fp) == -1)
        // {
        //     count = 0;
        // }
        // else
        // {
        //     count = ftell(fp) / sizeof(Schema_IssueSalary);
        // }

        // if (count != D.count[2])
        // {
        //     return false;
        // }

        fclose(fp);
    }
    else
    {
        return false;
    }

    return true;
}

bool pushBonusD(Dictionary D)
{
    PSB BTrav;
    int i, count;
    FILE *fp;

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

        // fseek(fp, 0L, SEEK_END);
        // if (ftell(fp) == -1)
        // {
        //     count = 0;
        // }
        // else
        // {
        //     count = ftell(fp) / sizeof(Schema_Bonus);
        // }

        // if (count != D.count[1])
        // {

        //     return false;
        // }

        fclose(fp);
    }
    else
    {
        return false;
    }

    return true;
}

bool pushAttendanceD(Dictionary D)
{
    PSA ATrav;
    int i, count;
    FILE *fp;

    // Attendance Information
    fp = fopen("Emp_Attendance.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (ATrav = D.AttendanceD[i]; ATrav != NULL; ATrav = ATrav->next)
            {
                fwrite(&ATrav->data, sizeof(Schema_Attendance), 1, fp);
            }
        }

        // fseek(fp, 0L, SEEK_END);
        // if (ftell(fp) == -1)
        // {
        //     count = 0;
        // }
        // else
        // {
        //     count = ftell(fp) / sizeof(Schema_Attendance);
        // }

        // if (count != D.count[0])
        // {
        //     return false;
        // }

        fclose(fp);
    }
    else
    {
        return false;
    }

    return true;
}

void displayDictionariesCount(Dictionary D)
{
    printf("\nAttendance: %d\n", D.count[0]);
    printf("Bonus: %d\n", D.count[1]);
    printf("Issue Salary: %d\n", D.count[2]);
    printf("Job Information: %d\n", D.count[3]);
    printf("User: %d\n", D.count[4]);
}

void insertDefault(Dictionary *D)
{
    Schema_User defaultUser = {
        1,
        "adminfn",
        "adminln",
        MALE,
        "1/1/1",
        YES,
        "1234",
        "1234",
        "admin@gmail.com",
        "adminaddress",
        EMPLOYEE};

    Schema_JobInformation defaultJobInformation = {
        1,
        1,
        "admin",
        "adminlocation",
        "1234",
        "1/1/2001",
        "admindepartment",
        "admin@gmail.com",
        1000,
        0};

    Schema_Attendance defaultAttendance = {
        1,
        1,
        0,
        0,
        0,
        0,
        "03/22"};

    Schema_Bonus defaultBonus = {
        1,
        1,
        "adminbonus",
        100,
        "03/02"};

    Schema_IssueSalary defaultIssueSalary = {
        1,
        1,
        100,
        "03/22"};

    insertUser(D, defaultUser);
    insertJobInformation(D, defaultJobInformation);
    insertAttendance(D, defaultAttendance);
    insertBonus(D, defaultBonus);
    insertIssueSalary(D, defaultIssueSalary);
}

/*--------------------------------- End of Dictionary Controller ----------------------------------*/

/*-------------------------------- Start of Attendance Controller ---------------------------------*/

Schema_Attendance *searchAttendance(Dictionary D, ID employeeID)
{
    PSA trav, temp;
    int hashVal = hash(employeeID);

    for (trav = D.AttendanceD[hashVal]; trav != NULL && trav->data.employeeID != employeeID; trav = trav->next)
    {
    }

    if (trav != NULL)
    {
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
    char period[20];

    printf("Create Employee Attendance\n");

    printf("Enter Employee ID: ");
    scanf("%d", &empID);

    printf("Enter period (mm/yy): ");
    scanf("%s", &period);

    if (searchUser(D, empID))
    {
        char dType[20] = "Attendance";
        sa.attendanceID = getNewID(dType, D);
        sa.employeeID = empID;
        strcpy(sa.period, period);
        sa.present = 0;
        sa.absent = 0;
        sa.leave = 0;
        sa.overtime = 0;
    }
    else
    {
        sa.attendanceID = -1;
    }

    return sa;
}

bool insertAttendance(Dictionary *D, Schema_Attendance data)
{
    PSA *trav;
    int hashVal = hash(data.employeeID);

    for (trav = &D->AttendanceD[hashVal]; *trav != NULL && strcmp((*trav)->data.period, data.period) != 0; trav = &(*trav)->next) 
    {
    }

    if (*trav == NULL)
    {
        *trav = (PSA)malloc(sizeof(Schema_Attendance));
        if (*trav != NULL)
        {
            (*trav)->data = data;
            (*trav)->next = NULL;
            D->count[0]++;
        }
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
        D->count[0]--;
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
}

/*--------------------------------- End of Attendance Controller ----------------------------------*/

/*---------------------------------- Start of Bonus Controller ------------------------------------*/

Schema_Bonus createBonus(Dictionary D)
{
    Schema_Bonus bonus;

    printf("Create Employee Bonus\n");

    char dType[10] = "Bonus";
    bonus.bonusID = getNewID(dType, D);

    printf("\tEmployee ID: ");
    scanf("%s", &bonus.employeeID);
    fflush(stdin);

    printf("\tBonus Name: ");
    scanf("%s", &bonus.bonusName);
    fflush(stdin);

    printf("\tAmount: ");
    scanf("%f", &bonus.amount);
    fflush(stdin);

    printf("\tPeriod (mm/yy): ");
    scanf("%s", &bonus.period);
    fflush(stdin);

    return bonus;
}

bool insertBonus(Dictionary *D, Schema_Bonus data)
{
    PSB *trav;
    int hashVal = hash(data.bonusID);

    for (trav = &(D->BonusD[hashVal]); *trav != NULL; trav = &(*trav)->next) // strcmp(data.bonusName, (*trav)->data.bonusName) != 0
    {
    }

    if (*trav == NULL)
    {
        *trav = (PSB)malloc(sizeof(Schema_Bonus));
        if (*trav != NULL)
        {
            (*trav)->data = data;
            (*trav)->next = NULL;

            D->count[1]++;
        }
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
        D->count[1]--;
        return true;
    }
}

Schema_Bonus *searchBonus(Dictionary D, ID employeeID, char period[])
{
    PSB trav, temp;
    int hashVal = hash(employeeID);

    for (trav = D.BonusD[hashVal]; trav != NULL && trav->data.employeeID != employeeID && strcmp(trav->data.period, period) != 0; trav = trav->next)
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

void debugBonus(Dictionary D)
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

bool displayBonus(int employeeID, Dictionary *D, char period[])
{
    Schema_Bonus *emp = searchBonus(*D, employeeID, period);
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

/*----------------------------------- End of Bonus Controller -------------------------------------*/

/*------------------------------- Start of Issue Salary Controller --------------------------------*/

Schema_IssueSalary createIssueSalary(Dictionary D, int employeeID, double balance, char period[])
{
    Schema_IssueSalary is;

    char dType[15] = "IssueSalary";
    is.issueID = getNewID(dType, D);
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

    if (*trav == NULL)
    {
        *trav = (PSIS)malloc(sizeof(Schema_IssueSalary));
        if (*trav != NULL)
        {

            (*trav)->data = data;
            (*trav)->next = NULL;
            D->count[2]++;
        }
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
        D->count[2]--;
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

bool displayIssueSalary(ID issueID, Dictionary *D, char period[])
{
    Schema_IssueSalary *emp = searchIssueSalary(*D, issueID, period);
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

        printf("Basic Income: P%.2f\n", basicSalary);
        printf("Taxable Income: P%.2f\n", income);
        printf("Additions: P%.2f\n", additions);
        printf("Dedutions: P%.2f\n", deductions);

        tax = calculateTax(income, &pagibigDeposit);
        income -= tax;

        printf("Tax: P%.2f\n", tax);
        printf("Issue Salary: P%.2f\n\n", income);
        printf("Add Issue Salary to the employee's record for period %s?\n\n", period);
        printf("[1] Yes\n");
        printf("[2] No\n");
        scanf("%d", &temp);

        if (temp == 1)
        {
            // Create new issue salary
            *is = createIssueSalary(*D, empID, income, period);
            insertIssueSalary(D, *is);
            // Update pagibig deposit
            Schema_JobInformation *ji = searchJobInformation(*D, empID);
            ji->pagibigDeposit = pagibigDeposit;
            return true;
        }
        else if (temp == 2)
        {

            return false;
        }
        else
        {

            printf("Input not recognized!");
            return false;
        }
    }
    else
    {

        printf("\nIssue Salary for period %s already exists!", period);
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

/*-------------------------------- End of Issue Salary Controller ---------------------------------*/

/*------------------------------ Start of Job Information Controller ------------------------------*/

Schema_JobInformation createJobInformation(Dictionary D, ID employeeID)
{
    Schema_JobInformation jobInfo;

    printf("Create Employee Job Information\n");

    char dType[15] = "JobInformation";
    jobInfo.employmentID = getNewID(dType, D);
    jobInfo.employeeID = employeeID;

    printf("\tJob Position: ");
    scanf("%s", &jobInfo.jobPosition);
    fflush(stdin);

    printf("\tJob Location: ");
    scanf("%s", &jobInfo.jobLocation);
    fflush(stdin);

    printf("\tJob Phone (11 digits): ");
    scanf("%s", &jobInfo.jobPhone);
    fflush(stdin);

    printf("\tStart Date (mm/dd/yy): ");
    scanf("%s", &jobInfo.startDate);
    fflush(stdin);

    printf("\tDepartment: ");
    scanf("%s", &jobInfo.department);
    fflush(stdin);

    printf("\tJob Email: ");
    scanf("%s", &jobInfo.jobEmail);
    fflush(stdin);

    printf("\tBasic Salary: ");
    scanf("%lf", &jobInfo.basicSalary);
    fflush(stdin);

    printf("\tPagibig Deposit: ");
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

    if (*trav == NULL)
    {
        *trav = (PSJI)malloc(sizeof(Schema_JobInformation));
        if (*trav != NULL)
        {
            (*trav)->data = data;
            (*trav)->next = NULL;
            D->count[3]++;
        }
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

void debugJobInformation(Dictionary D)
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

/*------------------------------- End of Job Information Controller -------------------------------*/

/*---------------------------------- Start of User Controller -------------------------------------*/

Schema_User createUserInformation(Dictionary D)
{
    Schema_User emp;

    printf("Create Employee Information\n");

    char dType[10] = "User";
    emp.userID = getNewID(dType, D);
    emp.userType = EMPLOYER;

    printf("\tFirst Name: ");
    scanf("%s", &emp.firstName);
    fflush(stdin);

    printf("\tLast Name: ");
    scanf("%s", &emp.lastName);
    fflush(stdin);

    printf("\tGender (MALE/FEMALE): ");
    scanf("%d", &emp.gender);
    fflush(stdin);

    printf("\tDate of Birth (mm/dd/yy): ");
    scanf("%s", &emp.dateOfBirth);
    fflush(stdin);

    printf("\tFilipino Citizen (YES/NO): ");
    scanf("%s", &emp.filipinoCitizen);
    fflush(stdin);

    printf("\tHome Phone (7 digits): ");
    scanf("%s", &emp.homePhone);
    fflush(stdin);

    printf("\tMobile Phone (11 digits): ");
    scanf("%s", &emp.mobilePhone);
    fflush(stdin);

    printf("\tEmail Address: ");
    scanf("%s", &emp.emailAddress);
    fflush(stdin);

    printf("\tAddress: ");
    scanf("%s", &emp.address);
    fflush(stdin);

    return emp;
}

bool insertUser(Dictionary *D, Schema_User data)
{
    PSU *trav;
    int hashVal = hash(data.userID);

    for (trav = &D->UserD[hashVal]; *trav != NULL && strcmp(data.emailAddress, (*trav)->data.emailAddress) != 0; trav = &(*trav)->next) //
    {
    }

    if (*trav == NULL)
    {
        *trav = (PSU)malloc(sizeof(Schema_User));
        if (*trav != NULL)
        {
            (*trav)->data = data;
            (*trav)->next = NULL;

            D->count[4]++;
        }
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
        D->count[4]--;
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

void debugUser(Dictionary D)
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
            if (trav == NULL)
            {
                printf("NULL");
            }
            else
            {
                printf("%d -> ", trav->data.userID);
            }
        }
        printf("\n", i);
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

        if (emp->gender == MALE)
        {
            printf("|  Gender:           \t%s  |", "MALE");
        }
        else
        {
            printf("|  Gender:           \t%s  |", "FEMALE");
        }

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

/*----------------------------------- End of User Controller --------------------------------------*/

/*------------------------------------- End of Functions ------------------------------------------*/
