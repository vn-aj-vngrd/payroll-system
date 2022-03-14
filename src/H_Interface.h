#ifndef INTERFACE_H
#define INTERFACE_H

#include "H_Tasks.h"

void showMenu();

void showMenu()
{
    int input1, input2;
    int empID;
    bool In = true, In2 = true;

    while (In)
    {
        system("cls");
        printf("Payroll System\n\n");
        printf("[1] Create Employee\n");
        printf("[2] View/Update Employee Attendance\n");
        printf("[3] View Employee Salary & Tax\n");
        printf("[4] View/Update Employee Profile\n");
        printf("[5] View/Update Employee Job Information\n");
        printf("[0] Exit\n\n");
        printf("Select: ");
        scanf("%d", &input1);
        fflush(stdin);

        switch (input1)
        {
        case 0:
            printf("test");
            In = false;
            break;

        // Create Employee
        case 1:
            // createEmployee();
            printf("test");
            break;

        // View/Update Employee Attendance
        case 2:
            system("cls");
            while (In2)
            {
                printf("[1] View Employee Attendance",
                       "[2] Set Employee Leave",
                       "[3] Set Employee Absence",
                       "[4] Set Employee Overtime Hours",
                       "[0] Exit"
                       "Input: ");
                scanf("%d", &input2);
                switch (input2)
                {
                case 0:
                    printf("test");
                    In2 = false;
                    break;
                case 1:
                    printf("test");
                    break;
                case 2:
                    printf("test");
                    break;
                case 3:
                    printf("test");
                    break;
                case 4:
                    printf("test");
                    break;
                default:
                    printf("Error! Input not recognized!");
                    break;
                }
            }
            break;
        // View Employee Salary & Tax
        case 3:
            printf("Enter Employee ID: ");
            scanf("%d", &empID);
            // double salary = createSalary(empID); // XXX: this is for creating salary; make new function for getSalary or combine with option 5.
            break;

        // View/Update Employee Profile
        case 4:
            printf("test");
            break;

        // View/Update Employee Job Information
        case 5:
            printf("test");
            break;

        default:
            printf("Please enter a valid option.");
            break;
        }
    }
}

#endif