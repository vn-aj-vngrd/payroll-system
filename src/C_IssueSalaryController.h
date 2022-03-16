#ifndef ISSUESALARYCONTROLLER_H
#define ISSUESALARYCONTROLLER_H

#include "H_Libraries.h"
#include "H_Schema.h"
#include "H_Model.h"
#include "C_DictionaryController.h"
#include "C_JobInformationController.h"

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
        
        case 2:
            return false;
        
        default:
            printf("Input not recognized!");
            return false;
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

#endif