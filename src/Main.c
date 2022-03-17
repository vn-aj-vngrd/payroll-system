#include <stdio.h>
#include <stdbool.h>
#include "H_Interface.h"

int main()
{
    Dictionary D;
    initDictionary(&D);
    bool b = pullDictionaries(&D);
    if (b)
    {
        printf("Dictionaries pulled successfully\n");
    }
    else
    {
        printf("Dictionaries failed to pull\n");
    }

    Schema_User defaultUser = {
        1,
        "adminfn",
        "adminln",
        MALE,
        "1/1/1",
        true,
        "1234",
        "1234",
        "admin@gmail.com",
        "adminaddress",
        EMPLOYEE};
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
    insertUser(&D, defaultUser);
    insertJobInformation(&D, defaultJobInformation);

    showMenu(&D);

    return 0;
}
