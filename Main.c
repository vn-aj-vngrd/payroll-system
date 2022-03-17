#include <stdio.h>
#include <stdbool.h>
#include "H_Interface.h"

int main()
{
    bool truthval;
    Dictionary D = {};
    // initDictionary(&D);

    // if (pullDictionaries(&D))
    // {
    //     printf("Dictionaries pulled successfully\n");
    // }
    // else
    // {2
    //     printf("Dictionaries failed to pull\n");
    // }

    // Insert default schemas
    Schema_User defaultUser = {
        1,
        "adminfn",
        "adminln",
        MALE,
        "1/1/1",
        YES,
        "1234",
        "1234",
        "admin@gmail.com",
        "adminaddress",
        EMPLOYEE};

    Schema_Bonus defaultBonus = {
        1,
        1,
        "adminbonus",
        100,
        "03/02"};

    Schema_Attendance defaultAttendance = {
        1,
        1,
        0,
        0,
        0,
        0,
        "1/1",
    };

    Schema_IssueSalary defaultIssueSalary = {
        1,
        1,
        100,
        "03/22"};

    Schema_JobInformation defaultJobInformation = {
        1,
        1,
        "admin",
        "adminlocation",
        "1234",
        "1/1/2001",
        "admindepartment",
        "admin@gmail.com",
        1000,
        0};

    // insertAttendance(&D, defaultAttendance);
    insertUser(&D, defaultUser);
    insertBonus(&D, defaultBonus);
    insertJobInformation(&D, defaultJobInformation);
    insertIssueSalary(&D, defaultIssueSalary);
    // End of insert default

    // debugAttendance(D);
    // debugSalary(D);
    // debugUser(D);
    // debugJobInformation(D);
    // debugBonus(D);

    showMenu(&D);

    return 0;
}
