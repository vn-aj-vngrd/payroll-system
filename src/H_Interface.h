#ifndef INTERFACE_H
#define INTERFACE_H

#include "H_Tasks.h"

void showMenu()
{
    int input1, input2, input3, input4;
    int empID;
    bool In = true, In2 = true, In3 = true, In4 = true;

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
            
            printf("\n*press any key to continue...*");
            getch();
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
                       "[0] Back"
                       "Input: ");
                scanf("%d", &input2);
                switch (input2)
                {
                case 0:
                    In2 = false;
                    break;
                case 1:
                    printf("Enter Employee ID: ");
                    scanf("%d",&empID);
                    displayEmployeeAttendence(empID, D);

                    printf("\n*press any key to continue...*");
                    getch();
                    break;
                case 2:
                    printf("Enter Employee ID: ");
                    scanf("%d",&empID);

                    setLeave(empID, D);
                    printf("\n*press any key to continue...*");
                    getch();
                    break;
                case 3:
                    printf("Enter Employee ID: ");
                    scanf("%d",&empID);
                    setAbsence(empID, D);

                    printf("\n*press any key to continue...*");
                    getch();
                    break;
                case 4:
                    printf("Enter Employee ID: ");
                    scanf("%d",&empID);
                    setOvertime(empID, D);

                    printf("\n*press any key to continue...*");
                    getch();
                    break;
                default:
                    printf("Error! Input not recognized!");

                    printf("\n*press any key to continue...*");
                    getch();
                    break;
                }
            }
            In2 = true;
            break;
        // View Employee Salary & Tax
        case 3:
            printf("Enter Employee ID: ");
            scanf("%d", &empID);
            createSalary(empID);
            printf("\n*press any key to continue...*");
            getch();
            // double salary = createSalary(empID); // XXX: this is for creating salary; make new function for getSalary or combine with option 5.
            break;

        // View/Update Employee Profile
        case 4:
            system("cls");
            while (In3)
            {
                printf("EMPLOYEE PROFILE"
                       "[1] View",
                       "[2] Update",
                       "[3] Delete",
                       "[0] Back",
                       "Input: ");
                scanf("%d", &input3);

                switch (input3)
                {
                case 0:
                    In3 = false;
                    break;
                case 1:
                    printf("Enter Employee ID: ");
                    scanf("%d",&empID);
                    displayEmployeeInformation(empID, D);

                    printf("\n*press any key to continue...*");
                    getch();
                    break;
                case 2:
                    printf("Enter Employee ID: ");
                    scanf("%d",&empID);
                    updateEmployeeInformation(empID, D);

                    printf("\n*press any key to continue...*");
                    getch();
                    break;
                case 3:
                    printf("Enter Employee ID: ");
                    scanf("%d",&empID);
                    deleteEmployeeInformation(empID, D);

                    printf("\n*press any key to continue...*");
                    getch();
                    break;
                default:
                    printf("Error! Input not recognized!");
                    break;
                }
            }
            In3 = true;
            break;

        // View/Update Employee Job Information
        case 5:
            system("cls");
            while (In4)
            {
                printf("JOB INFORMATION",
                       "[1] View",
                       "[2] Update",
                       "[3] Delete",
                       "[0] Back",
                       "Input: ");
                scanf("%d", &input4);

                switch (input4)
                {
                case 0:
                    In4 = false;
                    break;
                case 1:
                    printf("Enter Employee ID: ");
                    scanf("%d",&empID);
                    displayEmployeeJobInfo(empID, D);

                    printf("\n*press any key to continue...*");
                    getch();
                    break;
                case 2:
                    printf("Enter Employee ID: ");
                    scanf("%d",&empID);
                    updateJobInformation(empID, D);

                    printf("\n*press any key to continue...*");
                    getch();
                    break;
                case 3:
                    printf("Enter Employee ID: ");
                    scanf("%d",&empID);
                    deleteJobInformation(empID, D);

                    printf("\n*press any key to continue...*");
                    getch();
                    break;
                default:
                    printf("Error! Input not recognized!");
                    break;
                }
            }
            In4 = true;
            break;

        default:
            printf("Please enter a valid option.");
            break;
        }
    }
}

#endif