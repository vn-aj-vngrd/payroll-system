#include <stdio.h>
#include <stdbool.h>
#include "H_Interface.h"

int main()
{
    if(login)
    {
        login();
    }
    else
    {
        return 0;
    }

    dPtr D;
    initDictionary(&D);

    if (pullDictionaries(D))
    {
        printf("Dictionaries pulled successfully\n");
    }
    else
    {
        printf("Dictionaries failed to pull\n");
    }

    // Insert default schemas
    Schema_User defaultUser = {
        1,
        "employeefn",
        "employeeln",
        MALE,
        "1/1/1",
        YES,
        "1234",
        "1234",
        "employee@gmail.com",
        "employeeaddress",
        EMPLOYEE};

    Schema_Bonus defaultBonus = {
        1,
        1,
        "employeebonus",
        100,
        "03/02"};

    Schema_Attendance defaultAttendance = {
        1,
        1,
        0,
        0,
        0,
        0,
        "03/22",};

    Schema_IssueSalary defaultIssueSalary = {
        1,
        1,
        100,
        "03/22"};

    Schema_JobInformation defaultJobInformation = {
        1,
        1,
        "employee",
        "employeelocation",
        "1234",
        "1/1/2001",
        "employeedepartment",
        "employee@gmail.com",
        1000,
        0};

    insertUser(D, defaultUser);
    insertAttendance(D, defaultAttendance);
    insertBonus(D, defaultBonus);
    insertJobInformation(D, defaultJobInformation);
    insertIssueSalary(D, defaultIssueSalary);
    // End of insert default

    showMenu(D);

    return 0;
}
