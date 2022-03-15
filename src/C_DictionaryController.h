#ifndef GENERALCONTROLLER_H
#define GENERALCONTROLLER_H

#include "H_Libraries.h"
#include "H_Schema.h"
#include "H_Model.h"
#include "C_AttendanceController.h"
#include "C_BonusController.h"
#include "C_DictionaryController.h"
#include "C_JobInformationController.h"
#include "C_SalaryController.h"
#include "C_UserController.h"

void initDictionary(Dictionary D)
{
    int i;
    for (i = 0; i < DICT_SIZE; i++)
    {
        D.UserD[i] = NULL;
        D.JobInformationD[i] = NULL;
        D.AttendanceD[i] = NULL;
        D.IssueSalaryD[i] = NULL;
        D.BonusD[i] = NULL;
    }

    for (i = 0; i < 5; i++)
    {
        D.count[i] = 0;
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

/*
 * Pull the dictionary to file
 * @param D The dictionary
 **/
void pullDictionaries(Dictionary *D, char filename[])
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
        printf("Employee_Attendance.bin not found\n");
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
        printf("Employee_Bonus.bin not found\n");
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
        printf("Employee_JobInformation.bin not found\n");
    }

    // Salary Information
    fp = fopen("Employee_Salary.bin", "rb");
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
        printf("Employee_Salary.bin not found\n");
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
        printf("Employee_Information.bin not found\n");
    }
}

/*
 * Push the dictionary to file
 * @param D The dictionary
 **/
void pushDictionaries(Dictionary D, char filename[])
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
            for (ATrav = &(D.AttendanceD[i]); ATrav != NULL; ATrav = ATrav->next)
            {
                fwrite(&ATrav->data, sizeof(Schema_Attendance), 1, fp);
            }
        }

        fseek(fp, 0L, SEEK_END);
        count = ftell(fp) / sizeof(Schema_Attendance);
        if (count == D.count[0])
        {
            printf("Data saved successfully");
        }
        else
        {
            printf("There was an error saving the data.");
        }

        fclose(fp);
    }

    // Bonus Information
    fp = fopen("Employee_Bonus.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (BTrav = &(D.BonusD[i]); BTrav != NULL; BTrav = BTrav->next)
            {
                fwrite(&BTrav->data, sizeof(Schema_Bonus), 1, fp);
            }
        }

        fseek(fp, 0L, SEEK_END);
        count = ftell(fp) / sizeof(Schema_Bonus);
        if (count == D.count[1])
        {
            printf("Data saved successfully");
        }
        else
        {
            printf("There was an error saving the data.");
        }

        fclose(fp);
    }

    // Job Information
    fp = fopen("Employee_JobInformation.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (JITrav = &(D.JobInformationD[i]); JITrav != NULL; JITrav = JITrav->next)
            {
                fwrite(&JITrav->data, sizeof(Schema_JobInformation), 1, fp);
            }
        }

        fseek(fp, 0L, SEEK_END);
        count = ftell(fp) / sizeof(Schema_JobInformation);
        if (count == D.count[2])
        {
            printf("Data saved successfully");
        }
        else
        {
            printf("There was an error saving the data.");
        }

        fclose(fp);
    }

    // Salary Information
    fp = fopen("Employee_Salary.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (STrav = &(D.IssueSalaryD[i]); STrav != NULL; STrav = STrav->next)
            {
                fwrite(&STrav->data, sizeof(Schema_IssueSalary), 1, fp);
            }
        }

        fseek(fp, 0L, SEEK_END);
        count = ftell(fp) / sizeof(Schema_IssueSalary);
        if (count == D.count[3])
        {
            printf("Data saved successfully");
        }
        else
        {
            printf("There was an error saving the data.");
        }

        fclose(fp);
    }

    // User Information
    fp = fopen("Employee_Information.bin", "wb");
    if (fp)
    {
        for (i = 0; i < DICT_SIZE; i++)
        {
            for (UTrav = &(D.UserD[i]); UTrav != NULL; UTrav = UTrav->next)
            {
                fwrite(&UTrav->data, sizeof(Schema_User), 1, fp);
            }
        }

        fseek(fp, 0L, SEEK_END);
        count = ftell(fp) / sizeof(Schema_User);
        if (count == D.count[4])
        {
            printf("Data saved successfully");
        }
        else
        {
            printf("There was an error saving the data.");
        }

        fclose(fp);
    }
}

#endif