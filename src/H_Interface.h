#ifndef INTERFACE_H
#define INTERFACE_H

#include "H_Schema.h"
#include "H_Model.h"
#include "C_AttendanceController.h"
#include "C_BonusController.h"
#include "C_DictionaryController.h"
#include "C_JobInformationController.h"
#include "C_IssueSalaryController.h"
#include "C_UserController.h"

void showMenu(Dictionary *D)
{
    int temp;
    int empID;
    bool In = true, In2 = true, In3 = true, In4 = true, In5 = true, In6 = true;
    Schema_JobInformation *jiPtr;

    while (In)
    {
        system("cls");
        printf("Payroll System\n\n");
        printf("[2] Issue Employee Salary\n");
        printf("[1] Create Employee\n");
        printf("[3] View/Update Employee Attendance\n");
        printf("[4] View/Update Employee Profile\n");
        printf("[5] View/Update Employee Job Information\n");
        printf("[0] Exit\n\n");
        printf("Select: ");
        scanf("%d", &temp);
        fflush(stdin);

        switch (temp)
        {
        case 0:

            In = false;
            break;

        // Create Employee -- Completed
        case 1:
            Schema_User employeeInfo = createUserInformation(*D);
            bool b1 = insertUser(&D, employeeInfo);

            Schema_JobInformation jobInfo = createJobInformation(*D, employeeInfo.userID);
            bool b2 = insertJobInformation(&D, jobInfo);

            if (b1 && b2)
            {
                printf("\nEmployee created successfully!\n");
            }
            else
            {
                printf("\nEmployee creation failed!\n");
            }

            printf("\n*Press any key to continue...*");
            getch();
            break;

        // Calculate Employee Salary & Tax -- Completed
        case 2:
            printf("Enter Employee ID: ");
            scanf("%d", &empID);
            issueSalary(empID);
            printf("\n*Press any key to continue...*");
            getch();
            break;

        // View/Update Employee Attendance
        case 3:
            system("cls");
            while (In2)
            {
                printf("[1] View Employee Attendance\n");
                printf("[2] View All Employee Attendance\n");
                printf("[3] Set Employee Leave\n");
                printf("[4] Set Employee Absence\n");
                printf("[5] Set Employee Overtime Hours\n");
                printf("[0] Back\n\n");
                printf("Input: ");
                scanf("%d", &temp);
                switch (temp)
                {
                case 0:
                    In2 = false;
                    break;
                case 1:
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    displayEmployeeAttendence(empID, D);

                    printf("\n*Press any key to continue...*");
                    getch();
                    break;
                case 2:
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    setLeave(empID, D);

                    printf("\n*Press any key to continue...*");
                    getch();
                    break;
                case 3:
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    setAbsence(empID, D);

                    printf("\n*Press any key to continue...*");
                    getch();
                    break;
                case 4:
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    setOvertime(empID, D);

                    printf("\n*Press any key to continue...*");
                    getch();
                    break;
                default:
                    printf("Error! Input not recognized!");

                    printf("\n*Press any key to continue...*");
                    getch();
                    break;
                }
            }
            In2 = true;
            break;

        // View/Update Employee Profile
        case 4:
            system("cls");
            while (In3)
            {
                printf("EMPLOYEE PROFILE\n\n");
                printf("[1] View\n");
                printf("[2] Update\n");
                printf("[3] Delete\n");
                printf("[0] Back\n\n");
                printf("Input: ");
                scanf("%d", &temp);

                switch (temp)
                {
                case 0:
                    In3 = false;
                    break;
                case 1:
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    displayEmployeeInformation(empID, D);

                    printf("\n*Press any key to continue...*");
                    getch();
                    break;
                case 2:
                    system("cls");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    Schema_JobInformation *jobInfo = searchJobInformation(*D, empID);

                    while (In6)
                    {
                        printf("UPDATE JOB INFORMATION\n\n");
                        printf("[1] First Name\n");
                        printf("[2] Last Name \n");
                        printf("[3] Gender\n");
                        printf("[4] Filipino Citizenship\n");
                        printf("[5] Home Phone\n");
                        printf("[6] Mobile Phone\n");
                        printf("[7] Basic Salary\n");
                        printf("[8] Email\n");
                        printf("[9] Address\n");
                        printf("[10] Update All\n");
                        printf("[0] Back\n\n");
                        printf("Input: ");
                        scanf("%d", temp);

                        switch (temp)
                        {
                        case 1:
                            printf("\n\nEnter new job position: ");
                            scanf("%s", &jobInfo->jobPosition);
                            break;
                        case 2:
                            printf("\n\nEnter new job location: ");
                            scanf("%s", &jobInfo->jobLocation);
                            break;
                        case 3:
                            printf("\n\nEnter new job phone: ");
                            scanf("%s", &jobInfo->jobPhone);
                            break;
                        case 4:
                            printf("\n\nEnter new start date: ");
                            scanf("%s", &jobInfo->startDate);
                            break;
                        case 5:
                            printf("\n\nEnter new department: ");
                            scanf("%s", &jobInfo->department);
                            break;
                        case 6:
                            printf("\n\nEnter new email: ");
                            scanf("%s", &jobInfo->jobEmail);
                            break;
                        case 7:
                            printf("\n\nEnter new basic salary: ");
                            scanf("%lf", &jobInfo->basicSalary);
                            break;
                        case 8:
                            printf("\n\nEnter new pagibig deposit: ");
                            scanf("%lf", &jobInfo->pagibigDeposit);
                            break;
                        case 8:
                            printf("\n\nEnter new pagibig deposit: ");
                            scanf("%lf", &jobInfo->pagibigDeposit);
                            break;
                        case 10:
                            Schema_JobInformation data;

                            // bool updateJobInformation(Dictionary *D, Schema_JobInformation data, Schema_JobInformation *pointer)
                            printf("\n\nEnter new job position: ");
                            scanf("%s", &data.jobPosition);

                            printf("\nEnter new job location: ");
                            scanf("%s", &data.jobLocation);

                            printf("\nEnter new job phone: ");
                            scanf("%s", &data.jobPhone);

                            printf("\nEnter new start date: ");
                            scanf("%s", &data.startDate);

                            printf("\nEnter new department: ");
                            scanf("%s", &data.department);

                            printf("\nEnter new email: ");
                            scanf("%s", &data.jobEmail);

                            printf("\nEnter new basic salary: ");
                            scanf("%lf", &data.basicSalary);

                            printf("\nEnter new pagibig deposit: ");
                            scanf("%lf", &data.pagibigDeposit);

                            updateJobInformation(&D, data, jobInfo);
                            break;
                        case 0:
                            In6 = false;
                            break;
                        default:
                            printf("Please enter a valid option.");
                            break;
                        }
                    }
                    In6 = true;
                    printf("\n*Press any key to continue...*");
                    getch();
                    break;
                case 3:
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    deleteEmployeeInformation(empID, D);

                    printf("\n*Press any key to continue...*");
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
                printf("JOB INFORMATION\n\n");
                printf("[1] View\n");
                printf("[2] Update\n");
                printf("[3] Delete\n");
                printf("[0] Back\n\n");
                printf("Input: ");
                scanf("%d", &temp);

                switch (temp)
                {
                case 0:
                    In4 = false;
                    break;
                case 1:
                    system("cls");
                    printf("VIEW JOB INFORMATION\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    displayEmployeeJobInfo(&D, empID);

                    printf("\n*Press any key to continue...*");
                    getch();
                    break;
                case 2:
                    system("cls");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    Schema_JobInformation *jobInfo = searchJobInformation(*D, empID);

                    while (In5)
                    {
                        printf("UPDATE JOB INFORMATION\n\n");
                        printf("[1] Job Position\n");
                        printf("[2] Job Location\n");
                        printf("[3] Job Phone\n");
                        printf("[4] Start Date\n");
                        printf("[5] Department\n");
                        printf("[6] Email\n");
                        printf("[7] Basic Salary\n");
                        printf("[8] Pagibig Deposit\n");
                        printf("[9] Update All\n");
                        printf("[0] Back\n\n");
                        printf("Input: ");
                        scanf("%d", temp);

                        switch (temp)
                        {
                        case 1:
                            printf("\n\nEnter new job position: ");
                            scanf("%s", &jobInfo->jobPosition);
                            break;
                        case 2:
                            printf("\n\nEnter new job location: ");
                            scanf("%s", &jobInfo->jobLocation);
                            break;
                        case 3:
                            printf("\n\nEnter new job phone: ");
                            scanf("%s", &jobInfo->jobPhone);
                            break;
                        case 4:
                            printf("\n\nEnter new start date: ");
                            scanf("%s", &jobInfo->startDate);
                            break;
                        case 5:
                            printf("\n\nEnter new department: ");
                            scanf("%s", &jobInfo->department);
                            break;
                        case 6:
                            printf("\n\nEnter new email: ");
                            scanf("%s", &jobInfo->jobEmail);
                            break;
                        case 7:
                            printf("\n\nEnter new basic salary: ");
                            scanf("%lf", &jobInfo->basicSalary);
                            break;
                        case 8:
                            printf("\n\nEnter new pagibig deposit: ");
                            scanf("%lf", &jobInfo->pagibigDeposit);
                            break;
                        case 9:
                            Schema_JobInformation data;

                            // bool updateJobInformation(Dictionary *D, Schema_JobInformation data, Schema_JobInformation *pointer)
                            printf("\n\nEnter new job position: ");
                            scanf("%s", &data.jobPosition);

                            printf("\nEnter new job location: ");
                            scanf("%s", &data.jobLocation);

                            printf("\nEnter new job phone: ");
                            scanf("%s", &data.jobPhone);

                            printf("\nEnter new start date: ");
                            scanf("%s", &data.startDate);

                            printf("\nEnter new department: ");
                            scanf("%s", &data.department);

                            printf("\nEnter new email: ");
                            scanf("%s", &data.jobEmail);

                            printf("\nEnter new basic salary: ");
                            scanf("%lf", &data.basicSalary);

                            printf("\nEnter new pagibig deposit: ");
                            scanf("%lf", &data.pagibigDeposit);

                            updateJobInformation(&D, data, jobInfo);
                            break;
                        case 0:
                            In5 = false;
                            break;
                        default:
                            printf("Please enter a valid option.");
                            break;
                        }
                    }
                    In5 = true;
                    printf("\n*Press any key to continue...*");
                    getch();
                    break;
                case 3:
                    system("cls");
                    printf("DELETE JOB INFORMATION\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    deleteJobInformation(&D, empID);

                    printf("\n*Press any key to continue...*");
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