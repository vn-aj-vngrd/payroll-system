#ifndef TASKS_H
#define TASKS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Schema.h"
#include "Database.h"

bool run = true;

/*
 * Accepts employee information from employer.
 **/
bool createEmployee()
{
    Schema_User emp;
    Schema_JobInformation jobInfo;

    // Create employee basic information
    printf("Create Employee");
    printf("\nCreate Employee Information");

    emp.userID = getNewID("EmployeeInformation.bin", 'U');
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

    jobInfo.employmentID = getNewID("JobInformation", 'J');

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

    bool isSuccess = writeEmployeeToFile(emp, jobInfo);

    return isSuccess;
}

/*
 * Write employee's user details and job information records to file.
 * @param emp (Schema_User) The employee's user details record.
 * @param jobInfo (Schema_JobInformation) The employee's job information record.
 * @returns TRUE if file write was successful; FALSE otherwise.
 **/
bool writeEmployeeToFile(Schema_User emp, Schema_JobInformation jobInfo)
{
    bool isSuccess = false;

    FILE *file = fopen("EmployeeAttendance.bin", "wb");
    if (file)
    {
        // Create Employee Information
        fwrite(&emp, sizeof(Employee), 1, file);
        fclose(file);
        bool isSuccess = true;
    }
    else
    {
        bool isSuccess = false;
    }

    *file = fopen("EmployeeAttendance.bin", "wb");
    if (file)
    {
        // Create Job Information
        fwrite(&jobInfo, sizeof(JobInformation), 1, file);
        bool isSuccess = true;
    }
    else
    {
        bool isSuccess = false;
    }

    return isSuccess;
}

/*
 * Write an employee's monthly attendance record to file.
 * @param attendance (Schema_Attendance) The employee's attendace record.
 * @returns TRUE if file write was successful; FALSE otherwise.
 **/
bool writeAttendanceToFile(Schema_Attendance attendance)
{
    FILE *file = fopen("EmployeeAttendance.bin", "w");
    if (file)
    {
        fwrite(&attendance, sizeof(Schema_Attendance), 1, file);

        fclose(file);

        return true;
    }
    else
    {
        return false;
    }
}

/*
 * Creates an employee's monthly salary record.
 * @param empID The ID of the employee.
 * @returns The monthly salary of the employee.
 **/
float createSalary(int empID)
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

    FILE *fptr = fopen("JobInformation.bin", "rb+");
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
    int overtime; //# of overtime hours

    float hourlyRate;
    float dailyRate;
    float basicSalary;
    float pagibigDeposit;
    float deductions;
    float additions;
    float income;

    // input necessary info
    scanf("%");

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
    income -= calculateTax(income, &pagibigDeposit);

    printf("Income: P%.2f", income);

    // update pagibigDeposit
    if (fptr != NULL)
    {
        fseek(fptr, 0, SEEK_SET);
        while (empID != ji.employeeID && ftell(fptr) < fSize)
        {
            fwrite(&pagibigDeposit, sizeof(ji.pagibigDeposit), 1, fptr);
            fclose(fptr);
        }
    }

    return income;
}

/*
 * Calculates the monthly tax of an employee given the employee's taxable income and pagibig deposit.
 * @param taxableIncome The taxable income of the employee.
 * @param pagibigDeposit The Pagibig deposit of the employee.
 * @returns The monthly tax of the employee to be deducted from their salary.
 **/
float calculateTax(float taxableIncome, float *pagibigDeposit)
{
    float tax = 0;

    // SSS (4%)
    tax += taxableIncome - (taxableIncome * 0.04);

    // Pag-ibig (1% or 2%, max P24,300 per year)
    if (pagibigDeposit < 24300)
    {
        // Calculate the Pagibig tax for current month
        float pagibigTax = taxableIncome < 1500 ? taxableIncome - (taxableIncome * 0.01) : taxableIncome - (taxableIncome * 0.02);

        // Add Pagibig tax such that Pagibig deposit doesn't exceed 24300
        if (*pagibigDeposit + pagibigTax > 24300)
        {
            tax += 24300 - *pagibigDeposit;
            *pagibigDeopsit += 24300 - *pagibigDeposit;
        }
        else
        {
            tax += pagibigTax;
            *pagibigDeopsit += pagibigTax;
        }
    }

    // PHIC (1.75%)
    tax += taxableIncome - (taxableIncome * 0.0175);

    // WISP (P225)
    tax += taxableIncome - 225;

    // Calculate annual tax based on monthly income
    float annualTax = 0;
    float annualSalary = (taxableIncome - tax) * 12;
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
