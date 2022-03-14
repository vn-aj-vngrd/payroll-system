#ifndef INTERFACE_H
#define INTERFACE_H

#include "Tasks.h"

void showMenu()
{
    int input, attInput;
    int empID;
    bool In = true, In2 = true;

    while (In)
    {
        printf("[1] Create Employee",
               "[2] Update Employee Attendance",
               "[3] Check Employee Salary & Tax",
               "[4] Update Employee Record",
               "[0] Exit",
               "Input: ");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            createEmployee();
            break;
        case 2:
            clrscr();
            while(In2)
            {
                printf("[1] Check Employee Attendance",
                       "[2] Set Employee Leave",
                       "[3] Set Employee Absence",
                       "[4] Set Employee Overtime Hours",
                       "[0] Exit"
                       "Input: ");
                scanf("%d",&attInput);
                switch(attInput)
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
        case 3:
            printf("Enter Employee ID: ");
            scanf("%d", empID);
            createSalary(empID);
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