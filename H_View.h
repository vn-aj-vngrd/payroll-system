#ifndef VIEW_H
#define VIEW_H

#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "H_Controller.c"
#include "H_Dictionary.h"
#include "H_Model.h"

void showEmployerMenu(Dictionary *D)
{
    int temp;
    int empID;
    char period[MONTH];
    bool In = true, In2 = true, In3 = true, In4 = true, In5 = true, In6 = true,
         In7 = true, In8 = true, In9 = true, In10 = true, In11 = true;

    while (In)
    {
        system("cls");
        if (debug)
        {
            displayDictionariesCount(*D);
        }
        header();

        if (debugMenu)
        {
            printf(" DEBUG MODE\n");
            printf(" [-6] (Debug) Debug All\n");
            printf(" [-5] (Debug) Attendance\n");
            printf(" [-4] (Debug) Bonus\n");
            printf(" [-3] (Debug) JobInformation\n");
            printf(" [-2] (Debug) Salary\n");
            printf(" [-1] (Debug) User\n\n");
        }

        printf(" CREATE\n\n");
        printf(" [1] Create Employee\n");
        printf(" [2] Create Monthly Attendance\n");
        printf(" [3] Create Monthly Bonus\n");
        printf(" [4] Issue Employee Salary\n\n");

        printf(" VIEW / UPDATE / DELETE\n\n");
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

        case -6: // C-6
        {
            debugAll(*D);
            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Debug Attendance -- Complete
        case -5: // C-5
        {
            debugAttendance(*D);
            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Debug Bonus -- Complete
        case -4: // C-4
        {
            debugBonus(*D);
            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Debug Job Information -- Complete
        case -3: // C-3
        {
            debugJobInformation(*D);
            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Debug Salary -- Complete
        case -2: // C-2
        {
            debugSalary(*D);
            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Debug User -- Complete
        case -1: // C-1
        {
            debugUser(*D);
            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Push to Dictionary -- Complete
        case 0: // C0
        {
            if (pushUserD(*D) && pushJobInformationD(*D) &&
                pushIssueSalaryD(*D) && pushBonusD(*D) &&
                pushAttendanceD(*D)) // pushUserD(*D) &&
            {
                printf("\n Your changes have been successfully saved.");
            }
            else
            {
                printf("\n ERROR: Failed to saved changes.");
            }
            In = false;
            break;
        }

        // Create Employee -- Complete
        case 1: // C1
        {
            system("cls");
            if (debug == true)
            {
                displayDictionariesCount(*D);
            }
            header();
            printf(" CREATE EMPLOYEE INFORMATION\n\n");
            Model_User employeeInfo = createUserInformation(*D);
            Model_JobInformation jobInfo =
                createJobInformation(*D, employeeInfo.userID);

            if (insertUser(D, employeeInfo) &&
                insertJobInformation(D, jobInfo))
            {
                printf(" \n Employee information successfully created.\n");
            }
            else
            {
                printf(" \n ERROR: Failed to create employee information.\n");
            }

            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Create Attendance -- Complete
        case 2: // C2
        {
            system("cls");
            if (debug == true)
            {
                displayDictionariesCount(*D);
            }
            header();
            printf(" CREATE MONTHLY ATTENDANCE\n\n");

            printf(" Enter Employee ID: ");
            scanf("%d", &empID);
            printf(" Enter period (mm/yy): ");
            scanf("%s", &period);

            Model_Attendance sa = createAttendance(*D, empID, period);
            if (sa.attendanceID == -1)
            {
                printf(" \n ERROR: Employee ID #%d not found. \n", empID);
            }
            else
            {
                printf(" \n Creating Employee Attendance... \n");

                if (insertAttendance(D, sa))
                {
                    printf(" \n Employee #%d attendance for period #%s successfully created.\n", empID, period);
                }
                else
                {
                    printf(" \n ERROR: Employee #%d attendance for period #%s already exists.\n", empID, period);
                }
            }
            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Create Bonus -- Complete
        case 3: // C3
        {
            system("cls");
            if (debug == true)
            {
                displayDictionariesCount(*D);
            }
            header();
            printf(" CREATE MONTHLY BONUS\n\n");

            printf(" Employee ID: ");
            scanf("%d", &empID);
            fflush(stdin);
            printf(" Period (mm/yy): ");
            scanf("%s", &period);
            fflush(stdin);

            Model_Bonus empBonus = createBonus(*D, empID, period);
            if (empBonus.bonusID == -1)
            {
                printf(" \n ERROR: Employee ID #%d not found. \n", empID);
            }
            else
            {
                printf(" \n Creating Employee Bonus... \n");
                if (insertBonus(D, empBonus))
                {
                    printf("\n Employee #%d bonus for period %s successfully created.\n", empID, period);
                }
                else
                {
                    printf("\n ERROR: Employee #%d bonus for period %s already exists.\n", empID, period);
                }
            }

            printf(" _____________________________________________________\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Issue Employee Salary & Tax -- TODO (after case 7)
        case 4: // C4
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
                printf("\n Employee #%d salary for period %s successfully issued.\n", empID, period);
            }
            else
            {
                printf("\n ERROR: Failed to issue employee #%d salary for period #%s.\n", empID, period);
            }
            printf(
                " _____________________________________________________"
                "\n\n");
            printf(" *Press any key to continue...* ");
            getch();
            break;
        }

        // Employee Attendance -- Complete
        case 5: // C5
        {
            while (In2)
            {
                system("cls");
                if (debug == true)
                {
                    displayDictionariesCount(*D);
                }
                header();

                printf(" EMPLOYEE ATTENDANCE\n\n");
                printf("  [1] View\n");
                printf("  [2] View All\n");
                printf("  [3] Update\n");
                printf("  [4] Delete\n");
                printf("  [5] Set Attendance\n");
                printf("  [6] Set Leave\n");
                printf("  [7] Set Absence\n");
                printf("  [8] Set Overtime Hours\n");
                printf("  [0] Back\n");
                printf(" _____________________________________________________\n\n");
                printf(" Select Option: ");
                scanf("%d", &temp);
                fflush(stdin);

                switch (temp)
                {
                case 0: // C50
                {
                    In2 = false;
                    break;
                }

                case 1: // C51
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Attendance > View\n\n");

                    printf(" VIEW EMPLOYEE ATTENDANCE\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);

                    displayAttendance(D, empID, period);
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }

                case 2: // C52
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Attendance > View All\n\n");

                    printf(" VIEW ALL EMPLOYEE ATTENDANCE\n\n");
                    printf(" Enter period (mm/yy): ");
                    scanf("%s", &period);
                    displayAllAttendance(*D, period);

                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }

                case 3: // C53
                {
                    char period[20];
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Attendance > Update\n\n");

                    printf(" UPDATE EMPLOYEE ATTENDANCE\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);

                    Model_Attendance *empAttInfo = searchAttendance(*D, empID, period);
                    if (empAttInfo)
                    {
                        while (In9)
                        {
                            system("cls");
                            if (debug == true)
                            {
                                displayDictionariesCount(*D);
                            }
                            header();
                            printf(" Employee Attendance > Update\n\n");
                            printf(" UPDATE EMPLOYEE ATTENDANCE\n");
                            displayAttendance(D, empID, period);

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

                            switch (temp)
                            {
                            case 0: // C530
                            {
                                In9 = false;
                                break;
                            }
                            case 1: // C531
                            {
                                system("cls");
                                if (debug == true)
                                {
                                    displayDictionariesCount(*D);
                                }
                                header();
                                printf(" Employee Attendance > Update\n\n");
                                printf(" UPDATE EMPLOYEE ATTENDANCE\n");
                                displayAttendance(D, empID, period);

                                printf(" Enter new number of present days: ");
                                scanf("%d", &empAttInfo->present);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 2: // C532
                            {
                                system("cls");
                                if (debug == true)
                                {
                                    displayDictionariesCount(*D);
                                }
                                header();
                                printf(" Employee Attendance > Update\n\n");
                                printf(" UPDATE EMPLOYEE ATTENDANCE\n");
                                displayAttendance(D, empID, period);

                                printf(" Enter new number of absent days: ");
                                scanf("%d", &empAttInfo->absent);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 3: // C533
                            {
                                system("cls");
                                if (debug == true)
                                {
                                    displayDictionariesCount(*D);
                                }
                                header();
                                printf(" Employee Attendance > Update\n\n");
                                printf(" UPDATE EMPLOYEE ATTENDANCE\n");
                                displayAttendance(D, empID, period);

                                printf(
                                    " Enter new number of leave "
                                    "days: ");
                                scanf("%d", &empAttInfo->leave);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                                system("cls");
                                if (debug == true)
                                {
                                    displayDictionariesCount(*D);
                                }
                                header();
                                printf(" Employee Attendance > Update\n\n");
                                printf(" UPDATE EMPLOYEE ATTENDANCE\n");
                                displayAttendance(D, empID, period);

                            case 4: // C534
                            {
                                system("cls");
                                if (debug == true)
                                {
                                    displayDictionariesCount(*D);
                                }
                                header();
                                printf(" Employee Attendance > Update\n\n");
                                printf(" UPDATE EMPLOYEE ATTENDANCE\n");
                                displayAttendance(D, empID, period);

                                printf(" Enter new number of overtime hours: ");
                                scanf("%d", &empAttInfo->overtime);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                                system("cls");
                                if (debug == true)
                                {
                                    displayDictionariesCount(*D);
                                }
                                header();
                                printf(" Employee Attendance > Update\n\n");
                                printf(" UPDATE EMPLOYEE ATTENDANCE\n");
                                displayAttendance(D, empID, period);

                            case 5: // C535
                            {
                                system("cls");
                                if (debug == true)
                                {
                                    displayDictionariesCount(*D);
                                }
                                header();
                                printf(" Employee Attendance > Update\n\n");
                                printf(" UPDATE EMPLOYEE ATTENDANCE\n");
                                displayAttendance(D, empID, period);

                                printf(" Enter new period (mm/yy): ");
                                scanf("%s", &empAttInfo->period);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                                system("cls");
                                if (debug == true)
                                {
                                    displayDictionariesCount(*D);
                                }
                                header();
                                printf(" Employee Attendance > Update\n\n");
                                printf(" UPDATE EMPLOYEE ATTENDANCE\n");
                                displayAttendance(D, empID, period);

                            case 6: // C53
                            {
                                system("cls");
                                if (debug == true)
                                {
                                    displayDictionariesCount(*D);
                                }
                                header();
                                printf(" Employee Attendance > Update \n\n");
                                printf(" UPDATE EMPLOYEE ATTENDANCE\n");
                                displayAttendance(D, empID, period);

                                printf(" Enter new number of present days: ");
                                scanf("%d", &empAttInfo->present);
                                fflush(stdin);

                                printf(" Enter new number of absent days: ");
                                scanf("%d", &empAttInfo->absent);
                                fflush(stdin);

                                printf(" Enter new number of leave days: ");
                                scanf("%d", &empAttInfo->leave);
                                fflush(stdin);

                                printf(" Enter new number of overtime hours: ");
                                scanf("%d", &empAttInfo->overtime);
                                fflush(stdin);

                                printf(" Enter new period (mm/yy): ");
                                scanf("%s", &empAttInfo->period);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }

                            default:
                            {
                                invalidInput();
                                break;
                            }
                                printf(" *Press any key to continue...* ");
                                getch();
                            }
                        }
                    }
                    else
                    {
                        printf("\n ERROR: Employee #%d attendance for period %s does not exist.\n", empID, period);
                        In9 = false;
                        printf(" _____________________________________________________\n\n");
                        printf(" *Press any key to continue...* ");
                        getch();
                    }

                    In9 = true;
                    break;
                }

                case 4: // C54
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Attendance > Delete\n\n");

                    printf(" DELETE EMPLOYEE ATTENDANCE\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    if (deleteAttendance(D, empID, period))
                    {
                        printf("\n Employee #%d attendance for period %s successfully deleted.\n", empID, period);
                    }
                    else
                    {
                        printf("\n ERROR: Employee #%d attendance not found for period %s.\n", empID, period);
                    }
                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }

                case 5: // C55
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Attendance > Set Attendance\n\n");

                    printf(" SET EMPLOYEE ATTENDANCE\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    setPresent(empID, D, period);

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }

                case 6: // C56
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Attendance > Set Leave\n\n");

                    printf(" SET EMPLOYEE LEAVE\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    setLeave(empID, D, period);

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }

                case 7: // C57
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Attendance > Set Absence\n\n");

                    printf(" SET EMPLOYEE ABSENCE\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    setAbsent(empID, D, period);

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }

                case 8: // C58
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Attendance > Set Overtime Hours\n\n");

                    printf(" SET EMPLOYEE OVERTIME HOURS\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    setOvertime(empID, D, period);

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }

                default: // C5D
                {
                    invalidInput();
                    break;
                }
                }
            }
            In2 = true;
            break;
        }

        // View/Update Employee Profile -- Complete
        case 6: // C6
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
                case 0: // C60
                {
                    In3 = false;
                    break;
                }
                case 1: // C61
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Profile > View\n\n");

                    printf(" VIEW EMPLOYEE PROFILE\n\n");

                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);

                    displayUserInformation(empID, D);

                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }
                case 2: // C62
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Profile > View All\n\n");

                    printf(" VIEW ALL EMPLOYEE PROFILE\n");

                    displayAllUser(*D);

                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }
                case 3: // C63
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
                    if (empInfo)
                    {
                        while (In6)
                        {
                            system("cls");
                            if (debug == true)
                            {
                                displayDictionariesCount(*D);
                            }
                            header();
                            printf(" Employee Profile > Update\n\n");

                            printf(" UPDATE EMPLOYEE PROFILE\n");
                            displayUserInformation(empID, D);

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
                            printf(" Employee Profile > Update\n\n", empID);

                            printf(" UPDATE EMPLOYEE PROFILE\n");
                            displayUserInformation(empID, D);

                            switch (temp)
                            {
                            case 0: // C630
                            {
                                In6 = false;
                                break;
                            }
                            case 1: // C631
                            {
                                printf(" Enter new first name: ");
                                scanf("%s", &empInfo->firstName);
                                fflush(stdin);
                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 2: // C632
                            {
                                printf(" Enter new last name: ");
                                scanf("%s", &empInfo->lastName);
                                fflush(stdin);
                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 3: // C633
                            {
                                printf(
                                    " Enter new gender [MALE(0) / "
                                    "FEMALE(1)]: ");
                                scanf("%u", &empInfo->gender);
                                fflush(stdin);
                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 4: // C634
                            {
                                printf(" Enter new date of birth: ");
                                scanf("%s", &empInfo->dateOfBirth);
                                fflush(stdin);
                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 5: // C635
                            {
                                printf(" Is a Filipino citizen? [NO(0) / YES(1)]: ");
                                scanf("%u", &empInfo->filipinoCitizen);
                                fflush(stdin);
                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 6: // C636
                            {
                                printf(" Enter new home phone: ");
                                scanf("%s", &empInfo->homePhone);
                                fflush(stdin);
                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 7: // C637
                            {
                                printf(" Enter new mobile phone: ");
                                scanf("%s", &empInfo->mobilePhone);
                                fflush(stdin);
                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 8: // C638
                            {
                                printf(" Enter new email address: ");
                                scanf("%s", &empInfo->emailAddress);
                                fflush(stdin);
                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 9: // C639
                            {
                                printf(" Enter new address: ");
                                scanf("%s", &empInfo->address);
                                fflush(stdin);
                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 10: // C6310
                            {
                                printf(" Enter new user type [EMPLOYEE(0) / EMPLOYER(1)]: ");
                                scanf("%u", &empInfo->userType);
                                fflush(stdin);
                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 11: // C6311
                            {
                                printf(" Enter new first name: ");
                                scanf("%s", &empInfo->firstName);
                                fflush(stdin);

                                printf(" Enter new last name: ");
                                scanf("%s", &empInfo->lastName);
                                fflush(stdin);

                                printf(" Enter new gender [MALE(0) / FEMALE(1)]: ");
                                scanf("%u", &empInfo->gender);
                                fflush(stdin);

                                printf(" Enter new date of birth: ");
                                scanf("%s", &empInfo->dateOfBirth);
                                fflush(stdin);

                                printf(" Filipino Citizen? [NO(0) / YES(1)]: ");
                                scanf("%u", &empInfo->filipinoCitizen);
                                fflush(stdin);

                                printf(" Enter new home phone: ");
                                scanf("%s", &empInfo->homePhone);
                                fflush(stdin);

                                printf(" Enter new mobile phone: ");
                                scanf("%s", &empInfo->mobilePhone);
                                fflush(stdin);

                                printf(" Enter new email address: ");
                                scanf("%s", &empInfo->emailAddress);
                                fflush(stdin);

                                printf(" Enter new address: ");
                                scanf("%s", &empInfo->address);
                                fflush(stdin);

                                printf(" Enter new user type [EMPLOYEE(0) / EMPLOYER(1)]: ");
                                scanf("%u", &empInfo->userType);
                                fflush(stdin);
                                break;
                            }
                            default: // C63D
                            {
                                invalidInput();
                                break;
                            }
                            }
                        }
                    }
                    else
                    {
                        printf("\n ERROR: Employee #%d profile not found.\n", empID);
                        printf(" _____________________________________________________\n\n");
                        printf(" *Press any key to continue...* ");
                        getch();
                        In6 = false;
                    }

                    In6 = true;
                    break;
                }
                case 4: // C64
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Profile > Delete\n\n");
                    printf(" DELETE EMPLOYEE PROFILE\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);

                    if (deleteUser(D, empID))
                    {
                        printf("\n Employee profile successfully deleted.\n");
                    }
                    else
                    {
                        printf("\n Employee profile not found.\n");
                    }

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }
                default: // C6D
                {
                    invalidInput();
                    break;
                }
                }
            }
            In3 = true;
            break;
        }

        // View/Update Employee Job Information -- Complete
        case 7: // C7
        {
            while (In4)
            {
                system("cls");
                if (debug == true)
                {
                    displayDictionariesCount(*D);
                }
                header();

                printf(" JOB INFORMATION\n\n");
                printf("  [1] View All\n");
                printf("  [2] View One\n");
                printf("  [3] Update\n");
                printf("  [4] Delete\n");
                printf("  [0] Back\n");
                printf(" _____________________________________________________\n\n");
                printf(" Select Option: ");

                scanf("%d", &temp);
                fflush(stdin);

                switch (temp)
                {
                case 0: // C70
                {
                    In4 = false;
                    break;
                }
                case 1: // C71
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Job Information > View All\n\n");

                    printf(" VIEW JOB INFORMATION\n\n");
                    fflush(stdin);

                    displayAllJobInformation(*D);

                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }
                case 2: // C72
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Job Information > View One\n\n");

                    printf(" VIEW JOB INFORMATION\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);

                    displayJobInformation(empID, D);

                    printf("\n *Press any key to continue...* ");
                    getch();
                    break;
                }
                case 3: // C73
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Job Information > Update\n\n");

                    printf(" UPDATE JOB INFORMATION\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);

                    Model_JobInformation *jobInfo = searchJobInformation(*D, empID);
                    if (jobInfo)
                    {
                        while (In5)
                        {
                            system("cls");
                            if (debug == true)
                            {
                                displayDictionariesCount(*D);
                            }
                            header();
                            printf(" Job Information > Update\n\n");
                            printf(" UPDATE JOB INFORMATION\n");
                            displayJobInformation(empID, D);
                            printf("\n");
                            printf("  [1] Job Position\n");
                            printf("  [2] Job Location\n");
                            printf("  [3] Job Phone\n");
                            printf("  [4] Email\n");
                            printf("  [5] Start Date\n");
                            printf("  [6] Department\n");
                            printf("  [7] Basic Salary\n");
                            printf("  [8] Pagibig Deposit\n");
                            printf("  [9] Update All\n");
                            printf("  [0] Back\n");
                            printf(" _____________________________________________________\n\n");
                            printf("  Select Option: ");
                            scanf("%d", &temp);
                            fflush(stdin);

                            system("cls");
                            if (debug == true)
                            {
                                displayDictionariesCount(*D);
                            }
                            header();
                            printf(" Job Information > Update > Job Position\n\n");
                            printf(" UPDATE JOB INFORMATION\n");
                            displayJobInformation(empID, D);
                            switch (temp)
                            {
                            case 0: // C730
                            {
                                In5 = false;
                                break;
                            }
                            case 1: // C731
                            {
                                printf(" Enter new job position: ");
                                scanf("%s", &jobInfo->jobPosition);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 2: // C732
                            {
                                printf(" Enter new job location: ");
                                scanf("%s", &jobInfo->jobLocation);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 3: // C733
                            {
                                printf(" Enter new job phone: ");
                                scanf("%s", &jobInfo->jobPhone);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 4: // C734
                            {
                                printf(" Enter new email: ");
                                scanf("%s", &jobInfo->jobEmail);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 5: // C735
                            {
                                printf(" Enter new start date: ");
                                scanf("%s", &jobInfo->startDate);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 6: // C736
                            {
                                printf(" Enter new department: ");
                                scanf("%s", &jobInfo->department);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 7: // C737
                            {
                                printf(" Enter new basic salary: ");
                                scanf("%lf", &jobInfo->basicSalary);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 8: // C738
                            {
                                printf(" Enter new pagibig deposit: ");
                                scanf("%lf", &jobInfo->pagibigDeposit);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 9: // C739
                            {
                                printf(" Enter new job position: ");
                                scanf("%s", &jobInfo->jobPosition);
                                fflush(stdin);

                                printf(" Enter new job location: ");
                                scanf("%s", &jobInfo->jobLocation);
                                fflush(stdin);

                                printf(" Enter new job phone: ");
                                scanf("%s", &jobInfo->jobPhone);
                                fflush(stdin);

                                printf(" Enter new email: ");
                                scanf("%s", &jobInfo->jobEmail);
                                fflush(stdin);

                                printf(" Enter new start date: ");
                                scanf("%s", &jobInfo->startDate);
                                fflush(stdin);

                                printf(" Enter new department: ");
                                scanf("%s", &jobInfo->department);
                                fflush(stdin);

                                printf(" Enter new basic salary: ");
                                scanf("%lf", &jobInfo->basicSalary);
                                fflush(stdin);

                                printf(" Enter new pagibig deposit: ");
                                scanf("%lf", &jobInfo->pagibigDeposit);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            default: // C73D
                            {
                                invalidInput();
                                break;
                            }
                            }
                        }
                    }
                    else
                    {
                        printf("\n ERROR: Employee #%d job information does not exist.\n", empID);
                        printf(" _____________________________________________________\n\n");
                        printf(" *Press any key to continue...* ");
                        getch();
                        In5 = false;
                    }
                    In5 = true;
                    break;
                }
                case 4: // C74
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Job Information > Delete\n\n");
                    printf(" DELETE JOB INFORMATION\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);

                    if (deleteJobInformation(D, empID))
                    {
                        printf("\n Employee job information sucessfully deleted.\n");
                    }
                    else
                    {
                        printf("\n ERROR: Employee #%d job information does not exist.\n", empID);
                    }

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }
                default: // C7D
                {
                    invalidInput();
                    break;
                }
                }
            }
            In4 = true;
            break;
        }

        // View/Update Bonus -- Complete
        case 8: // C8
        {
            char period[20];
            int bonusID;
            int employeeID;
            while (In7)
            {
                system("cls");
                if (debug == true)
                {
                    displayDictionariesCount(*D);
                }
                header();
                printf(" EMPLOYEE BONUS\n\n");
                printf("  [1] View All\n");
                printf("  [2] View One\n");
                printf("  [3] Update\n");
                printf("  [4] Delete\n");
                printf("  [0] Back\n");
                printf(" _____________________________________________________\n\n");
                printf(" Select Option: ");
                scanf("%d", &temp);
                fflush(stdin);

                switch (temp)
                {
                case 0: // C80
                {
                    In7 = false;
                    break;
                }

                case 1: // C81
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Bonus > View All\n\n");
                    printf(" VIEW ALL BONUS INFORMATION\n\n");
                    printf(" Enter period (mm/yy): ");

                    scanf("%s", &period);
                    displayAllBonus(*D, period);

                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }
                case 2: // C82
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

                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }
                case 3: // C83
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

                    Model_Bonus *bonusInfo =
                        searchBonus(*D, empID, period);
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
                            printf(" Employee Bonus > Update\n\n");

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
                            case 0: // C820
                                In8 = false;
                                break;
                            case 1: // C821
                            {
                                printf(" Enter new bonus name: ");
                                scanf("%s", &bonusInfo->bonusName);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 2: // C822
                            {
                                printf(" Enter new amount: ");
                                scanf("%lf", &bonusInfo->amount);
                                fflush(stdin);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 3: // C823
                            {
                                printf(" Enter new period (mm/yy): ");
                                scanf("%s", &bonusInfo->period);
                                fflush(stdin);
                                strcpy(period, bonusInfo->period);

                                printf(" _____________________________________________________\n\n");
                                printf(" *Press any key to continue...* ");
                                getch();
                                break;
                            }
                            case 4: // C824
                            {
                                printf(" Enter new bonus name: ");
                                scanf("%s", &bonusInfo->bonusName);
                                fflush(stdin);

                                printf(" Enter new amount: ");
                                scanf("%lf", &bonusInfo->amount);
                                fflush(stdin);

                                printf(" Enter new period (mm/yy): ");
                                scanf("%s", &bonusInfo->period);
                                strcpy(period, bonusInfo->period);
                                fflush(stdin);
                                break;
                            }
                            default: // C82D
                            {
                                invalidInput();
                                break;
                            }
                            }
                        }
                    }
                    else
                    {
                        printf("\n ERROR: Employee #%d bonus not found for period %s.\n", empID, period);
                        printf(" _____________________________________________________\n\n");
                        printf(" *Press any key to continue...* ");
                        getch();
                        In8 = false;
                    }
                    In8 = true;
                    break;
                }
                case 4: // C84
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Bonus > Delete\n\n");

                    printf(" DELETE BONUS INFORMATION\n\n");

                    printf(" Enter Employee ID: ");
                    scanf("%d", &employeeID);
                    fflush(stdin);

                    printf(" Enter period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);

                    if (deleteBonus(D, employeeID, period))
                    {
                        printf("\n Employee #%d bonus for period %s sucessfully deleted.\n", employeeID, period);
                    }
                    else
                    {
                        printf("\n ERROR: Employee #%d bonus not found for period $s.\n", employeeID, period);
                    }

                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }
                default: // C8D
                {
                    invalidInput();
                    break;
                }
                }
            }
            In7 = true;
            break;
        }

        // View/Delete Salary -- TODO
        case 9: // C9
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
                case 0: // C90
                {
                    In10 = false;
                    break;
                }
                case 1: // C91
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Salary > View All\n\n");
                    printf(" VIEW ALL EMPLOYEE SALARY\n\n");
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    displayAllSalary(*D, period);

                    printf("\n *Press any key to continue...* ");
                    getch();
                    break;
                }
                case 2: // C92
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Salary > View One\n\n");
                    printf(" VIEW ONE EMPLOYEE SALARY\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    fflush(stdin);
                    displayIssueSalary(D, empID, period);

                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }
                case 3: // C93
                {
                    system("cls");
                    if (debug == true)
                    {
                        displayDictionariesCount(*D);
                    }
                    header();
                    printf(" Employee Salary > Delete\n\n");
                    printf(" DELETE EMPLOYEE SALARY\n\n");
                    printf(" Enter Employee ID: ");
                    scanf("%d", &empID);
                    printf(" Enter Period (mm/yy): ");
                    scanf("%s", &period);
                    if (deleteIssueSalary(D, empID, period))
                    {
                        printf("\n Employee #%d salary for period %s deleted successfully.", empID, period);
                    }
                    else
                    {
                        printf("\n ERROR: Employee #%d salary not found for period %s.\n", empID, period);
                    }

                    printf(" \n _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                    break;
                }
                default: // C9D
                {
                    invalidInput();
                    break;
                }
                }
            }
            In10 = true;
            break;
        }

        default: // CD
        {
            invalidInput();
            break;
        }
        }
    }
}

void showEmployeeSalary(Dictionary *D)
{
    int run = 1;
    int empID;
    char period[20];

    // if (debug)
    // {
    //     displayDictionariesCount(*D);
    // }

    while (run)
    {
        system("cls");
        header();
        printf(" VIEW EMPLOYEE SALARY\n\n");
        printf(" Enter employee ID: ");
        scanf("%d", &empID);
        fflush(stdin);

        printf(" Enter period (mm/yy): ");
        scanf("%s", &period);
        fflush(stdin);

        displayIssueSalary(D, empID, period);

        printf(" [1] Continue\n");
        printf(" [0] Exit\n");
        printf(" _____________________________________________________\n");
        printf("\n Select Option: ");
        scanf("%d", &run);
        fflush(stdin);
    }
}

#endif
