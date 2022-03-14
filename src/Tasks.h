#ifndef TASKS_H
#define TASKS_H

#include "Schema.h"
#include "Database.h"
#include "Interface.h"

/*
 * Insert employee's user details and job information records to dictionary.
 * @param emp (Schema_User) The employee's user details record.
 * @param jobInfo (Schema_JobInformation) The employee's job information record.
 * @returns TRUE if file write was successful; FALSE otherwise.
 **/
bool insertToDictionary(Schema_User emp, Schema_JobInformation jobInfo)
{
    bool isSuccess = false;

    // Insert employee's user details record to dictionary.
    int pos1 = hashFunc(emp.userID);
    //insertfunction

    // Insert employee's job information to dictionary.
    int pos2 = hashFunc(jobInfo.employmentID);
    //insertfunction

    return isSuccess;
}

/*
 * Accepts employee information from employer.
 * @returns TRUE if createEmployee was successful; FALSE otherwise.
 **/
bool createEmployee()
{
    Schema_User emp;
    Schema_JobInformation jobInfo;

    // Create employee basic information
    printf("Create Employee");
    printf("\nCreate Employee Information");

    char file1[50] = "EmployeeInformation.bin";
    emp.userID = getNewID(file1, 'U');
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

    char file2[50] = "JobInformation.bin";
    jobInfo.employmentID = getNewID(file2, 1);

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

    bool isSuccess = insertToDictionary(emp, jobInfo);

    return isSuccess;
}

/*
 * Write an employee's monthly attendance record to file.
 * @param attendance (Schema_Attendance) The employee's attendace record.
 * @returns TRUE if file write was successful; FALSE otherwise.
 **/
bool writeAttendanceToFile(Schema_Attendance attendance)
{
    FILE *file = fopen("EmployeeAttendance.bin", "wb");
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
 * Calculates the monthly tax of an employee given the employee's taxable income and pagibig deposit.
 * @param taxableIncome The taxable income of the employee.
 * @param pagibigDeposit The Pagibig deposit of the employee.
 * @returns The monthly tax of the employee to be deducted from their salary.
 **/
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

/*
 * Creates an employee's monthly salary record.
 * @param empID The ID of the employee.
 * @returns The monthly salary of the employee.
 **/
double createSalary(int empID)
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
            fclose(fptr);
        }
    }

    return income;
}

#endif
