#ifndef INTERFACE_H
#define INTERFACE_H

#include "H_Dictionary.h"
#include "H_Schema.h"
#include "C_Controller.c"
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

void showMenu(Dictionary *D)
{
    bool debug = false;

    int temp;
    int empID;
    char period[MONTH];
    bool In = true, 
        In2 = true, 
        In3 = true, 
        In4 = true, 
        In5 = true, 
        In6 = true, 
        In7 = true, 
        In8 = true, 
        In9 = true, 
        In10 = true;
    Schema_JobInformation *jiPtr;

    while (In)
    {
        system("cls");
        if (debug)
        {
            displayDictionariesCount(*D);
        }

        header();

        if (debug)
        {
            printf("[-5] (Debug) Attendance\n");
            printf("[-4] (Debug) Bonus\n");
            printf("[-3] (Debug) JobInformation\n");
            printf("[-2] (Debug) Salary\n");
            printf("[-1] (Debug) User\n\n");
        }

        printf("[1] Create Employee\n");
        printf("[2] Create Monthly Attendance\n");
        printf("[3] Create Monthly Bonus\n");
        printf("[4] Issue Employee Salary\n");
        printf("[5] Employee Attendance\n");
        printf("[6] Employee Profile\n");
        printf("[7] Employee Job Information\n");
        printf("[8] Employee Bonus\n");
        printf("[9] Employee Salary\n");
        printf("[0] Save and Exit\n\n");
        printf("Select: ");
        scanf("%d", &temp);
        fflush(stdin);

        switch (temp)
        {

        // Push to Dictionary -- Complete
        case 0:
        {
            if (pushUserD(*D) && pushJobInformationD(*D) && pushIssueSalaryD(*D) && pushBonusD(*D) && pushAttendanceD(*D)) // pushUserD(*D) &&
            {
                printf("\nYour changes have been successfully saved.");
            }
            else
            {
                printf("\nFailed to save your changes.");
            }
            In = false;
            break;
        }

        // Create Employee -- Complete
        case 1:
        {
            printf("Create Employee\n\n");
            Schema_User employeeInfo = createUserInformation(*D);
            Schema_JobInformation jobInfo = createJobInformation(*D, employeeInfo.userID);

            if (insertUser(D, employeeInfo) && insertJobInformation(D, jobInfo))
            {
                printf("\nEmployee information was successfully created.");
            }
            else
            {
                printf("\nFailed to create employee information.");
            }

            printf("\n*Press any key to continue...* ");
            getch();
            break;
        }

        // Create Attendance -- See Error
        case 2:
        {
            printf("Create Monthly Attendance\n\n");
            Schema_Attendance sa = createAttendance(*D);
            if (sa.attendanceID == -1)
            {
                printf("\nEmployee ID not found.");
            }
            else
            {
                printf("\nCreating Employee Attendance... \n");

                if (insertAttendance(D, sa))
                {
                    printf("\nEmployee monthly attendance was successfully created.");
                }
                else
                {
                    printf("\nEmployee monthly attendance already exists.");
                }
            }
            printf("\n*Press any key to continue...* ");
            getch();
            break;
        }

        // Create Bonus -- Complete
        case 3:
        {
            printf("Create Monthly Bonus\n\n");
            Schema_Bonus empBonus = createBonus(*D);
            bool b = insertBonus(D, empBonus);
            if (b)
            {
                printf("\nEmployee monthly bonus was successfully created.");
            }
            else
            {
                printf("\nFailed to create employee monthly bonus.");
            }

            printf("\n*Press any key to continue...* ");
            getch();
            break;
        }

        // Issue Employee Salary & Tax -- See Error
        case 4:
        {
            printf("Issue Employee Salary\n\n");
            printf("Enter Employee ID: ");
            scanf("%d", &empID);
            printf("Enter period (mm/yy): ");
            scanf("%s", &period);
            fflush(stdin);

            bool b = issueSalary(D, empID, period);
            if (b)
            {
                printf("\nEmployee salary was successfully issued.");
            }
            else
            {
                printf("\nFailed to issue employee salary.");
            }
            printf("\n*Press any key to continue...* ");
            getch();
            break;
        }

        // Employee Attendance -- Complete
        case 5:
        {

            while (In2)
            {
                system("cls");
                if (debug == true)
                {
                    displayDictionariesCount(*D);
                }
                if (debug == true)
                {
                    displayDictionariesCount(*D);
                }
                header();

                printf("Employee Attendance\n\n");

                printf("EMPLOYEE ATTENDANCE\n\n");
                printf("[1] View Employee Attendance\n");
                printf("[2] View All Employee Attendance\n");
                printf("[3] Update Employee Attendance\n");
                printf("[4] Delete Employee Attendance\n");
                printf("[5] Set Employee Attendance\n");
                printf("[6] Set Employee Leave\n");
                printf("[7] Set Employee Absence\n");
                printf("[8] Set Employee Overtime Hours\n");
                printf("[0] Back\n\n");
                printf("Select Option: ");
                scanf("%d", &temp);
                fflush(stdin);

                switch (temp)
                {
                case 0:
                {
                    In2 = false;
                    break;
                }
                case 1:
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Attendance > View Employee Attendance\n\n");

                    printf("VIEW EMPLOYEE ATTENDANCE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf("Enter Period: ");
                    scanf("%s", &period);
                    fflush(stdin);
                    displayAttendance(D, empID, period);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 2:
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Attendance > View All Employee Attendance\n\n");

                    printf("VIEW ALL EMPLOYEE ATTENDANCE\n\n");
                    printf("Enter Period: ");
                    scanf("%s", &period);
                    displayAllAttendance(*D, period);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 3:
                {
                    char period[20];
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Attendance > Update Employee Attendance\n\n");

                    printf("UPDATE EMPLOYEE ATTENDANCE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf("Enter Period: ");
                    scanf("%s", &period);
                    fflush(stdin);

                    Schema_Attendance *empAttInfo = searchAttendance(*D, empID, period);

                    while (In9)
                    {
                        system("cls");
                        if (debug == true)
                        {
                            displayDictionariesCount(*D);
                        }
                        header();
                        printf("Employee Attendance > Update Employee Attendance\n\n");

                        printf("UPDATE EMPLOYEE ATTENDANCE FOR %s\n\n", period);
                        printf("[1] No. of Present Days\n");
                        printf("[2] No. of Absents\n");
                        printf("[3] No. of Leaves\n");
                        printf("[4] No. of Overtime Hours\n");
                        printf("[5] Period [MM/YY]\n");
                        printf("[6] Update All\n");
                        printf("[0] Back\n\n");
                        printf("Select Option: ");
                        scanf("%d", &temp);
                        fflush(stdin);

                        system("cls");
                        if (debug == true)
                        {
                            displayDictionariesCount(*D);
                        }
                        header();
                        displayAttendance(D, empID, period);

                        switch (temp)
                        {
                        case 0:
                        {
                            In9 = false;
                            break;
                        }
                        case 1:
                        {
                            printf("\n\nEnter new number of present days: ");
                            scanf("%s", &empAttInfo->present);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 2:
                        {
                            printf("\n\nEnter new number of absent days: ");
                            scanf("%s", &empAttInfo->absent);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 3:
                        {
                            printf("\n\nEnter new number of leave days: ");
                            scanf("%s", &empAttInfo->leave);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 4:
                        {
                            printf("\n\nEnter new number of overtime hours: ");
                            scanf("%s", &empAttInfo->overtime);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 5:
                        {
                            printf("\n\nEnter new period: ");
                            scanf("%s", &empAttInfo->period);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 6:
                        {
                            Schema_Attendance att;
                            printf("\n\nEnter new number of present days: ");
                            scanf("%s", &att.present);
                            fflush(stdin);

                            printf("\n\nEnter new number of absent days: ");
                            scanf("%s", &att.absent);
                            fflush(stdin);

                            printf("\n\nEnter new number of leave days: ");
                            scanf("%s", &att.leave);
                            fflush(stdin);

                            printf("\n\nEnter new number of overtime hours: ");
                            scanf("%s", &att.overtime);
                            fflush(stdin);

                            printf("\n\nEnter new period: ");
                            scanf("%s", &att.period);
                            fflush(stdin);

                            updateAttendance(D, att, empAttInfo, period);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }

                        default:
                        {
                            printf("ERROR: Please enter a vaid input*\n");
                            break;
                        }
                        }
                    }
                    In9 = true;
                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }

                case 4:
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Attendance > Delete Employee Attendance\n\n");

                    printf("DELETE EMPLOYEE ATTENDANCE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf("Enter period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    deleteAttendance(D, empID, period);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 5:
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Attendance > Set Employee Attendance\n\n");

                    printf("SET EMPLOYEE ATTENDANCE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf("Enter period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    setPresent(empID, D, period);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 6:
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Attendance > Set Employee Leave\n\n");

                    printf("SET EMPLOYEE LEAVE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf("Enter period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    setLeave(empID, D, period);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 7:
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Attendance > Set Employee Absence\n\n");

                    printf("SET EMPLOYEE ABSENCE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf("Enter period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    setAbsent(empID, D, period);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 8:
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Attendance > Set Employee Overtime Hours\n\n");

                    printf("SET EMPLOYEE OVERTIME HOURS\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf("Enter period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    setOvertime(empID, D, period);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                default:
                {
                    printf("ERROR: Please enter a vaid input*\n");

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                }
            }
            In2 = true;
            break;
        }

        // View/Update Employee Profile -- Complete
        case 6:
        {
            while (In3)
            {
                system("cls");
                if (debug == true)
                {
                    displayDictionariesCount(*D);
                }
                header();
                printf("Employee Profile\n\n");

                printf("EMPLOYEE PROFILE\n\n");
                printf("[1] View\n");
                printf("[2] View All\n");
                printf("[3] Update\n");
                printf("[4] Delete\n");
                printf("[0] Back\n\n");
                printf("Select Option: ");
                scanf("%d", &temp);
                fflush(stdin);

                switch (temp)
                {
                case 0:
                {
                    In3 = false;
                    break;
                }
                case 1:
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Profile > View\n\n");

                    printf("VIEW EMPLOYEE PROFILE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);
                    displayUserInformation(empID, D);

                    printf("\n\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 2:
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Profile > View All\n\n");

                    printf("VIEW ALL EMPLOYEE PROFILE\n\n");
                    displayAllUser(*D);

                    printf("\n\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 3:
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Profile > Update\n\n");

                    printf("UPDATE EMPLOYEE PROFILE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);

                    Schema_User *empInfo = searchUser(*D, empID);

                    while (In6)
                    {
                        system("cls");
                        if (debug == true)
                        {
                            displayDictionariesCount(*D);
                        }
                        header();
                        printf("Employee Profile > Update\n\n");

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
                        printf("Select Option: ");
                        scanf("%d", &temp);
                        fflush(stdin);

                        system("cls");
                        if (debug == true)
                        {
                            displayDictionariesCount(*D);
                        }
                        header();
                        displayUserInformation(empID, D);

                        switch (temp)
                        {
                        case 1:
                        {
                            printf("\n\nEnter new first name: ");
                            scanf("%s", &empInfo->firstName);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 2:
                        {
                            printf("\n\nEnter new last name: ");
                            scanf("%s", &empInfo->lastName);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 3:
                        {
                            printf("\n\nEnter new gender [MALE/FEMALE]: ");
                            scanf("%s", &empInfo->gender);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 4:
                        {
                            printf("\n\nEnter new date of birth: ");
                            scanf("%s", &empInfo->dateOfBirth);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 5:
                        {
                            printf("\n\nIs a Filipino citizen? [YES/NO]: ");
                            scanf("%s", &empInfo->filipinoCitizen);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 6:
                        {
                            printf("\n\nEnter new home phone: ");
                            scanf("%s", &empInfo->homePhone);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 7:
                        {
                            printf("\n\nEnter new mobile phone: ");
                            scanf("%lf", &empInfo->mobilePhone);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 8:
                        {
                            printf("\n\nEnter new email address: ");
                            scanf("%lf", &empInfo->emailAddress);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 9:
                        {
                            printf("\n\nEnter new address: ");
                            scanf("%lf", &empInfo->address);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 10:
                        {
                            Schema_User data;

                            printf("\n\nEnter new first name: ");
                            scanf("%s", &data.firstName);
                            fflush(stdin);

                            printf("\nEnter new last name: ");
                            scanf("%s", &data.lastName);
                            fflush(stdin);

                            printf("\nEnter new gender [MALE/FEMALE]: ");
                            scanf("%d", &data.gender);
                            fflush(stdin);

                            printf("\nEnter new start date: ");
                            scanf("%s", &data.dateOfBirth);
                            fflush(stdin);

                            printf("\nFilipino Citizen? [YES/NO]: ");
                            scanf("%d", &data.filipinoCitizen);
                            fflush(stdin);

                            printf("\nEnter new home phone: ");
                            scanf("%s", &data.homePhone);
                            fflush(stdin);

                            printf("\nEnter new mobile phone: ");
                            scanf("%s", &data.mobilePhone);
                            fflush(stdin);

                            printf("\nEnter new email address: ");
                            scanf("%s", &data.emailAddress);
                            fflush(stdin);

                            printf("\nEnter new address: ");
                            scanf("%s", &data.address);
                            fflush(stdin);

                            updateUser(D, data, empInfo);
                            break;
                        }
                        case 0:
                        {
                            In6 = false;
                            break;
                        }
                        default:
                        {
                            printf("ERROR: Please enter a vaid input*\n");
                            break;
                        }
                        }
                    }
                    In6 = true;
                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 4:
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Profile > Delete\n\n");

                    printf("DELETE EMPLOYEE PROFILE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);
                    bool b = deleteUser(D, empID);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                default:
                {
                    printf("ERROR: Please enter a vaid input*\n");
                    break;
                }
                }
            }
            In3 = true;
            break;
        }

        // View/Update Employee Job Information -- Incomplete
        case 7:
        {
            // while (In4)
            // {
            //     system("cls");
            if (debug == true)
            {
                displayDictionariesCount(*D);
            }
            header();
            //     printf("Employee Job Information\n\n");

            //     printf("JOB INFORMATION\n\n");
            //     printf("[1] View\n");
            //     printf("[2] Update\n");
            //     printf("[3] Delete\n");
            //     printf("[0] Back\n\n");
            //     printf("Select Option: ");
            //     scanf("%d", &temp);
            //     fflush(stdin);

            //     switch (temp)
            //     {
            //     case 0:
            //     {
            //         In4 = false;
            //         break;
            //     }
            //     case 1:
            //     {
            //         system("cls");
            if (debug == true)
            {
                displayDictionariesCount(*D);
            }
            header();
            //         printf("VIEW JOB INFORMATION\n\n");
            //         printf("Enter Employee ID: ");
            //         scanf("%d", &empID);
            //         fflush(stdin);
            //         displayJobInformation(empID, D);

            //         printf("\n*Press any key to continue...* ");
            //         getch();
            //         break;
            //     }
            //     case 2:
            //     {
            //         system("cls");
            if (debug == true)
            {
                displayDictionariesCount(*D);
            }
            header();
            //         printf("UPDATE JOB INFORMATION\n\n");
            //         printf("Enter Employee ID: ");
            //         scanf("%d", &empID);
            //         fflush(stdin);

            //         Schema_JobInformation *jobInfo = searchJobInformation(*D, empID);

            //         while (In5)
            //         {
            //             system("cls");
            if (debug == true)
            {
                displayDictionariesCount(*D);
            }
            header();
            //             printf("UPDATE JOB INFORMATION\n\n");
            //             printf("[1] Job Position\n");
            //             printf("[2] Job Location\n");
            //             printf("[3] Job Phone\n");
            //             printf("[4] Start Date\n");
            //             printf("[5] Department\n");
            //             printf("[6] Email\n");
            //             printf("[7] Basic Salary\n");
            //             printf("[8] Pagibig Deposit\n");
            //             printf("[9] Update All\n");
            //             printf("[0] Back\n\n");
            //             printf("Select Option: ");
            //             scanf("%d", temp);
            //             fflush(stdin);

            //             system("cls");
            if (debug == true)
            {
                displayDictionariesCount(*D);
            }
            header();
            //             displayJobInformation(empID, D);

            //             switch (temp)
            //             {
            //             case 1:
            //             {
            //                 printf("\n\nEnter new job position: ");
            //                 scanf("%s", &jobInfo->jobPosition);
            //                 fflush(stdin);

            //                 printf("\n*Press any key to continue...* ");
            //                 getch();
            //                 break;
            //             }
            //             case 2:
            //             {
            //                 printf("\n\nEnter new job location: ");
            //                 scanf("%s", &jobInfo->jobLocation);
            //                 fflush(stdin);

            //                 printf("\n*Press any key to continue...* ");
            //                 getch();
            //                 break;
            //             }
            //             case 3:
            //             {
            //                 printf("\n\nEnter new job phone: ");
            //                 scanf("%s", &jobInfo->jobPhone);
            //                 fflush(stdin);

            //                 printf("\n*Press any key to continue...* ");
            //                 getch();
            //                 break;
            //             }
            //             case 4:
            //             {
            //                 printf("\n\nEnter new start date: ");
            //                 scanf("%s", &jobInfo->startDate);
            //                 fflush(stdin);

            //                 printf("\n*Press any key to continue...* ");
            //                 getch();
            //                 break;
            //             }
            //             case 5:
            //             {
            //                 printf("\n\nEnter new department: ");
            //                 scanf("%s", &jobInfo->department);
            //                 fflush(stdin);

            //                 printf("\n*Press any key to continue...* ");
            //                 getch();
            //                 break;
            //             }
            //             case 6:
            //             {
            //                 printf("\n\nEnter new email: ");
            //                 scanf("%s", &jobInfo->jobEmail);
            //                 fflush(stdin);

            //                 printf("\n*Press any key to continue...* ");
            //                 getch();
            //                 break;
            //             }
            //             case 7:
            //             {
            //                 printf("\n\nEnter new basic salary: ");
            //                 scanf("%lf", &jobInfo->basicSalary);
            //                 fflush(stdin);

            //                 printf("\n*Press any key to continue...* ");
            //                 getch();
            //                 break;
            //             }
            //             case 8:
            //             {
            //                 printf("\n\nEnter new pagibig deposit: ");
            //                 scanf("%lf", &jobInfo->pagibigDeposit);
            //                 fflush(stdin);

            //                 printf("\n*Press any key to continue...* ");
            //                 getch();
            //                 break;
            //             }
            //             case 9:
            //             {
            //                 Schema_JobInformation data;

            //                 printf("\n\nEnter new job position: ");
            //                 scanf("%s", &data.jobPosition);
            //                 fflush(stdin);

            //                 printf("\nEnter new job location: ");
            //                 scanf("%s", &data.jobLocation);
            //                 fflush(stdin);

            //                 printf("\nEnter new job phone: ");
            //                 scanf("%s", &data.jobPhone);
            //                 fflush(stdin);

            //                 printf("\nEnter new start date: ");
            //                 scanf("%s", &data.startDate);
            //                 fflush(stdin);

            //                 printf("\nEnter new department: ");
            //                 scanf("%s", &data.department);
            //                 fflush(stdin);

            //                 printf("\nEnter new email: ");
            //                 scanf("%s", &data.jobEmail);
            //                 fflush(stdin);

            //                 printf("\nEnter new basic salary: ");
            //                 scanf("%lf", &data.basicSalary);
            //                 fflush(stdin);

            //                 printf("\nEnter new pagibig deposit: ");
            //                 scanf("%lf", &data.pagibigDeposit);
            //                 fflush(stdin);

            //                 updateJobInformation(D, data, jobInfo);
            //                 break;
            //             }
            //             case 0:
            //             {
            //                 In5 = false;
            //                 break;
            //             }
            //             default:
            //             {
            //                 printf("ERROR: Please enter a vaid input*\n");
            //                 break;
            //             }
            //             }
            //         }
            //         In5 = true;
            //         break;
            //     }
            //     case 3:
            //     {
            //         system("cls");
            if (debug == true)
            {
                displayDictionariesCount(*D);
            }
            header();
            //         printf("DELETE JOB INFORMATION\n\n");
            //         printf("Enter Employee ID: ");
            //         scanf("%d", &empID);
            //         fflush(stdin);
            //         deleteJobInformation(D, empID);

            //         printf("\n*Press any key to continue...* ");
            //         getch();
            //         break;
            //     }
            //     default:
            //     {
            //         printf("ERROR: Please enter a vaid input*\n");
            //         break;
            //     }
            //     }
            // }
            // In4 = true;
            break;
        }

        // View/Update Bonus -- Incomplete
        case 8:
        {
            char period[20];
            int bonusID;
            while (In7)
            {
                system("cls");
                if (debug == true)
                {
                    displayDictionariesCount(*D);
                }
                header();
                printf("Employee Bonus\n\n");

                printf("BONUS\n\n");
                printf("[1] View\n");
                printf("[2] Update\n");
                printf("[3] Delete\n");
                printf("[0] Back\n\n");
                printf("Select Option: ");
                scanf("%d", &temp);
                fflush(stdin);

                switch (temp)
                {
                case 0:
                {
                    In7 = false;
                    break;
                }
                case 1:
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Bonus > View\n\n");

                    printf("VIEW BONUS INFORMATION\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf("\nEnter Period: ");
                    scanf("%s", &period);
                    fflush(stdin);
                    if (displayBonus(empID, D, period))
                    {
                    }
                    else
                    {
                        printf("Database Error!");
                    }

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 2:
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Bonus > Update\n\n");

                    printf("UPDATE BONUS INFORMATION\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf("\nEnter Period: ");
                    scanf("%s", &period);
                    fflush(stdin);

                    Schema_Bonus *bonusInfo = searchBonus(*D, empID, period);

                    while (In8)
                    {
                        system("cls");
                        if (debug == true)
                        {
                            displayDictionariesCount(*D);
                        }
                        header();
                        printf("Employee Bonus > View\n\n");

                        printf("UPDATE BONUS INFORMATION\n\n");
                        printf("[1] Bonus Name\n");
                        printf("[2] Amount\n");
                        printf("[3] Period\n");
                        printf("[4] Update All\n");
                        printf("[0] Back\n\n");
                        printf("Select Option: ");
                        scanf("%d", temp);
                        fflush(stdin);

                        system("cls");
                        if (debug == true)
                        {
                            displayDictionariesCount(*D);
                        }
                        header();
                        displayBonus(empID, D, period);

                        switch (temp)
                        {
                        case 0:
                            In8 = false;
                            break;
                        case 1:
                        {
                            printf("\n\nEnter new bonus name: ");
                            scanf("%s", &bonusInfo->bonusName);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 2:
                        {
                            printf("\n\nEnter new amount: ");
                            scanf("%lf", &bonusInfo->amount);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 3:
                        {
                            printf("\n\nEnter new period [mm/yy]: ");
                            scanf("%s", &bonusInfo->period);
                            fflush(stdin);

                            printf("\n*Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 4:
                        {
                            Schema_Bonus data;

                            printf("\n\nEnter new bonus name: ");
                            scanf("%s", &data.bonusName);
                            fflush(stdin);

                            printf("\n\nEnter new amount: ");
                            scanf("%lf", &data.amount);
                            fflush(stdin);

                            printf("\n\nEnter new period [mm/yy]: ");
                            scanf("%s", &data.period);
                            fflush(stdin);

                            updateBonus(D, data, bonusInfo);
                            break;
                        }
                        default:
                        {
                            printf("ERROR: Please enter a vaid input*\n");
                        }
                        }
                    }
                    In8 = true;
                    break;
                }
                case 3:
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf("Employee Bonus > Delete\n\n");

                    printf("DELETE BONUS INFORMATION\n\n");
                    printf("Enter Bonus ID: ");
                    scanf("%d", &bonusID);
                    fflush(stdin);

                    bool b = deleteBonus(D, bonusID);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                default:
                {
                    printf("ERROR: Please enter a vaid input*\n");
                    break;
                }
                }
            }
            In7 = true;
            break;
        }
        // case 9:
        // {
        //     while (In10)
        //     {
        //         system("cls");
        //         if (debug == true)
        //         {
        //             displayDictionariesCount(*D);
        //         }
        //         header();
        //         printf("Employee Salary\n\n");

        //         printf("EMPLOYEE SALARY\n\n");
        //         printf("[1] View All\n");
        //         printf("[2] View Employee\n");
        //         printf("[3] Update\n");
        //         printf("[4] Delete\n");
        //         printf("[0] Back\n\n");
        //         printf("Select Option: ");
        //         scanf("%d", &temp);
        //         fflush(stdin);
        //         break;
        //         switch (temp)
        //         {
        //         case 0:
        //             In10 = false;
        //             break;
        //         case 1:
        //             printf("Enter Period: ");
        //             scanf("%s", &period);
        //             fflush(stdin);
        //             displayAllSalary(*D, period);
        //             break;
        //         case 2:
        //             printf("Enter Employee ID: ");
        //             scanf("%d", &empID);
        //             printf("Enter Period: ");
        //             scanf("%s", &period);
        //             fflush(stdin);
        //             displayIssueSalary(*D, empID, period);
        //             break;
        //         case 3:
        //             system("cls");
        //             if (debug == true)
        //             {
        //                 displayDictionariesCount(*D);
        //             }
        //             header();
        //             printf("UPDATE SALARY INFORMATION\n\n");
        //             printf("Enter Employee ID: ");
        //             scanf("%d", &empID);
        //             printf("\nEnter Period: ");
        //             scanf("%s", &period);

        //             Schema_IssueSalary *salaryInfo = searchIssueSalary(*D, empID, period);

        //             while (In11)
        //             {
        //                 printf("UPDATE SALARY INFORMATION\n\n");
        //                 printf("[1] Bonus Name\n");
        //                 printf("[2] Amount\n");
        //                 printf("[3] Period\n");
        //                 printf("[4] Update All\n");
        //                 printf("[0] Back\n\n");
        //                 printf("Select Option: ");
        //                 scanf("%d", temp);
        //                 fflush(stdin);

        //                 switch (temp)
        //                 {
        //                     temp
        //                 }
        //             }
        //             In11 = true break;
        //         case 4:

        //             break;
        //         }
        //     }
        //     In10 = true;
        // }

        case -1:
            debugAttendance(*D);
            printf("\n*Press any key to continue...* ");
            getch();
            break;
        case -2:
            debugBonus(*D);
            printf("\n*Press any key to continue...* ");
            getch();
            break;
        case -3:
            debugJobInformation(*D);
            printf("\n*Press any key to continue...* ");
            getch();
            break;
        case -4:
            debugSalary(*D);
            printf("\n*Press any key to continue...* ");
            getch();
            break;
        case -5:
            debugUser(*D);
            printf("\n*Press any key to continue...* ");
            getch();
            break;

        default:
        {
            printf("ERROR: Please enter a vaid input*\n");
            break;
        }
        }
    }
}

#endif
