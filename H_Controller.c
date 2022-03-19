#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#include "H_Dictionary.h"
#include "H_Model.h"

/*-------------------------------------------------------------------------------------------------*/
/*------------------------------------- Function Prototypes ---------------------------------------*/
/*-------------------------------------------------------------------------------------------------*/

/*---------------------------------------- AUTHORIZATION ------------------------------------------*/

bool login(void);

/*---------------------------------- Dictionary Function Headers ----------------------------------*/

void initDictionary(dPtr *D);
ElemPos hash(ID id);
int getNewID(char DictionaryType[], Dictionary D);
bool pullDictionaries(Dictionary *D);
bool pushDictionaries(Dictionary D);

/*---------------------------------- Attendance Function Headers ----------------------------------*/

Model_Attendance *searchAttendance(Dictionary D, ID employeeID, char period[]);
Model_Attendance createAttendance(Dictionary D);
bool insertAttendance(Dictionary *D, Model_Attendance data);
bool deleteAttendance(Dictionary *D, int ID, char period[]);
bool setPresent(int employeeID, Dictionary *D, char period[]);
bool setLeave(int employeeID, Dictionary *D, char period[]);
bool setAbsent(int employeeID, Dictionary *D, char period[]);
bool setOvertime(int employeeID, Dictionary *D, char period[]);
void displayAttendance(Dictionary *D, int employeeID, char period[]);
void displayAllAttendance(Dictionary D, char period[]);

/*----------------------------------- Bonus Function Headers --------------------------------------*/

Model_Bonus *searchBonus(Dictionary D, ID bonusID, char period[]);
Model_Bonus createBonus(Dictionary D);
bool insertBonus(Dictionary *D, Model_Bonus data);
bool deleteBonus(Dictionary *D, ID bonusID);
void displayBonus(int bonusID, Dictionary *D, char period[]);
void displayAllBonus(Dictionary D);

/*-------------------------------- Issue Salary Function Headers ----------------------------------*/

Model_IssueSalary *searchIssueSalary(Dictionary D, ID userID, char period[]);
Model_IssueSalary createIssueSalary(Dictionary D, int employeeID, double balance, char period[]);
bool insertIssueSalary(Dictionary *D, Model_IssueSalary data);
bool deleteIssueSalary(Dictionary *D, ID issueID);
bool issueSalary(Dictionary *D, int empID, char period[]);
double calculateTax(double basicIncome, double taxableIncome, double *pagibigDeposit);
void displayIssueSalary(Dictionary *D, ID empID, char period[]);
void displayAllSalary(Dictionary D, char period[]);

/*-------------------------------- Job Information Function Headers -------------------------------*/

Model_JobInformation *searchJobInformation(Dictionary D, ID employmentID);
Model_JobInformation createJobInformation(Dictionary D, ID employeeID);
bool insertJobInformation(Dictionary *D, Model_JobInformation data);
bool deleteJobInformation(Dictionary *D, ID employmentID);
void displayJobInformation(ID employeeID, Dictionary *D);
void displayAllJobInformation(Dictionary D);

/*------------------------------------- User Function Headers -------------------------------------*/

Model_User *searchUser(Dictionary D, ID userID);
Model_User createUserInformation(Dictionary D);
bool insertUser(Dictionary *D, Model_User data);
bool deleteUser(Dictionary *D, ID userID);
void displayUserInformation(ID userID, Dictionary *D);
void displayAllUser(Dictionary D);

/*------------------------------------------- Default ---------------------------------------------*/

void insertDefault(Dictionary *D);

/*-------------------------------------------- Debug ----------------------------------------------*/

void debugAttendance(Dictionary D);
void debugBonus(Dictionary D);
void debugSalary(Dictionary D);
void debugJobInformation(Dictionary D);
void debugUser(Dictionary D);
void debugAll(Dictionary D);

/*---------------------------------------------- UI -----------------------------------------------*/

void header(void);
void invalidInput(void);

/*-------------------------------------------- DEBUG ----------------------------------------------*/

void displayDictionariesCount(Dictionary D);

/*-------------------------------------------------------------------------------------------------*/
/*------------------------------------ Function Definitions  --------------------------------------*/
/*-------------------------------------------------------------------------------------------------*/

/*-------------------------------- Start of Debug All Controller ----------------------------------*/

void debugAll(Dictionary D)
{
    debugAttendance(D);
    debugBonus(D);
    debugSalary(D);
    debugJobInformation(D);
    debugUser(D);
}

/*--------------------------------- End of Debug All Controller ------------------------------------*/

/*------------------------------ Start of Authorization Controller ---------------------------------*/

bool login(void)
{
    char USERNAME[MD_MAX] = "admin", PASSWORD[MD_MAX] = "admin", user[MD_MAX], pass[MD_MAX];

    printf(" WELCOME TO EDWIN'S BEST PAYROLL SYSTEM\n\n");
    printf(" Login\n\n");
    printf(" Username: ");
    scanf("%s", &user);
    fflush(stdin);
    printf(" Password: ");
    scanf("%s", &pass);
    fflush(stdin);

    if (strcmp(USERNAME, user) == 0 && strcmp(PASSWORD, pass) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*------------------------------ End of Authorization Controller -----------------------------------*/

/*--------------------------------- Start of Dictionary Controller --------------------------------*/

void initDictionary(dPtr *D)
{
    *D = (dPtr)calloc(1, sizeof(Dictionary));
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
        printf(" Invalid Dictionary Type\n");
        return -1;
    }

    return lastID + 1;
}

bool pullDictionaries(Dictionary *D)
{
    // Attendance Information
    FILE *fp = fopen("Emp_Attendance.bin", "rb");
    Model_Attendance attendance;

    if (fp)
    {
        while (fread(&attendance, sizeof(Model_Attendance), 1, fp))
        {
            printf(" Attendance inserting to dictionary...\n");
            insertAttendance(D, attendance);
        }

        fclose(fp);
    }
    else
    {
        return false;
    }

    // Bonus Information
    fp = fopen("Emp_Bonus.bin", "rb");
    Model_Bonus bonus;

    if (fp)
    {
        while (fread(&bonus, sizeof(Model_Bonus), 1, fp))
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
    fp = fopen("Emp_IssueSalary.bin", "rb");
    Model_IssueSalary salary;

    if (fp)
    {
        while (fread(&salary, sizeof(Model_IssueSalary), 1, fp))
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
    fp = fopen("Emp_JobInformation.bin", "rb");
    Model_JobInformation jobinfo;

    if (fp)
    {
        while (fread(&jobinfo, sizeof(Model_JobInformation), 1, fp))
        {
            insertJobInformation(D, jobinfo);
        }
        fclose(fp);
    }
    else
    {
        return false;
    }

    // Emp Information
    fp = fopen("Emp_Information.bin", "rb");
    Model_User employee;

    if (fp)
    {
        while (fread(&employee, sizeof(Model_User), 1, fp))
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
    fp = fopen("Emp_Information.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (UTrav = D.UserD[i]; UTrav != NULL; UTrav = UTrav->next)
            {
                fwrite(&UTrav->data, sizeof(Model_User), 1, fp);
            }
        }

        // fseek(fp, 0L, SEEK_END);
        // if (ftell(fp) == -1)
        // {
        //     count = 0;
        // }
        // else
        // {
        //     count = ftell(fp) / sizeof(Model_User);
        // }

        // if (count != D.count[4])
        // {
        //     return false;
        // }

        fclose(fp);
    }
    else
    {
        printf(" \n ERROR: Failed to create");
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
                fwrite(&JITrav->data, sizeof(Model_JobInformation), 1, fp);
            }
        }

        // fseek(fp, 0L, SEEK_END);
        // if (ftell(fp) == -1)
        // {
        //     count = 0;
        // }
        // else
        // {
        //     count = ftell(fp) / sizeof(Model_JobInformation);
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
    fp = fopen("Emp_IssueSalary.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (STrav = D.IssueSalaryD[i]; STrav != NULL; STrav = STrav->next)
            {
                fwrite(&STrav->data, sizeof(Model_IssueSalary), 1, fp);
            }
        }

        // fseek(fp, 0L, SEEK_END);
        // if (ftell(fp) == -1)
        // {
        //     count = 0;
        // }
        // else
        // {
        //     count = ftell(fp) / sizeof(Model_IssueSalary);
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
    fp = fopen("Emp_Bonus.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (BTrav = D.BonusD[i]; BTrav != NULL; BTrav = BTrav->next)
            {
                fwrite(&BTrav->data, sizeof(Model_Bonus), 1, fp);
            }
        }

        // fseek(fp, 0L, SEEK_END);
        // if (ftell(fp) == -1)
        // {
        //     count = 0;
        // }
        // else
        // {
        //     count = ftell(fp) / sizeof(Model_Bonus);
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
                fwrite(&ATrav->data, sizeof(Model_Attendance), 1, fp);
            }
        }

        // fseek(fp, 0L, SEEK_END);
        // if (ftell(fp) == -1)
        // {
        //     count = 0;
        // }
        // else
        // {
        //     count = ftell(fp) / sizeof(Model_Attendance);
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

void insertDefault(Dictionary *D)
{
    Model_User defaultUser = {
        1,
        "employeefn",
        "employeeln",
        FEMALE,
        "1/1/1",
        NO,
        "1234",
        "1234",
        "employee@gmail.com",
        "employeeaddress",
        EMPLOYER
    };

    Model_Bonus defaultBonus = {
        1,
        1,
        "employeebonus",
        100,
        "03/02"
    };

    Model_Attendance defaultAttendance = {
        1,
        1,
        0,
        0,
        0,
        0,
        "03/22",
    };

    Model_IssueSalary defaultIssueSalary = {
        1,
        1,
        100,
        "03/22"
    };

    Model_JobInformation defaultJobInformation = {
        1,
        1,
        "employee",
        "employeelocation",
        "1234",
        "1/1/2001",
        "employeedepartment",
        "employee@gmail.com",
        1000,
        0
    };

    insertUser(D, defaultUser);
    insertAttendance(D, defaultAttendance);
    insertBonus(D, defaultBonus);
    insertJobInformation(D, defaultJobInformation);
    insertIssueSalary(D, defaultIssueSalary);
}

/*--------------------------------- End of Dictionary Controller ----------------------------------*/

/*-------------------------------- Start of Attendance Controller ---------------------------------*/

Model_Attendance *searchAttendance(Dictionary D, ID employeeID, char period[])
{
    PSA trav, temp;
    int hashVal = hash(employeeID);

    for (trav = D.AttendanceD[hashVal]; trav != NULL && (trav->data.employeeID != employeeID || strcmp(trav->data.period, period) != 0); trav = trav->next)
    {
        if (trav->data.employeeID == employeeID && strcmp(trav->data.period, period) == 0)
            break;
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

Model_Attendance createAttendance(Dictionary D)
{
    Model_Attendance sa;
    int empID;
    char period[20];

    printf(" Enter Employee ID: ");
    scanf("%d", &empID);

    printf(" Enter period (mm/yy): ");
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

bool insertAttendance(Dictionary *D, Model_Attendance data)
{
    PSA *trav;
    int hashVal = hash(data.employeeID);

    for (trav = &(D->AttendanceD[hashVal]); *trav != NULL && strcmp((*trav)->data.period, data.period) != 0; trav = &(*trav)->next)
    {
    }

    if (*trav == NULL)
    {
        *trav = (PSA)malloc(sizeof(Model_Attendance) + 1);
        if (trav != NULL)
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

bool deleteAttendance(Dictionary *D, int ID, char period[])
{
    PSA *trav, temp;
    int hashVal = hash(ID);

    for (trav = &(D->AttendanceD[hashVal]); *trav != NULL && ((*trav)->data.attendanceID != ID || strcmp((*trav)->data.period, period) != 0); trav = &(*trav)->next)
    {
    }

    if (*trav == NULL)
    {
        return false;
    }
    else
    {
        temp = *trav;
        *trav = (*trav)->next;
        free(temp);
        D->count[0]--;
        return true;
    }
}

void displayAttendance(Dictionary *D, ID employeeID, char period[])
{
    Model_Attendance *emp = searchAttendance(*D, employeeID, period);
    if (emp)
    {
        printf(" _____________________________________________________\n\n");

        printf(" EMPLOYEE #%d - %s         \t\t\n\n", employeeID, period);
        printf(" Attendance ID:       \t\t%d  \n", emp->attendanceID);
        printf(" Employee ID:           \t%d  \n", emp->employeeID);
        printf(" Present:               \t%d  \n", emp->present);
        printf(" Absent                 \t%d  \n", emp->absent);
        printf(" Leave:                 \t%d  \n", emp->leave);
        printf(" Overtime:              \t%d  \n", emp->overtime);
        printf(" Period:                \t%s  \n", emp->period);
        printf(" _____________________________________________________\n\n");
    }
    
}

bool setPresent(int employeeID, Dictionary *D, char period[])
{
    int presentNum;
    Model_Attendance *sa = searchAttendance(*D, employeeID, period);
    if (sa)
    {
        printf(" Enter No. of Present Days: ");
        scanf("%d", &presentNum);
        sa->present += presentNum;
        return true;
    }
    else
    {
        printf(" ERROR: Employee attendance for period %s does not exist.", period);
        return false;
    }
}

bool setLeave(int employeeID, Dictionary *D, char period[])
{
    int leaveNum;
    Model_Attendance *sa = searchAttendance(*D, employeeID, period);
    if (sa)
    {
        printf(" Enter No. of Leave Days: ");
        scanf("%d", &leaveNum);
        sa->leave += leaveNum;
        return true;
    }
    else
    {
        printf(" ERROR: Employee attendance for period %s does not exist.", period);
        return false;
    }
}

bool setAbsent(int employeeID, Dictionary *D, char period[])
{
    int absentNum;
    Model_Attendance *sa = searchAttendance(*D, employeeID, period);
    if (sa)
    {
        printf(" Enter No. of Absent Days: ");
        scanf("%d", &absentNum);
        sa->absent += absentNum;

        return true;
    }
    else
    {
        printf(" ERROR: Employee attendance for period %s does not exist.", period);
        return false;
    }
}

bool setOvertime(int employeeID, Dictionary *D, char period[])
{
    int otHours;
    Model_Attendance *sa = searchAttendance(*D, employeeID, period);
    if (sa)
    {
        printf(" Enter No. of Overtime Hours: ");
        scanf("%d", &otHours);
        sa->overtime += otHours;

        return true;
    }
    else
    {
        printf(" ERROR: Employee attendance for period %s does not exist.", period);
        return false;
    }
}

void displayAllAttendance(Dictionary D, char period[])
{
    PSA trav;
    int i;

    printf(" %4s___%14s___%12s___%8s___%7s___%8s___%9s___%7s\n",
           "____",
           "______________",
           "____________",
           "________",
           "_______",
           "________",
           "_________",
           "_______");
    printf(" \t\t\t\t\tATTENDANCE\n\n");
    printf(" %-4s | %-14s | %-12s | %-8s | %-7s | %-8s | %-9s | %-7s\n",
           "#",
           "ATTENDANCE ID",
           "EMPLOYEE ID",
           "PRESENT",
           "ABSENT",
           "LEAVE",
           "OVERTIME",
           "PERIOD");
    printf(" %-4s | %-14s | %-12s | %-8s | %-7s | %-8s | %-9s | %-7s\n",
           "",
           "",
           "",
           "",
           "",
           "",
           "",
           "");

    for (i = 0; i < DICT_SIZE; i++)
    {
        for (trav = D.AttendanceD[i]; trav != NULL; trav = trav->next)
        {
            if (strcmp(trav->data.period, period) == 0)
            {
                printf(" %4d | %14d | %12d | %8d | %7d | %8d | %9d | %-7s\n",
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
    }

    printf(" %4s_|_%14s_|_%12s_|_%8s_|_%7s_|_%8s_|_%9s_|_%7s\n",
           "____",
           "______________",
           "____________",
           "________",
           "_______",
           "________",
           "_________",
           "_______");
    printf("\n End of Dictionary\n\n");
}

void debugAttendance(Dictionary D)
{
    PSA trav;
    int i;
    printf("\n *****************************************************\n");
    printf(" (DEBUG) DICTIONARY ATTENDANCE\n");
    printf(" *****************************************************\n");
    printf(" %4s | %4s\n", "row", "ID");
    for (i = 0; i < DICT_SIZE; i++)
    {
        printf(" %4d | ", i);
        for (trav = D.AttendanceD[i]; trav != NULL; trav = trav->next)
        {
            printf(" ID#%d -> ", trav->data.attendanceID);
        }
        printf("\n", i);
    }
}

/*--------------------------------- End of Attendance Controller ----------------------------------*/

/*---------------------------------- Start of Bonus Controller ------------------------------------*/

Model_Bonus createBonus(Dictionary D)
{
    Model_Bonus bonus;

    char dType[10] = "Bonus";
    bonus.bonusID = getNewID(dType, D);

    printf(" Employee ID: ");
    scanf("%d", &bonus.employeeID);
    fflush(stdin);

    printf(" Bonus Name: ");
    scanf("%s", &bonus.bonusName);
    fflush(stdin);

    printf(" Amount: ");
    scanf("%lf", &bonus.amount);
    fflush(stdin);

    printf(" Period (mm/yy): ");
    scanf("%s", &bonus.period);
    fflush(stdin);

    return bonus;
}

bool insertBonus(Dictionary *D, Model_Bonus data)
{
    PSB *trav;
    int hashVal = hash(data.employeeID);

    for (trav = &(D->BonusD[hashVal]); *trav != NULL && (data.employeeID != (*trav)->data.employeeID || strcmp((*trav)->data.period, data.period) != 0); trav = &(*trav)->next)
    {
    }

    if (*trav == NULL)
    {
        *trav = (PSB)malloc(sizeof(Model_Bonus) + 1);
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

bool deleteBonus(Dictionary *D, ID bonusID)
{
    PSB *trav, temp;
    int hashVal = hash(bonusID);

    for (trav = &(D->BonusD[hashVal]); *trav != NULL && (*trav)->data.bonusID != bonusID; trav = &(*trav)->next)
    {
    }

    if (*trav == NULL)
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

Model_Bonus *searchBonus(Dictionary D, ID employeeID, char period[])
{
    PSB trav, temp;
    int hashVal = hash(employeeID);

    for (trav = D.BonusD[hashVal]; trav != NULL && (trav->data.employeeID != employeeID || strcmp(trav->data.period, period) != 0); trav = trav->next)
    {
        if (trav->data.employeeID == employeeID && strcmp(trav->data.period, period) == 0)
            break;
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

void debugBonus(Dictionary D)
{
    PSB trav;
    int i;
    printf("\n *****************************************************\n");
    printf(" (DEBUG) DICTIONARY BONUS\n");
    printf("\n *****************************************************\n");
    printf(" %4s | %4s\n", "row", "ID");
    for (i = 0; i < DICT_SIZE; i++)
    {
        printf(" %4d | ", i);
        for (trav = D.BonusD[i]; trav != NULL; trav = trav->next)
        {
            printf(" ID#%d -> ", trav->data.bonusID);
        }
        printf("\n", i);
    }
}

void displayAllBonus(Dictionary D)
{
    PSB trav;
    int i;

    printf(" %-4s___%-9s___%-12s___%-11s___%-7s___%-7s\n",
           "____",
           "_________",
           "____________",
           "___________",
           "_______",
           "_______");
    printf("\t\t\t\tBONUS\n\n");
    printf(" %-4s | %-9s | %-12s | %-11s | %-7s | %-7s\n",
           "#",
           "BONUS ID",
           "EMPLOYEE ID",
           "BONUS NAME",
           "AMOUNT",
           "PERIOD");
    printf(" %-4s | %-9s | %-12s | %-11s | %-7s | %-7s\n",
           "",
           "",
           "",
           "",
           "",
           "");

    for (i = 0; i < DICT_SIZE; i++)
    {
        for (trav = D.BonusD[i]; trav != NULL; trav = trav->next)
        {
            printf(" %4d | %14d | %12d | %8d | %7d | %8d | %9d | %-7s\n",
                   i,
                   trav->data.bonusID,
                   trav->data.employeeID,
                   trav->data.bonusName,
                   trav->data.amount,
                   trav->data.period);
        }
    }

    printf(" %-4s_|_%-9s_|_%-12s_|_%-11s_|_%-7s_|_%-7s\n",
           "____",
           "_________",
           "____________",
           "___________",
           "_______",
           "_______");
    printf("\n End of Dictionary\n\n");
}

void displayBonus(int employeeID, Dictionary *D, char period[])
{
    Model_Bonus *emp = searchBonus(*D, employeeID, period);
    if (emp)
    {
        printf(" _____________________________________________________\n\n");
        printf(" EMPLOYEE #%d - %s         \t\t\n\n", employeeID, period);

        printf(" Bonus ID:       \t%d", emp->bonusID);
        printf("\n Employee ID:    \t%d", emp->employeeID);
        printf("\n Bonus Name:     \t%s", emp->bonusName);
        printf("\n Amount          \t%.2lf", emp->amount);
        printf("\n Period:         \t%s\n", emp->period);
        printf(" _____________________________________________________\n\n");
    }
    else
    {
        printf("\n ERROR: Employee bonus for period %s does not exist.\n", period);
        printf(" _____________________________________________________\n\n");
    }
}

/*----------------------------------- End of Bonus Controller -------------------------------------*/

/*------------------------------- Start of Issue Salary Controller --------------------------------*/

Model_IssueSalary createIssueSalary(Dictionary D, int employeeID, double balance, char period[])
{
    Model_IssueSalary is;

    char dType[15] = "IssueSalary";
    is.issueID = getNewID(dType, D);
    is.employeeID = employeeID;
    is.balance = balance;
    strcpy(is.period, period);

    return is;
}

bool insertIssueSalary(Dictionary *D, Model_IssueSalary data)
{
    PSIS *trav;
    int hashVal = hash(data.employeeID);

    for (trav = &(D->IssueSalaryD[hashVal]); *trav != NULL; trav = &(*trav)->next)
    {
    }

    if (*trav == NULL)
    {
        *trav = (PSIS)malloc(sizeof(Model_IssueSalary) + 1);
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

Model_IssueSalary *searchIssueSalary(Dictionary D, ID employeeID, char period[])
{
    PSIS trav, temp;
    int hashVal = hash(employeeID);

    for (trav = D.IssueSalaryD[hashVal]; trav != NULL && (trav->data.employeeID != employeeID || strcmp(trav->data.period, period) != 0); trav = trav->next)
    {
        if (trav->data.employeeID == employeeID && strcmp(trav->data.period, period) == 0)
            break;
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

void debugSalary(Dictionary D)
{
    PSIS trav;
    int i;
    printf("\n *****************************************************\n");
    printf(" (DEBUG) DICTIONARY SALARY\n");
    printf("\n *****************************************************\n");
    printf(" %4s | %4s\n", "row", "ID");
    for (i = 0; i < DICT_SIZE; i++)
    {
        printf(" %4d | ", i);
        for (trav = D.IssueSalaryD[i]; trav != NULL; trav = trav->next)
        {
            printf(" ID#%d -> ", trav->data.issueID);
        }
        printf("\n", i);
    }
}

void displayAllSalary(Dictionary D, char period[])
{
    PSIS trav;
    int i;

    printf(" %-4s___%-9s___%-12s___%-8s___%7s \n",
           "____",
           "_________",
           "____________",
           "________",
           "_______");
    printf("\t\t\t SALARY\n\n");
    printf(" %-4s | %-9s | %-12s | %-8s | %7s \n",
           "#",
           "ISSUE ID",
           "EMPLOYEE ID",
           "BALANCE",
           "PERIOD");
    printf(" %-4s | %-9s | %-12s | %-8s | %7s \n",
           "",
           "",
           "",
           "",
           "");
    for (i = 0; i < DICT_SIZE; i++)
    {
        for (trav = D.IssueSalaryD[i]; trav != NULL; trav = trav->next)
        {
            if (strcmp(trav->data.period, period) == 0)
            {
                printf(" %-4d | %-9d | %-12d | %-8.2lf | %7s \n",
                       i,
                       trav->data.issueID,
                       trav->data.employeeID,
                       trav->data.balance,
                       trav->data.period);
            }
        }
    }

    printf(" %-4s_|_%-9s_|_%-12s_|_%-8s_|_%7s \n",
           "____",
           "_________",
           "____________",
           "________",
           "_______");
    printf("\n End of Dictionary\n");
}

void displayIssueSalary(Dictionary *D, ID empID, char period[])
{
    Model_IssueSalary *emp = searchIssueSalary(*D, empID, period);
    if (emp)
    {
        printf(" _____________________________________________________\n\n");
        printf(" EMPLOYEE #%d - %s         \t\t\n\n", empID, period);
        printf(" Issue ID:       \t%d  \n", emp->issueID);
        printf(" Employee ID:       \t%d  \n", emp->employeeID);
        printf(" Balance:           \t%d  \n", emp->balance);
        printf(" Period:            \t%s  \n", emp->period);
        printf(" _____________________________________________________\n\n");
    }
    else
    {
        printf(" \n ERROR: Salary for period %s does not exist.", period);
    }
}

bool issueSalary(Dictionary *D, int empID, char period[])
{
    int temp;
    int present;
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

    Model_Attendance *sa = searchAttendance(*D, empID, period);
    if (sa)
    {
        present = sa->present;
        leave = sa->leave;
        absent = sa->absent;
        overtime = sa->overtime;
    }
    else
    {
        printf("\n Employee Attendance could not be found.");
        return false;
    }

    Model_JobInformation *ji = searchJobInformation(*D, empID);
    if (ji)
    {
        basicSalary = ji->basicSalary;
        pagibigDeposit = ji->pagibigDeposit;
    }
    else
    {
        printf("\n Employee Job Information could not be found.");
        return false;
    }

    Model_Bonus *b = searchBonus(*D, empID, period);
    // check is employee has bonus
    if (b)
        additions += b->amount;

    dailyRate = basicSalary / 30;
    hourlyRate = dailyRate / 8;

    // check if employee has absences
    if (leave != absent)
        deductions += (dailyRate * absent);

    // check if employee has overtime
    if (overtime > 0)
        additions += ((hourlyRate * 1.25) * overtime);

    Model_IssueSalary *is = searchIssueSalary(*D, empID, period);
    if (!is)
    {
        income = ((basicSalary + additions) - deductions);
        printf(" _____________________________________________________\n\n");
        printf(" Basic Income: P%.2f\n", basicSalary);
        printf(" Taxable Income: P%.2f\n", income);
        if (b)
            printf(" Bonus: P%.2f\n", b->amount);
        printf(" Additions: P%.2f\n", additions);
        printf(" Deductions: P%.2f\n", deductions);

        tax = calculateTax(basicSalary, income, &pagibigDeposit);
        income += tax;

        printf(" Tax: P%.2f\n", tax);
        printf(" Issue Salary: P%.2f\n", income);
        printf(" _____________________________________________________\n\n");
        printf(" Add Issue Salary to the employee's record for period %s?\n\n", period);
        printf(" [1] Yes\n");
        printf(" [2] No\n");
        printf(" _____________________________________________________\n\n");
        printf(" Select Option: ");
        scanf("%d", &temp);

        if (temp == 1)
        {
            // Create new issue salary
            Model_IssueSalary is2 = createIssueSalary(*D, empID, income, period);
            insertIssueSalary(D, is2);
            // Update pagibig deposit
            Model_JobInformation *ji2 = searchJobInformation(*D, empID);
            ji2->pagibigDeposit = pagibigDeposit;
            return true;
        }
        else if (temp == 2)
        {
            return false;
        }
        else
        {
            printf(" Input not recognized!");
            return false;
        }
    }
    else
    {
        printf("\n Issue Salary for period %s already exists!", period);
        return false;
    }
}

double calculateTax(double basicIncome, double taxableIncome, double *pagibigDeposit)
{
    double tax = 0;

    // SSS (4%)
    tax += taxableIncome * 0.04;

    if (debug)
    {
        printf("\n (Debug) SSS = %.2lf", tax);
    }

    // Pag-ibig (1% or 2%, max P24,300 per year)
    if (*pagibigDeposit < 24300)
    {
        // Calculate the Pagibig tax for current month
        double pagibigTax = taxableIncome < 1500 ? taxableIncome * 0.01 : taxableIncome * 0.02;

        if (debug)
        {
            printf("\n (Debug) Pagibig Tax = %.2lf", pagibigTax);
        }

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

        if (debug)
        {
            printf("\n (Debug) +Pagibig = %.2lf", tax);
        }
    }

    // PHIC (1.75%)
    tax += taxableIncome * 0.0175;

    if (debug)
    {
        printf("\n (Debug) +PHIC = %.2lf", tax);
    }

    // WISP (P225)
    tax -= 225;

    // Calculate annual tax based on monthly income
    double annualTax = 0;
    double annualSalary = basicIncome * 12;

    if (debug)
    {
        printf("\n (Debug) Annual Salary = %.2lf", annualSalary);
    }

    if (annualSalary <= 250000)
    {
        // 0%
        annualTax += (annualSalary * 0);
    }
    else if (annualSalary <= 400000)
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
    tax += (annualTax / 12);

    if (debug)
    {
        printf("\n (Debug) Annual Tax = %.2lf", annualTax);
        printf("\n (Debug) Monthly Tax = %.2lf", annualTax / 12);
    }

    return tax;
}

/*-------------------------------- End of Issue Salary Controller ---------------------------------*/

/*------------------------------ Start of Job Information Controller ------------------------------*/

Model_JobInformation createJobInformation(Dictionary D, ID employeeID)
{
    Model_JobInformation jobInfo;

    printf("\n CREATE EMPLOYEE JOB INFORMATION\n\n");

    char dType[15] = "JobInformation";
    jobInfo.employmentID = getNewID(dType, D);
    jobInfo.employeeID = employeeID;

    printf(" Job Position: ");
    scanf("%s", &jobInfo.jobPosition);
    fflush(stdin);

    printf(" Job Location: ");
    scanf("%s", &jobInfo.jobLocation);
    fflush(stdin);

    printf(" Job Phone (11 digits): ");
    scanf("%s", &jobInfo.jobPhone);
    fflush(stdin);

    printf(" Start Date (mm/dd/yy): ");
    scanf("%s", &jobInfo.startDate);
    fflush(stdin);

    printf(" Department: ");
    scanf("%s", &jobInfo.department);
    fflush(stdin);

    printf(" Job Email: ");
    scanf("%s", &jobInfo.jobEmail);
    fflush(stdin);

    printf(" Basic Salary: ");
    scanf("%lf", &jobInfo.basicSalary);
    fflush(stdin);

    printf(" Pagibig Deposit: ");
    scanf("%lf", &jobInfo.pagibigDeposit);
    fflush(stdin);

    return jobInfo;
}

bool insertJobInformation(Dictionary *D, Model_JobInformation data)
{
    PSJI *trav;
    int hashVal = hash(data.employmentID);

    for (trav = &(D->JobInformationD[hashVal]); *trav != NULL && (*trav)->data.employmentID != data.employmentID; trav = &(*trav)->next)
    {
    }

    if (*trav == NULL)
    {
        *trav = (PSJI)malloc(sizeof(Model_JobInformation) + 1);
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

Model_JobInformation *searchJobInformation(Dictionary D, ID employeeID)
{
    PSJI trav, temp;
    int hashVal = hash(employeeID);

    for (trav = D.JobInformationD[hashVal]; trav != NULL && trav->data.employeeID != employeeID; trav = trav->next)
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

void debugJobInformation(Dictionary D)
{
    PSJI trav;
    int i;
    printf("\n *****************************************************\n");
    printf(" (DEBUG) DICTIONARY JOB INFORMATION\n");
    printf("\n *****************************************************\n");
    printf(" %4s | %4s\n", "row", "ID");
    for (i = 0; i < DICT_SIZE; i++)
    {
        printf(" %4d | ", i);
        for (trav = D.JobInformationD[i]; trav != NULL; trav = trav->next)
        {
            printf(" ID#%d -> ", trav->data.employmentID);
        }
        printf("\n", i);
    }
}

void displayAllJobInformation(Dictionary D)
{
    PSJI trav;
    int i;

    printf(" %-4s___%-14s___%-13s___%-13s___%-10s___%-11s___%-10s___%-13s___%-16s \n",
           "____",
           "______________",
           "_____________",
           "_____________",
           "__________",
           "___________",
           "__________",
           "______________",
           "_________________");
    printf(" JOB INFORMATION\n\n");
    printf(" %-4s | %-14s | %-13s | %-13s | %-10s | %-11s | %-10s | %-13s | %-16s \n",
           "#",
           "EMPLOYMENT ID",
           "JOB POSITION",
           "JOB LOCATION",
           "JOB PHONE",
           "DEPARTMENT",
           "JOB EMAIL",
           "BASIC SALARY",
           "PAGIBIG DEPOSIT");
    printf(" %-4s | %-14s | %-13s | %-13s | %-10s | %-11s | %-10s | %-13s | %-16s \n",
           "",
           "",
           "",
           "",
           "",
           "",
           "",
           "",
           "");

    for (i = 0; i < DICT_SIZE; i++)
    {
        for (trav = D.JobInformationD[i]; trav != NULL; trav = trav->next)
        {
            printf(" %-4s | %-9s | %-12s | %-9s | %-8s | %7s \n",
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

    printf(" %-4s_|_%-14s_|_%-13s_|_%-13s_|_%-10s_|_%-11s_|_%-10s_|_%-13s_|_%-16s \n",
           "____",
           "______________",
           "_____________",
           "_____________",
           "__________",
           "___________",
           "__________",
           "______________",
           "_________________");
    printf("\n End of Dictionary\n\n");
}

void displayJobInformation(ID employeeID, Dictionary *D)
{
    Model_JobInformation *ji = searchJobInformation(*D, employeeID);
    if (ji)
    {
        printf(" _____________________________________________________\n\n");
        printf(" EMPLOYEE #%d         \t\t\n\n", employeeID);

        printf(" Employee ID:      \t%d   \n", ji->employeeID);
        printf(" Employment ID:    \t%d   \n", ji->employmentID);
        printf(" Job Position:     \t%s   \n", ji->jobPosition);
        printf(" Job Location:     \t%s   \n", ji->jobLocation);
        printf(" Job Phone:        \t%s   \n", ji->jobPhone);
        printf(" Job Email:        \t%s   \n", ji->jobEmail);
        printf(" Start Date:       \t%s   \n", ji->startDate);
        printf(" Department:       \t%s   \n", ji->department);
        printf(" Basic Salary:     \t%.2lf  \n", ji->basicSalary);
        printf(" Pag-ibig Deposit: \t%.2lf  \n", ji->pagibigDeposit);
        printf(" _____________________________________________________\n\n");
    }
    else
    {
        printf("Employee ID %d not found", employeeID);
    }
}

/*------------------------------- End of Job Information Controller -------------------------------*/

/*---------------------------------- Start of User Controller -------------------------------------*/

Model_User createUserInformation(Dictionary D)
{
    Model_User emp;

    char dType[10] = "User";
    emp.userID = getNewID(dType, D);

    printf(" First Name: ");
    scanf("%s", &emp.firstName);
    fflush(stdin);

    printf(" Last Name: ");
    scanf("%s", &emp.lastName);
    fflush(stdin);

    printf(" Gender [MALE(0) / FEMALE(1)]: ");
    scanf("%u", &emp.gender);
    fflush(stdin);

    printf(" Date of Birth (mm/dd/yy): ");
    scanf("%s", &emp.dateOfBirth);
    fflush(stdin);

    printf(" Filipino Citizen [NO(0) / YES(1)]: ");
    scanf("%u", &emp.filipinoCitizen);
    fflush(stdin);

    printf(" Home Phone (7 digits): ");
    scanf("%s", &emp.homePhone);
    fflush(stdin);

    printf(" Mobile Phone (11 digits): ");
    scanf("%s", &emp.mobilePhone);
    fflush(stdin);

    printf(" Email Address: ");
    scanf("%s", &emp.emailAddress);
    fflush(stdin);

    printf(" Address: ");
    scanf("%s", &emp.address);
    fflush(stdin);

    printf(" User Type [EMPLOYEE(0) / EMPLOYER(1)]: ");
    scanf("%u", &emp.userType);
    fflush(stdin);

    return emp;
}

bool insertUser(Dictionary *D, Model_User data)
{
    PSU *trav;
    int hashVal = hash(data.userID);

    for (trav = &D->UserD[hashVal]; *trav != NULL && strcmp(data.emailAddress, (*trav)->data.emailAddress) != 0; trav = &(*trav)->next)
    {
    }

    if (*trav == NULL)
    {
        *trav = (PSU)malloc(sizeof(Model_User) + 1);
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


bool deleteUser(Dictionary *D, ID userID)
{
    PSU *trav, temp;
    int hashVal = hash(userID);

    for (trav = &(D->UserD[hashVal]); *trav != NULL && (*trav)->data.userID != userID; trav = &(*trav)->next)
    {
    }

    if (*trav == NULL)
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

Model_User *searchUser(Dictionary D, ID userID)
{
    PSU trav, temp;
    int hashVal = hash(userID);

    for (trav = D.UserD[hashVal]; trav != NULL && trav->data.userID != userID; trav = trav->next)
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

void debugUser(Dictionary D)
{
    PSU trav;
    int i;
    printf("\n *****************************************************\n");
    printf(" (DEBUG) DICTIONARY USER\n");
    printf("\n *****************************************************\n");
    printf(" %4s | %4s\n", "row", "ID");
    for (i = 0; i < DICT_SIZE; i++)
    {
        printf(" %4d | ", i);
        for (trav = D.UserD[i]; trav != NULL; trav = trav->next)
        {
            printf(" ID#%d -> ", trav->data.userID);
        }
        printf("\n", i);
    }
}

void displayAllUser(Dictionary D)
{
    PSU trav;
    int i;

    printf(" %-4s___%-8s___%-11s___%-10s___%-7s___%-14s___%-17s___%-10s___%-13s___%-20s___%-20s___%-10s \n",
           "____",
           "________",
           "___________",
           "__________",
           "_______",
           "______________",
           "_________________",
           "__________",
           "_____________",
           "____________________",
           "____________________",
           "__________");
    printf("\t\t\t\t\t\t\t\t\t\t\tUSER\n\n");
    printf(" %-4s | %-8s | %-11s | %-10s | %-7s | %-14s | %-17s | %-10s | %-13s | %-20s | %-20s | %-10s \n",
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
    printf(" %-4s | %-8s | %-11s | %-10s | %-7s | %-14s | %-17s | %-10s | %-13s | %-20s | %-20s | %-10s \n",
           "",
           "",
           "",
           "",
           "",
           "",
           "",
           "",
           "",
           "",
           "",
           "");

    for (i = 0; i < DICT_SIZE; i++)
    {
        for (trav = D.UserD[i]; trav != NULL; trav = trav->next)
        {
            char filipinoCitizen[10];
            char gender[10];
            char userType[10];

            if (trav->data.gender == MALE)
            {
                strcpy(gender, "Male");
            }
            else
            {
                strcpy(gender, "Female");
            }

            if (trav->data.filipinoCitizen == NO)
            {

                strcpy(filipinoCitizen, "No");
            }
            else
            {
                strcpy(filipinoCitizen, "Yes");
            }

            if (trav->data.userType == EMPLOYEE)
            {

                strcpy(userType, "Employee");
            }
            else
            {
                strcpy(userType, "Employer");
            }

            printf(" %-4d | %-8d | %-11s | %-10s | %-7s | %-14s | %-17s | %-10s | %-13s | %-20s | %-20s | %-10s \n",
                   i,
                   trav->data.userID,
                   trav->data.firstName,
                   trav->data.lastName,
                   gender,
                   trav->data.dateOfBirth,
                   filipinoCitizen,
                   trav->data.homePhone,
                   trav->data.mobilePhone,
                   trav->data.emailAddress,
                   trav->data.address,
                   userType);
        }
    }

    printf(" %-4s_|_%-8s_|_%-11s_|_%-10s_|_%-7s_|_%-14s_|_%-17s_|_%-10s_|_%-13s_|_%-20s_|_%-20s_|_%-10s \n",
           "____",
           "________",
           "___________",
           "__________",
           "_______",
           "______________",
           "_________________",
           "__________",
           "_____________",
           "____________________",
           "____________________",
           "__________");
    printf("\n End of Dictionary\n\n");
}

void displayUserInformation(ID userID, Dictionary *D)
{
    Model_User *emp = searchUser(*D, userID);
    if (emp)
    {
        printf(" _____________________________________________________\n\n");
        printf(" EMPLOYEE #%d        \t\t\n\n", userID);
        printf(" Employee ID:      \t%d  \n", emp->userID);
        printf(" First Name:       \t%s  \n", emp->firstName);
        printf(" Last Name:        \t%s  \n", emp->lastName);

        if (emp->gender == MALE)
        {
            printf(" Gender:           \t%s  \n", "MALE");
        }
        else
        {
            printf(" Gender:           \t%s  \n", "FEMALE");
        }

        printf(" Date of Birth     \t%s  \n", emp->dateOfBirth);

        if (emp->filipinoCitizen == NO)
        {
            printf(" Filipino:           \t%s  \n", "NO");
        }
        else
        {
            printf(" Filipino:           \t%s  \n", "YES");
        }

        printf(" Home Phone:       \t%s  \n", emp->homePhone);
        printf(" Mobile Phone:     \t%s  \n", emp->mobilePhone);
        printf(" Email:            \t%s  \n", emp->emailAddress);
        printf(" Address           \t%s  \n", emp->address);
        if (emp->userType == EMPLOYEE)
        {
            printf(" User Type:           \t%s  \n", "EMPLOYEE");
        }
        else
        {
            printf(" User Type:           \t%s  \n", "EMPLOYER");
        }
        printf(" _____________________________________________________\n\n");
    }
    else
    {
        printf(" Employee ID %d not found\n", userID);
    }
}

/*----------------------------------- End of User Controller --------------------------------------*/

/*---------------------------------- Start of Debug Controller -------------------------------------*/

void displayDictionariesCount(Dictionary D)
{
    printf(" *****************************************************\n");
    printf(" Dictionaries Count\n");
    printf(" *****************************************************\n");
    printf(" Attendance: %d\n", D.count[0]);
    printf(" Bonus: %d\n", D.count[1]);
    printf(" Issue Salary: %d\n", D.count[2]);
    printf(" Job Information: %d\n", D.count[3]);
    printf(" User: %d\n", D.count[4]);
    printf(" *****************************************************\n");
}

/*---------------------------------- End of Debug Controller --------------------------------------*/

/*----------------------------------- Start of UI Controller --------------------------------------*/

void header(void)
{
    printf(" _____________________________________________________\n");
    printf("   _          _   _           __     __ ___ _      \n");
    printf("  |_) /\\ \\_/ |_) / \\ |  |    (_ \\_/ (_   | |_ |\\/| \n");
    printf("  |  /--\\ |  | \\ \\_/ |_ |_   __) |  __)  | |_ |  | \n");
    printf(" _____________________________________________________\n\n");
}

void invalidInput(void)
{
    printf("\n ERROR: Please enter a vaid input*\n");
    printf(" _____________________________________________________\n\n");
    printf(" *Press any key to continue...* ");
    getch();
}

/*------------------------------------ End of UI Controller ---------------------------------------*/

/*------------------------------------- End of Functions ------------------------------------------*/
