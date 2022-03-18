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
    int temp;
    int empID;
    bool In = true, In2 = true, In3 = true, In4 = true, In5 = true, In6 = true, In7 = true, In8 = true;
    Schema_JobInformation *jiPtr;

    while (In)
    {
        system("cls");
        displayDictionariesCount(*D);
        printf("\nPayroll System\n\n");
        printf("[1] Create Employee\n");
        printf("[2] Create Monthly Attendance\n");
        printf("[3] Create Monthly Bonus\n");
        printf("[4] Issue Employee Salary\n");
        printf("[5] View/Update Employee Attendance\n");
        printf("[6] View/Update/Delete Employee Profile\n");
        printf("[7] View/Update/Delete Employee Job Information\n");
        printf("[8] View/Update/Delete Bonus\n");
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
            printf("Enter Employee ID: ");
            scanf("%d", &empID);
            fflush(stdin);

            bool b = issueSalary(empID, D);
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

        // View/Update Employee Attendance -- Complete
        case 5:
        {
            while (In2)
            {
                system("cls");
                printf("EMPLOYEE ATTENDANCE\n\n");
                printf("[1] View Employee Attendance\n");
                printf("[2] View All Employee Attendance\n");
                printf("[3] Set Employee Attendance\n");
                printf("[4] Set Employee Leave\n");
                printf("[5] Set Employee Absence\n");
                printf("[6] Set Employee Overtime Hours\n");
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
                    printf("VIEW EMPLOYEE ATTENDANCE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);
                    displayUserInformation(empID, D);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 2:
                {
                    system("cls");
                    printf("VIEW ALL EMPLOYEE ATTENDANCE\n\n");
                    displayAllAttendance(*D);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 3:
                {
                    system("cls");
                    printf("SET EMPLOYEE ATTENDANCE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);
                    setPresent(empID, D);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 4:
                {
                    system("cls");
                    printf("SET EMPLOYEE LEAVE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);
                    setLeave(empID, D);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 5:
                {
                    system("cls");
                    printf("SET EMPLOYEE ABSENCE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);
                    setAbsent(empID, D);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 6:
                {
                    system("cls");
                    printf("SET EMPLOYEE OVERTIME HOURS\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);
                    setOvertime(empID, D);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                default:
                {
                    printf("Error! Input not recognized!");

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
                printf("EMPLOYEE PROFILE\n\n");
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
                    In3 = false;
                    break;
                }
                case 1:
                {
                    system("cls");
                    printf("VIEW EMPLOYEE PROFILE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);
                    displayUserInformation(empID, D);

                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 2:
                {
                    system("cls");
                    printf("UPDATE EMPLOYEE PROFILE\n\n");
                    printf("Enter Employee ID: ");
                    scanf("%d", &empID);
                    fflush(stdin);

                    Schema_User *empInfo = searchUser(*D, empID);

                    while (In6)
                    {
                        system("cls");
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
                            printf("Please enter a valid option.");
                            break;
                        }
                        }
                    }
                    In6 = true;
                    printf("\n*Press any key to continue...* ");
                    getch();
                    break;
                }
                case 3:
                {
                    system("cls");
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
                    printf("Error! Input not recognized!");
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
            //         printf("UPDATE JOB INFORMATION\n\n");
            //         printf("Enter Employee ID: ");
            //         scanf("%d", &empID);
            //         fflush(stdin);

            //         Schema_JobInformation *jobInfo = searchJobInformation(*D, empID);

            //         while (In5)
            //         {
            //             system("cls");
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
            //                 printf("Please enter a valid option.");
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
            //         printf("Error! Input not recognized!");
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
                        }
                    }
                    In8 = true;
                    break;
                }
                case 3:
                {
                    system("cls");
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
                    printf("Error! Input not recognized!");
                    break;
                }
                }
            }
            In7 = true;
            break;
        }

        default:
        {
            printf("Please enter a valid option.");
            break;
        }
        }
    }
}

#endif
