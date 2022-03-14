#ifndef INTERFACE_H
#define INTERFACE_H

#include "Tasks.h"

void showMenu();

void showMenu()
{
    int input1, input2;
    int empID;
    bool In = true, In2 = true;

    while (In)
    {
        printf("[1] Create Employee",
               "[2] View/Update Employee Attendance",
               "[3] View Employee Salary & Tax",
               "[4] View/Update Employee Profile",
               "[5] View/Update Employee Job Information",
               "[0] Exit",
               "Choice: ");
        scanf("%d", &input1);
        switch (input1)
        {
        case 1: // Create Employee
            // createEmployee();
            break;
        case 2: // View/Update Employee Attendance
            // clrscr();
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
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 0:
                    In2 = false;
                    break;
                default:
                    printf("Error! Input not recognized!");
                    break;
                }
            }
            break;
        case 3: // View Employee Salary & Tax
            printf("Enter Employee ID: ");
            scanf("%d", &empID);
            double salary = createSalary(empID); // XXX: this is for creating salary; make new function for getSalary or combine with option 5.
            break;
        case 4: // View/Update Employee Profile
            break;
        case 5: // View/Update Employee Job Information
            break;
        case 0:
            In = false;
            break;
        default:
            printf("Error! Input not recognized!");
            break;
        }
    }
}

#endif