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
        "mm/dd/yy",
        true,
        "#######",
        "###########",
        "admin@gmail.com",
        "adminaddress",
        EMPLOYEE};
    D.count[4] += 1;
    Schema_JobInformation defaultJobInformation = {
        1,
        1,
        "admin",
        "adminlocation",
        "###########",
        "mm/dd/yy",
        "admindepartment",
        "admin@gmail.com",
        1000,
        0
    };
    D.count[3] += 1;
    insertUser(&D, defaultUser);
    insertJobInformation(&D, defaultJobInformation);
    
    showMenu(&D);
    
    return 0;
}