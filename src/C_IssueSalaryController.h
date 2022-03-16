#ifndef ISSUESALARYCONTROLLER_H
#define ISSUESALARYCONTROLLER_H

#include "H_Libraries.h"
#include "H_Schema.h"
#include "H_Model.h"
#include "C_DictionaryController.h"

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

// bool issueSalary(int empID)
// {
//     Schema_Attendance sa;
//     Schema_JobInformation ji;
//     int fSize;

//     // Read Attendance
//     FILE *fptr = fopen("Employee_Attendance.bin", "rb");
//     if (fptr != NULL)
//     {
//         fseek(fptr, 0, SEEK_END);
//         fSize = ftell(fptr);
//         rewind(fptr);

//         while (empID != sa.employeeID && ftell(fptr) < fSize)
//         {
//             fread(&sa, sizeof(Schema_Attendance), 1, fptr);
//         }
//         fclose(fptr);
//     }
//     else
//     {
//         printf("Error! Failed to open file Employee_Attendance.bin");
//         return false;
//     }

//     // Read Job Information
//     fptr = fopen("Employee_JobInformation.bin", "rb+");
//     if (fptr != NULL)
//     {
//         fseek(fptr, 0, SEEK_END);
//         fSize = ftell(fptr);
//         rewind(fptr);

//         while (empID != ji.employeeID && ftell(fptr) < fSize)
//         {
//             fread(&ji, sizeof(Schema_JobInformation), 1, fptr);
//         }
//         fclose(fptr);
//     }
//     else
//     {
//         printf("Error! Failed to open file Employee_JobInformation.bin");
//         return false;
//     }

//     // Read Issue Salary
//     fptr = fopen("Employee_JobInformation.bin", "rb+");
//     if (fptr != NULL)
//     {
//         fseek(fptr, 0, SEEK_END);
//         fSize = ftell(fptr);
//         rewind(fptr);

//         while (empID != ji.employeeID && ftell(fptr) < fSize)
//         {
//             fread(&ji, sizeof(Schema_JobInformation), 1, fptr);
//         }
//         fclose(fptr);
//     }
//     else
//     {
//         printf("Error! Failed to open file Employee_JobInformation.bin");
//         return false;
//     }

//     int leaveNum;
//     int absentNum;
//     int overtime; // # of overtime hours

//     double hourlyRate;
//     double dailyRate;
//     double basicSalary;
//     double pagibigDeposit;
//     double deductions;
//     double additions;
//     double income;
//     double tax;

//     // retrieve data from structure
//     basicSalary = ji.basicSalary;
//     dailyRate = basicSalary / 30;
//     hourlyRate = dailyRate / 8;

//     leaveNum = sa.leave;
//     absentNum = sa.absent;
//     overtime = sa.overtime;

//     pagibigDeposit = ji.pagibigDeposit;

//     // check if no. of leaves == no. of absents
//     if (leaveNum == absentNum)
//     {
//         // check if employee has overtime
//         if (overtime > 0)
//         {
//             additions = ((hourlyRate * 1.25) * overtime);
//         }
//     }
//     else
//     {
//         deductions = (dailyRate * absentNum);
//     }

//     income = ((basicSalary + additions) - deductions);
//     tax = calculateTax(income, &pagibigDeposit);
//     income -= tax;

//     // printf("\nIncome: P%.2f", income);
//     // printf("\nTax: P%.2f", tax);
//     int x;
//     printf("This will add P%.2f to the eployee's issue salary record. Continue?\n\n", income, tax);
//     printf("[1] Yes\n");
//     printf("[2] No\n");
//     scanf("%d", &x);

//     switch (x)
//     {
//     case 1:
//         // Update Pagibig Deposit
//         fptr = fopen("Employee_JobInformation.bin", "rb+");
//         if (fptr != NULL)
//         {
//             fseek(fptr, 0, SEEK_SET);
//             while (empID != ji.employeeID && ftell(fptr) < fSize)
//             {
//                 fwrite(&pagibigDeposit, sizeof(double), 1, fptr);
//             }
//             fclose(fptr);
//         }
//         else
//         {
//             printf("Error! Failed to open file Employee_JobInformation.bin");
//             return false;
//         }

//         return true;
//         break;

//     case 2:
//         return false;
//         break;

//     default:
//         printf("Input not recognized. Canceled operation.");
//         return false;
//         break;
//     }
// }

bool issueSalary(int empID, Dictionary *D)
{
    // TODO: Read Attendance
    // TODO: Read Job Information
    // TODO: Update Job Information
    // TODO: Read Issue Salary
    // TODO: Create Issue Salary

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

    printf("Enter month");
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
        printf("Employee Attendance could not be found.");
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
        printf("Employee Job Information could not be found.");
        return false;
    }

    Schema_Bonus *b = searchBonus(*D, empID, period);
    if (b) {
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
        // Calculate taxable income
        // Calculate tax
        // Salary = taxable income - tax
    }
    else
    {
        printf("Issue Salary for %s already exists!", period);
        return false;
    }

    return true;
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

void displayAllSalary(Dictionary D)
{
    PSIS trav;
    int i;

    printf("%-4s | %-9s | %-12s | %-9s | %-8s | %7s \n",
           "____",
           "_________",
           "____________",
           "_________",
           "________",
           "_______");
    printf("SALARY\n");
    printf("%-4s | %-9s | %-12s | %-9s | %-8s | %7s \n",
           "____",
           "_________",
           "____________",
           "_________",
           "________",
           "_______");
    printf("%-4s | %-9s | %-12s | %-9s | %-8s | %7s \n",
           "#",
           "ISSUE ID",
           "EMPLOYEE ID",
           "BONUS ID",
           "BALANCE",
           "PERIOD");

    for (i = 0; i < DICT_SIZE; i++)
    {
        for (trav = D.IssueSalaryD[i]; trav != NULL; trav = trav->next)
        {
            printf("%-4s | %-9s | %-12s | %-9s | %-8s | %7s \n",
                   i,
                   trav->data.issueID,
                   trav->data.employeeID,
                   trav->data.bonusID,
                   trav->data.balance,
                   trav->data.period);
        }
    }

    if (trav == NULL && i == DICT_SIZE - 1)
    {
        printf("%-4s | %-9s | %-12s | %-9s | %-8s | %7s \n",
           "____",
           "_________",
           "____________",
           "_________",
           "________",
           "_______");
        printf("End of Dictionary\n");
    }
}

#endif