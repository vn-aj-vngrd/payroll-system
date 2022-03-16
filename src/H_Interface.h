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
        printf("[1] Create Employee\n");
        printf("[2] Create Attendance\n");
        printf("[3] Create Bonus\n");
        printf("[4] Issue Employee Salary\n");
        printf("[5] View/Update Employee Attendance\n");
        printf("[6] View/Update Employee Profile\n");
        printf("[7] View/Update Employee Job Information\n");
        printf("[8] View/Update Bonus\n");
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

        // Create Attendance
        case 2:

        // Create Bonus
        case 3:

        // Issue Employee Salary & Tax
        case 4:
            printf("Enter Employee ID: ");
            scanf("%d", &empID);
            issueSalary(empID, D);
            printf("\n*Press any key to continue...*");
            getch();
            break;

        // View/Update Employee Attendance
        case 5:
            system("cls");
            while (In2)
            {
                printf("[1] View Employee Attendance\n");
                printf("[2] View All Employee Attendance\n");
                printf("[3] Set Employee Attendance\n");
                printf("[4] Set Employee Leave\n");
                printf("[5] Set Employee Absence\n");
                printf("[6] Set Employee Overtime Hours\n");
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
                    displayUserInformation(empID, D); 

                    printf("\n*Press any key to continue...*");
                    getch();
                    break;
                case 2:
                    displayAllEmployeeAttendence(*D); 

                    printf("\n*Press any key to continue...*");
                    getch();
                    break;
                case 3:
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    setPresent(empID, D);

                    printf("\n*Press any key to continue...*");
                    getch();
                    break;
                case 4:
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    setLeave(empID, D);

                    printf("\n*Press any key to continue...*");
                    getch();
                    break;
                case 5:
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    setAbsent(empID, D);

                    printf("\n*Press any key to continue...*");
                    getch();
                    break;
                case 6:
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
        case 6:
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
                    Schema_User *empInfo = searchUser(*D, empID);

                    while (In6)
                    {
                        printf("UPDATE JOB INFORMATION\n\n");
                        printf("[1] First Name\n");
                        printf("[2] Last Name \n");
                        printf("[3] Gender\n");
                        printf("[4] Date of Birth\n");
                        printf("[5] Filipino Citizenship\n");
                        printf("[6] Home Phone\n");
                        printf("[7] Mobile Phone\n");
                        printf("[8] Email\n");
                        printf("[9] Address\n");
                        printf("[10] Update All\n");
                        printf("[0] Back\n\n");
                        printf("Input: ");
                        scanf("%d", temp);

                        system("cls");
                        printf("| First Name:      \t%s    |", empInfo->firstName);
                        printf("| Last Name:       \t%s    |", empInfo->lastName);
                        printf("| Gender:          \t%d    |", empInfo->gender);
                        printf("| Date of Birth:   \t%s    |", empInfo->dateOfBirth);
                        printf("| Filipino Citizen:\t%d    |", empInfo->filipinoCitizen);
                        printf("| Home Phone:      \t%s    |", empInfo->homePhone);
                        printf("| Mobile Phone:    \t%s    |", empInfo->mobilePhone);
                        printf("| Email:           \t%s    |", empInfo->emailAddress);
                        printf("| Address:         \t%s    |", empInfo->address);

                        switch (temp)
                        {
                        case 1:
                            printf("\n\nEnter new first name: ");
                            scanf("%s", &empInfo->firstName);
                            break;
                        case 2:
                            printf("\n\nEnter new last name: ");
                            scanf("%s", &empInfo->lastName);
                            break;
                        case 3:
                            printf("\n\nEnter new gender [MALE/FEMALE]: ");
                            scanf("%s", &empInfo->gender);
                            break;
                        case 4:
                            printf("\n\nEnter new date of birth: ");
                            scanf("%s", &empInfo->dateOfBirth);
                            break;
                        case 5:
                            printf("\n\nIs a Filipino citizen? [TRUE/FALSE]: ");
                            scanf("%s", &empInfo->filipinoCitizen);
                            break;
                        case 6:
                            printf("\n\nEnter new home phone: ");
                            scanf("%s", &empInfo->homePhone);
                            break;
                        case 7:
                            printf("\n\nEnter new mobile phone: ");
                            scanf("%lf", &empInfo->mobilePhone);
                            break;
                        case 8:
                            printf("\n\nEnter new email address: ");
                            scanf("%lf", &empInfo->emailAddress);
                            break;
                        case 9:
                            printf("\n\nEnter new address: ");
                            scanf("%lf", &empInfo->address);
                            break;
                        case 10:
                            Schema_User data;

                            // bool updateJobInformation(Dictionary *D, Schema_JobInformation data, Schema_JobInformation *pointer)
                            printf("\n\nEnter new job position: ");
                            scanf("%s", &data.firstName);

                            printf("\nEnter new job location: ");
                            scanf("%s", &data.lastName);

                            printf("\nEnter new job phone: ");
                            scanf("%s", &data.gender);

                            printf("\nEnter new start date: ");
                            scanf("%s", &data.dateOfBirth);

                            printf("\nEnter new department: ");
                            scanf("%s", &data.filipinoCitizen);

                            printf("\nEnter new email: ");
                            scanf("%s", &data.homePhone);

                            printf("\nEnter new basic salary: ");
                            scanf("%lf", &data.mobilePhone);

                            printf("\nEnter new pagibig deposit: ");
                            scanf("%lf", &data.emailAddress);

                            printf("\nEnter new pagibig deposit: ");
                            scanf("%lf", &data.address);

                            updateUser(&D, data, empInfo);
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
        case 7:
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

                        system("cls");
                        printf("| Job Position:   \t%s    |", jobInfo->jobPosition);
                        printf("| Job Location:   \t%s    |", jobInfo->jobLocation);
                        printf("| Job Phone:      \t%s    |", jobInfo->jobPhone);
                        printf("| Start Date:     \t%s    |", jobInfo->startDate);
                        printf("| Department:     \t%s    |", jobInfo->department);
                        printf("| Email:          \t%s    |", jobInfo->jobEmail);
                        printf("| Basic Salary:   \tP%lf  |", jobInfo->basicSalary);
                        printf("| Pagibig Deposit:\tP%lf  |", jobInfo->pagibigDeposit);

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

        // View/Update Bonus
        case 8:

        default:
            printf("Please enter a valid option.");
            break;
        }
    }
}

#endif