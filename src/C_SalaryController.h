#ifndef ISSUESALARYCONTROLLER_H
#define ISSUESALARYCONTROLLER_H

#include "H_Libraries.h"
#include "H_Schema.h"
#include "H_Model.h"
#include "C_DictionaryController.h"

void insertIssueSalary(Dictionary *D, Schema_IssueSalary data)
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
        printf("IssueSalary Inserted Successfully\n");
    }
}

void updateIssueSalary(Dictionary *D, Schema_IssueSalary data)
{
    PSIS *trav;
    int hashVal = hash(data.issueID);

    for (trav = &(D->IssueSalaryD[hashVal]); *trav != NULL && (*trav)->data.issueID != data.issueID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        printf("IssueSalary ID not found\n");
    }
    else
    {
        (*trav)->data = data;
        printf("IssueSalary Updated Successfully\n");
    }
}

void deleteIssueSalary(Dictionary *D, ID issueID)
{
    PSIS *trav, temp;
    int hashVal = hash(issueID);

    for (trav = &(D->IssueSalaryD[hashVal]); *trav != NULL && (*trav)->data.issueID != issueID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        printf("IssueSalary ID not found\n");
    }
    else
    {
        temp = *trav;
        *trav = (*trav)->next;
        free(temp);
        D->count[3]++;
        printf("IssueSalary Deleted Successfully\n");
    }
}

Schema_IssueSalary* searchIssueSalary(Dictionary D, ID userID)
{
    PSIS trav, temp;
    int hashVal = hash(userID);

    for (trav = D.IssueSalaryD[hashVal]; trav != NULL && trav->data.issueID != userID; trav = trav->next)
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
        printf("IssueSalary ID not found\n");
        return NULL;
    }
}

double issueSalary(int empID)
{
    Schema_Attendance sa;
    Schema_JobInformation ji;
    int fSize;

    FILE *fptr = fopen("EmployeeAttendance.bin", "rb");
    if (fptr != NULL)
    {
        fseek(fptr, 0, SEEK_END);
        fSize = ftell(fptr);
        rewind(fptr);

        while (empID != sa.employeeID && ftell(fptr) < fSize)
        {
            fread(&sa, sizeof(Schema_Attendance), 1, fptr);
        }
        fclose(fptr);
    }
    else
    {
        printf("Error! Failed to open file!");
    }

    fptr = fopen("JobInformation.bin", "rb+");
    if (fptr != NULL)
    {
        fseek(fptr, 0, SEEK_END);
        fSize = ftell(fptr);
        rewind(fptr);

        while (empID != ji.employeeID && ftell(fptr) < fSize)
        {
            fread(&ji, sizeof(Schema_JobInformation), 1, fptr);
        }
    }
    else
    {
        printf("Error! Failed to open file!");
    }

    int leaveNum;
    int absentNum;
    int overtime; // # of overtime hours

    double hourlyRate;
    double dailyRate;
    double basicSalary;
    double pagibigDeposit;
    double deductions;
    double additions;
    double income;
    double tax;

    // retrieve data from structure
    basicSalary = ji.basicSalary;
    dailyRate = basicSalary / 30;
    hourlyRate = dailyRate / 8;

    leaveNum = sa.excused;
    absentNum = sa.absent;
    overtime = sa.overtime;

    pagibigDeposit = ji.pagibigDeposit;

    // check if no. of leaves == no. of absents
    if (leaveNum == absentNum)
    {
        // check if employee has overtime
        if (overtime > 0)
        {
            additions = ((hourlyRate * 1.25) * overtime);
        }
    }
    else
    {
        deductions = (dailyRate * absentNum);
    }

    income = ((basicSalary + additions) - deductions);
    tax = calculateTax(income, &pagibigDeposit);
    income -= tax;

    printf("\nIncome: P%.2f", income);
    printf("\nTax: P%.2f", tax);

    // update Pagibig deposit
    if (fptr != NULL)
    {
        fseek(fptr, 0, SEEK_SET);
        while (empID != ji.employeeID && ftell(fptr) < fSize)
        {
            fwrite(&pagibigDeposit, sizeof(double), 1, fptr);
        }
        fclose(fptr);
    }

    return income;
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


#endif