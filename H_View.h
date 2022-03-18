#ifndef VIEW_H
#define VIEW_H

#include "H_Dictionary.h"
#include "H_Model.h"
#include "H_Controller.c"
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

void showMenu(Dictionary *D)
{
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
         In10 = true,
         In11 = true;
    Model_JobInformation *jiPtr;

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
            printf(" [-5] (Debug) Attendance\n");
            printf(" [-4] (Debug) Bonus\n");
            printf(" [-3] (Debug) JobInformation\n");
            printf(" [-2] (Debug) Salary\n");
            printf(" [-1] (Debug) User\n\n");
        }

        printf(" [1] Create Employee\n");
        printf(" [2] Create Monthly Attendance\n");
        printf(" [3] Create Monthly Bonus\n");
        printf(" [4] Issue Employee Salary\n");
        printf(" [5] Employee Attendance\n");
        printf(" [6] Employee Profile\n");
        printf(" [7] Employee Job Information\n");
        printf(" [8] Employee Bonus\n");
        printf(" [9] Employee Salary\n");
        printf(" [0] Save and Exit\n");
        printf(" _____________________________________________________\n\n");
        printf(" Select Option: ");
        scanf("%d", &temp);
        fflush(stdin);

        switch (temp)
        {

        // Debug Attendance -- Complete
        case -5:
        {
            debugAttendance(*D);
            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Debug Bonus -- Complete
        case -4:
        {
            debugBonus(*D);
            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Debug Job Information -- Complete
        case -3:
        {
            debugJobInformation(*D);
            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Debug Salary -- Complete
        case -2:
        {
            debugSalary(*D);
            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Debug User -- Complete
        case -1:
        {
            debugUser(*D);
            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Push to Dictionary -- Complete
        case 0:
        {
            if (pushUserD(*D) && pushJobInformationD(*D) && pushIssueSalaryD(*D) && pushBonusD(*D) && pushAttendanceD(*D)) // pushUserD(*D) &&
            {
                printf("\n Your changes have been successfully saved.");
            }
            else
            {
                printf("\n Failed to saved changes.");
            }
            In = false;
            break;
        }

        // Create Employee -- Complete
        case 1:
        {
            system("cls");
            if (debug == true)
            {
                displayDictionariesCount(*D);
            }
            header();
            printf(" CREATE EMPLOYEE INFORMATION\n\n");
            Model_User employeeInfo = createUserInformation(*D);
            Model_JobInformation jobInfo = createJobInformation(*D, employeeInfo.userID);

            if (insertUser(D, employeeInfo) && insertJobInformation(D, jobInfo))
            {
                printf(" \n Employee information was successfully created.\n");
            }
            else
            {
                printf(" \n Failed to create employee information.\n");
            }

            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Create Attendance -- Complete
        case 2:
        {
            system("cls");
            if (debug == true)
            {
                displayDictionariesCount(*D);
            }
            header();
            printf(" CREATE MONTHLY ATTENDANCE\n\n");
            Model_Attendance sa = createAttendance(*D);
            if (sa.attendanceID == -1)
            {
                printf(" \n Employee ID not found.");
            }
            else
            {
                printf(" \n Creating Employee Attendance... \n");

                if (insertAttendance(D, sa))
                {
                    printf(" \n Employee monthly attendance was successfully created.\n");
                }
                else
                {
                    printf(" \n Employee monthly attendance already exists.\n");
                }
            }
            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Create Bonus -- Complete
        case 3:
        {
            system("cls");
            if (debug == true)
            {
                displayDictionariesCount(*D);
            }
            header();
            printf(" CREATE MONTHLY BONUS\n\n");
            Model_Bonus empBonus = createBonus(*D);
            if (insertBonus(D, empBonus))
            {
                printf("\n Employee monthly bonus was successfully created.\n");
            }
            else
            {
                printf("\n Employee monthly bonus already exists.\n");
            }

            printf("\n *Press any key to continue...* ");
            getch();
            break;
        }

        // Issue Employee Salary & Tax -- TODO (after case 7)
        case 4:
        {
            system("cls");
            if (debug == true)
            {
                displayDictionariesCount(*D);
            }
            header();
            printf(" ISSUE EMPLOYEE SALARY\n\n");
            printf(" Enter Employee ID: ");
            scanf("%d", &empID);
            printf(" Enter period (mm/yy): ");
            scanf("%s", &period);
            fflush(stdin);

            if (issueSalary(D, empID, period))
            {
                printf("\n Employee salary was successfully issued.\n");
            }
            else
            {
                printf("\n Failed to issue employee salary.\n");
            }
            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
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
                header();

                printf(" Employee Attendance >\n\n");
                printf(" EMPLOYEE ATTENDANCE\n\n");
                printf("  [1] View Employee Attendance\n");
                printf("  [2] View All Employee Attendance\n");
                printf("  [3] Update Employee Attendance\n");
                printf("  [4] Delete Employee Attendance\n");
                printf("  [5] Set Employee Attendance\n");
                printf("  [6] Set Employee Leave\n");
                printf("  [7] Set Employee Absence\n");
                printf("  [8] Set Employee Overtime Hours\n");
                printf("  [0] Back\n");
                printf(" _____________________________________________________\n\n");
                printf(" Select Option: ");
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
                    printf(" Employee Attendance > View Employee Attendance\n\n");

                    printf(" VIEW EMPLOYEE ATTENDANCE\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    displayAttendance(D, empID, period);

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
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
                    printf(" Employee Attendance > View All Employee Attendance\n\n");

                    printf(" VIEW ALL EMPLOYEE ATTENDANCE\n\n");
                    printf(" Enter period (mm/yy): ");
                    scanf("%s", &period);
                    displayAllAttendance(*D, period);

                    printf(" *Press any key to continue...* ");
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
                    printf(" Employee Attendance > Update Employee Attendance\n\n");

                    printf(" UPDATE EMPLOYEE ATTENDANCE\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);

                    Model_Attendance *empAttInfo = searchAttendance(*D, empID, period);

                    while (In9)
                    {
                        system("cls");
                        if (debug == true)
                        {
                            displayDictionariesCount(*D);
                        }
                        header();
                        printf(" Employee Attendance > Update Employee Attendance\n\n");

                        printf(" UPDATE EMPLOYEE ATTENDANCE FOR %s\n\n", period);
                        printf("  [1] No. of Present Days\n");
                        printf("  [2] No. of Absents\n");
                        printf("  [3] No. of Leaves\n");
                        printf("  [4] No. of Overtime Hours\n");
                        printf("  [5] Period (mm/yy)\n");
                        printf("  [6] Update All\n");
                        printf("  [0] Back\n");
                        printf(" _____________________________________________________\n\n");
                        printf(" Select Option: ");
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
                            printf(" \n\n Enter new number of present days: ");
                            scanf("%d", &empAttInfo->present);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 2:
                        {
                            printf(" \n\n Enter new number of absent days: ");
                            scanf("%d", &empAttInfo->absent);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 3:
                        {
                            printf(" \n\n Enter new number of leave days: ");
                            scanf("%d", &empAttInfo->leave);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 4:
                        {
                            printf(" \n\n Enter new number of overtime hours: ");
                            scanf("%d", &empAttInfo->overtime);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 5:
                        {
                            printf(" \n\n Enter new period (mm/yy): ");
                            scanf("%s", &empAttInfo->period);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 6:
                        {
                            Model_Attendance att;
                            printf(" Enter new number of present days: ");
                            scanf("%d", &att.present);
                            fflush(stdin);

                            printf(" Enter new number of absent days: ");
                            scanf("%d", &att.absent);
                            fflush(stdin);

                            printf(" Enter new number of leave days: ");
                            scanf("%d", &att.leave);
                            fflush(stdin);

                            printf(" Enter new number of overtime hours: ");
                            scanf("%d", &att.overtime);
                            fflush(stdin);

                            printf(" Enter new period (mm/yy): ");
                            scanf("%s", &att.period);
                            fflush(stdin);

                            updateAttendance(D, att, empAttInfo, period);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }

                        default:
                        {
                            printf(" ERROR: Please enter a vaid input*\n");
                            break;
                        }
                        }
                    }
                    In9 = true;
                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
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
                    printf(" Employee Attendance > Delete Employee Attendance\n\n");

                    printf(" DELETE EMPLOYEE ATTENDANCE\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    if (deleteAttendance(D, empID, period))
                    {
                        printf("\n Employee Attendance was successfully deleted.\n");
                    }
                    else
                    {
                        printf("\n Employee attendance was not found.\n");
                    }

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
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
                    printf(" Employee Attendance > Set Employee Attendance\n\n");

                    printf(" SET EMPLOYEE ATTENDANCE\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    setPresent(empID, D, period);

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
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
                    printf(" Employee Attendance > Set Employee Leave\n\n");

                    printf(" SET EMPLOYEE LEAVE\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    setLeave(empID, D, period);

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
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
                    printf(" Employee Attendance > Set Employee Absence\n\n");

                    printf(" SET EMPLOYEE ABSENCE\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    setAbsent(empID, D, period);

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
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
                    printf(" Employee Attendance > Set Employee Overtime Hours\n\n");

                    printf(" SET EMPLOYEE OVERTIME HOURS\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    setOvertime(empID, D, period);

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }
                default:
                {
                    printf(" ERROR: Please enter a vaid input*\n");

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
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
                printf(" EMPLOYEE PROFILE\n\n");

                printf("  [1] View\n");
                printf("  [2] View All\n");
                printf("  [3] Update\n");
                printf("  [4] Delete\n");
                printf("  [0] Back\n");
                printf(" _____________________________________________________\n\n");
                printf(" Select Option: ");
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
                    printf(" Employee Profile > View\n\n");

                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);
                    displayUserInformation(empID, D);

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
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
                    printf(" Employee Profile > View All\n\n");

                    printf(" VIEW ALL EMPLOYEE PROFILE\n\n");
                    displayAllUser(*D);

                    printf(" *Press any key to continue...* ");
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
                    printf(" Employee Profile > Update\n\n");

                    printf(" UPDATE EMPLOYEE PROFILE\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);

                    Model_User *empInfo = searchUser(*D, empID);

                    while (In6)
                    {
                        system("cls");
                        if (debug == true)
                        {
                            displayDictionariesCount(*D);
                        }
                        header();
                        printf(" Employee Profile > Update\n\n");

                        printf("  [1] First Name\n");
                        printf("  [2] Last Name \n");
                        printf("  [3] Gender\n");
                        printf("  [4] Date of Birth\n");
                        printf("  [5] Filipino Citizenship\n");
                        printf("  [6] Home Phone\n");
                        printf("  [7] Mobile Phone\n");
                        printf("  [8] Email\n");
                        printf("  [9] Address\n");
                        printf("  [10] User Type\n");
                        printf("  [11] Update All\n");
                        printf("  [0] Back\n");
                        printf(" _____________________________________________________\n\n");
                        printf(" Select Option: ");
                        scanf("%d", &temp);
                        fflush(stdin);

                        system("cls");
                        if (debug == true)
                        {
                            displayDictionariesCount(*D);
                        }
                        header();
                        printf(" Employee Profile > Update > Employee %d\n\n", empID);
                        displayUserInformation(empID, D);

                        switch (temp)
                        {
                        case 1:
                        {
                            printf(" _____________________________________________________\n\n");
                            printf(" Enter new first name: ");
                            scanf("%s", &empInfo->firstName);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 2:
                        {
                            printf(" _____________________________________________________\n\n");
                            printf(" Enter new last name: ");
                            scanf("%s", &empInfo->lastName);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 3:
                        {
                            printf(" _____________________________________________________\n\n");
                            printf(" Enter new gender [MALE(0) / FEMALE(1)]: ");
                            scanf("%u", &empInfo->gender);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 4:
                        {
                            printf(" _____________________________________________________\n\n");
                            printf(" Enter new date of birth: ");
                            scanf("%s", &empInfo->dateOfBirth);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 5:
                        {
                            printf(" _____________________________________________________\n\n");
                            printf(" Is a Filipino citizen? [NO(0) / YES(1)]: ");
                            scanf("%u", &empInfo->filipinoCitizen);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 6:
                        {
                            printf(" _____________________________________________________\n\n");
                            printf(" Enter new home phone: ");
                            scanf("%s", &empInfo->homePhone);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 7:
                        {
                            printf(" _____________________________________________________\n\n");
                            printf(" Enter new mobile phone: ");
                            scanf("%s", &empInfo->mobilePhone);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 8:
                        {
                            printf(" _____________________________________________________\n\n");
                            printf(" Enter new email address: ");
                            scanf("%s", &empInfo->emailAddress);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 9:
                        {
                            printf(" _____________________________________________________\n\n");
                            printf(" Enter new address: ");
                            scanf("%s", &empInfo->address);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 10:
                        {
                            printf(" _____________________________________________________\n\n");
                            printf(" Enter new user type [EMPLOYEE(0) / EMPLOYER(1)]: ");
                            scanf("%u", &empInfo->userType);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 11:
                        {
                            Model_User data;
                            printf(" _____________________________________________________\n\n");
                            printf(" Enter new first name: ");
                            scanf("%s", &data.firstName);
                            fflush(stdin);

                            printf(" Enter new last name: ");
                            scanf("%s", &data.lastName);
                            fflush(stdin);

                            printf(" Enter new gender [MALE(0) / FEMALE(1)]: ");
                            scanf("%u", &data.gender);
                            fflush(stdin);

                            printf(" Enter new date of birth: ");
                            scanf("%s", &data.dateOfBirth);
                            fflush(stdin);

                            printf(" Filipino Citizen? [NO(0) / YES(1)]: ");
                            scanf("%u", &data.filipinoCitizen);
                            fflush(stdin);

                            printf(" Enter new home phone: ");
                            scanf("%s", &data.homePhone);
                            fflush(stdin);

                            printf(" Enter new mobile phone: ");
                            scanf("%s", &data.mobilePhone);
                            fflush(stdin);

                            printf(" Enter new email address: ");
                            scanf("%s", &data.emailAddress);
                            fflush(stdin);

                            printf(" Enter new address: ");
                            scanf("%s", &data.address);
                            fflush(stdin);

                            printf(" Enter new user type [EMPLOYEE(0) / EMPLOYER(1)]: ");
                            scanf("%u", &data.userType);
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
                            printf(" ERROR: Please enter a vaid input*\n");
                            break;
                        }
                        }
                    }
                    In6 = true;
                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
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
                    printf(" Employee Profile > Delete\n\n");

                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);

                    if (deleteUser(D, empID))
                    {
                        printf("\n Employee profile was successfully deleted.\n");
                    }
                    else
                    {
                        printf("\n Employee profile was not found.\n");
                    }

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }
                default:
                {
                    printf(" ERROR: Please enter a vaid input*\n");
                    break;
                }
                }
            }
            In3 = true;
            break;
        }

        // TODO: View/Update Employee Job Information -- TODO
        case 7:
        {
            while (In4)
            {
                system("cls");
                if (debug == true)
                {
                    displayDictionariesCount(*D);
                }
                header();
                printf(" Employee Job Information\n\n");

                printf(" JOB INFORMATION\n\n");
                printf("  [1] View\n");
                printf("  [2] Update\n");
                printf("  [3] Delete\n");
                printf("  [0] Back\n");
                printf(" _____________________________________________________\n\n");
                printf(" Select Option: ");

                scanf("%d", &temp);
                fflush(stdin);

                switch (temp)
                {
                case 0:
                {
                    In4 = false;
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
                    printf(" VIEW JOB INFORMATION\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);
                    displayJobInformation(empID, D);

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
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
                    printf(" UPDATE JOB INFORMATION\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);

                    Model_JobInformation *jobInfo = searchJobInformation(*D, empID);

                    while (In5)
                    {
                        system("cls");
                        if (debug == true)
                        {
                            displayDictionariesCount(*D);
                        }
                        header();
                        printf(" UPDATE JOB INFORMATION\n\n");
                        printf("  [1] Job Position\n");
                        printf("  [2] Job Location\n");
                        printf("  [3] Job Phone\n");
                        printf("  [4] Start Date\n");
                        printf("  [5] Department\n");
                        printf("  [6] Email\n");
                        printf("  [7] Basic Salary\n");
                        printf("  [8] Pagibig Deposit\n");
                        printf("  [9] Update All\n");
                        printf("  [0] Back\n");
                        printf(" _____________________________________________________\n\n");
                        printf("  Select Option: ");
                        scanf("%d", temp);
                        fflush(stdin);

                        system("cls");
                        if (debug == true)
                        {
                            displayDictionariesCount(*D);
                        }
                        header();
                        displayJobInformation(empID, D);

                        switch (temp)
                        {
                        case 1:
                        {
                            printf(" \n\nEnter new job position: ");
                            scanf("%s", &jobInfo->jobPosition);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 2:
                        {
                            printf(" \n\nEnter new job location: ");
                            scanf("%s", &jobInfo->jobLocation);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 3:
                        {
                            printf(" \n\nEnter new job phone: ");
                            scanf("%s", &jobInfo->jobPhone);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 4:
                        {
                            printf(" \n\nEnter new start date: ");
                            scanf("%s", &jobInfo->startDate);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 5:
                        {
                            printf(" \n\nEnter new department: ");
                            scanf("%s", &jobInfo->department);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 6:
                        {
                            printf(" \n\nEnter new email: ");
                            scanf("%s", &jobInfo->jobEmail);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 7:
                        {
                            printf(" \n\nEnter new basic salary: ");
                            scanf("%lf", &jobInfo->basicSalary);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 8:
                        {
                            printf(" \n\nEnter new pagibig deposit: ");
                            scanf("%lf", &jobInfo->pagibigDeposit);
                            fflush(stdin);

                            printf(" _____________________________________________________\n\n");
                            printf(" *Press any key to continue...* ");
                            getch();
                            break;
                        }
                        case 9:
                        {
                            Model_JobInformation data;

                            printf(" \n\nEnter new job position: ");
                            scanf("%s", &data.jobPosition);
                            fflush(stdin);

                            printf(" \nEnter new job location: ");
                            scanf("%s", &data.jobLocation);
                            fflush(stdin);

                            printf(" \nEnter new job phone: ");
                            scanf("%s", &data.jobPhone);
                            fflush(stdin);

                            printf(" \nEnter new start date: ");
                            scanf("%s", &data.startDate);
                            fflush(stdin);

                            printf(" \nEnter new department: ");
                            scanf("%s", &data.department);
                            fflush(stdin);

                            printf(" \nEnter new email: ");
                            scanf("%s", &data.jobEmail);
                            fflush(stdin);

                            printf(" \nEnter new basic salary: ");
                            scanf("%lf", &data.basicSalary);
                            fflush(stdin);

                            printf(" \nEnter new pagibig deposit: ");
                            scanf("%lf", &data.pagibigDeposit);
                            fflush(stdin);

                            updateJobInformation(D, data, jobInfo);
                            break;
                        }
                        case 0:
                        {
                            In5 = false;
                            break;
                        }
                        default:
                        {
                            printf(" ERROR: Please enter a vaid input*\n");
                            break;
                        }
                        }
                    }
                    In5 = true;
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
                    printf(" DELETE JOB INFORMATION\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);
                    deleteJobInformation(D, empID);

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }
                default:
                {
                    printf(" ERROR: Please enter a vaid input*\n");
                    break;
                }
                }
            }
            In4 = true;
            break;
        }

        // View/Update Bonus -- Complete
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
                printf(" EMPLOYEE BONUS\n\n");
                printf("  [1] View\n");
                printf("  [2] Update\n");
                printf("  [3] Delete\n");
                printf("  [0] Back\n");
                printf(" _____________________________________________________\n\n");
                printf(" Select Option: ");
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
                    printf(" Employee Bonus > View\n\n");

                    printf(" VIEW BONUS INFORMATION\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);

                    displayBonus(empID, D, period);

                    printf("\n _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
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
                    printf(" Employee Bonus > Update\n\n");

                    printf(" UPDATE BONUS INFORMATION\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);

                    Model_Bonus *bonusInfo = searchBonus(*D, empID, period);
                    if (bonusInfo)
                    {
                        while (In8)
                        {
                            system("cls");

                            if (debug == true)
                            {
                                displayDictionariesCount(*D);
                            }
                            header();
                            printf(" Employee Bonus > View\n\n");

                            printf(" UPDATE BONUS INFORMATION\n\n");
                            printf("  [1] Bonus Name\n");
                            printf("  [2] Amount\n");
                            printf("  [3] Period\n");
                            printf("  [4] Update All\n");
                            printf("  [0] Back\n");
                            printf(" _____________________________________________________\n\n");
                            printf(" Select Option: ");
                            scanf("%d", &temp);
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
                                printf("\n\n Enter new bonus name: ");
                                scanf("%s", &bonusInfo->bonusName);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 2:
                            {
                                printf("\n\n Enter new amount: ");
                                scanf("%lf", &bonusInfo->amount);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 3:
                            {
                                printf("\n\n Enter new period (mm/yy): ");
                                scanf("%s", &bonusInfo->period);
                                fflush(stdin);
                                strcpy(period, bonusInfo->period);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 4:
                            {
                                Model_Bonus data;

                                printf("\n\n Enter new bonus name: ");
                                scanf("%s", &data.bonusName);
                                fflush(stdin);

                                printf(" Enter new amount: ");
                                scanf("%lf", &data.amount);
                                fflush(stdin);

                                printf(" Enter new period (mm/yy): ");
                                scanf("%s", &data.period);
                                strcpy(period, data.period);
                                fflush(stdin);

                                updateBonus(D, data, bonusInfo);
                                break;
                            }
                            default:
                            {
                                printf(" ERROR: Please enter a vaid input*\n");
                                break;
                            }
                            }
                        }
                    }
                    else
                    {
                        printf("\n Employee Bonus was not found.\n");
                        printf(" _____________________________________________________\n\n");
                        printf(" *Press any key to continue...* ");
                        getch();
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
                    printf(" Employee Bonus > Delete\n\n");

                    printf(" DELETE BONUS INFORMATION\n\n");
                    printf(" Enter Bonus ID: ");
                    scanf("%d", &bonusID);
                    fflush(stdin);

                    if (deleteBonus(D, bonusID))
                    {
                        printf("\n Employee Bonus was sucessfully deleted.\n");
                    }
                    else
                    {
                        printf("\n Employee Bonus was not found.\n");
                    }

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }
                default:
                {
                    printf("\n ERROR: Please enter a vaid input* ");
                    getch();
                    break;
                }
                }
            }
            In7 = true;
            break;
        }

        // View/Delete Salary -- To Do
        case 9:
        {
            while (In10)
            {
                system("cls");
                if (debug == true)
                {
                    displayDictionariesCount(*D);
                }
                header();
                printf(" EMPLOYEE SALARY\n\n");
                printf("  [1] View All\n");
                printf("  [2] View One\n");
                printf("  [3] Delete\n");
                printf("  [0] Back\n");
                printf(" _____________________________________________________\n\n");
                printf(" Select Option: ");
                scanf("%d", &temp);
                fflush(stdin);
                switch (temp)
                {
                case 0:
                    printf("case 0");
                    In10 = false;
                    break;
                case 1:
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Salary > View All\n\n");
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    displayAllSalary(*D, period);

                    printf(" \n _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                case 2:
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Salary > View One\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    displayIssueSalary(D, empID, period);

                    printf(" \n _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                case 3:
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Salary > Delete\n\n");
                    printf(" DELETE SALARY INFORMATION\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);

                    Model_IssueSalary *salaryInfo2 = searchIssueSalary(*D, empID, period);
                    if (salaryInfo2)
                    {
                        if (deleteIssueSalary(D, salaryInfo2->issueID))
                        {
                            printf("\n Salary was deleted successfully.");
                        }
                        else
                        {
                            printf("\n Failed to delete salary.");
                        }
                    }
                    else
                    {
                        printf("\n Salary was not found.");
                    }

                    printf(" \n _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                default:
                {
                    printf("\n ERROR: Please enter a vaid input* ");
                    getch();
                    break;
                }
                }
            }
            In10 = true;
            break;
        }

        // Default
        default:
        {
            printf("\n ERROR: Please enter a vaid input* ");
            getch();
            break;
        }
        }
    }
}

#endif
