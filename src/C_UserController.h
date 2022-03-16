#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "H_Libraries.h"
#include "H_Schema.h"
#include "H_Model.h"
#include "C_DictionaryController.h"

Schema_User createUserInformation(Dictionary D)
{
    Schema_User emp;

    printf("Create Employee Information");

    char dType[10] = "User";
    emp.userID = getNewID(dType, D);
    emp.userType = EMPLOYER;

    printf("\n\tFirst Name: ");
    scanf("%s", &emp.firstName);
    fflush(stdin);

    printf("\n\tLast Name: ");
    scanf("%s", &emp.lastName);
    fflush(stdin);

    printf("\n\tGender (MALE/FEMALE): ");
    scanf("%d", &emp.gender);
    fflush(stdin);

    printf("\n\tDate of Birth (mm/dd/yy): ");
    scanf("%s", &emp.dateOfBirth);
    fflush(stdin);

    printf("\n\tFilipino Citizen: ");
    scanf("%s", &emp.filipinoCitizen);
    fflush(stdin);

    printf("\n\tHome Phone: ");
    scanf("%s", &emp.homePhone);
    fflush(stdin);

    printf("\n\tMobile Phone: ");
    scanf("%s", &emp.mobilePhone);
    fflush(stdin);

    printf("\nEmail Address: ");
    scanf("%s", &emp.emailAddress);
    fflush(stdin);

    printf("\n\tAddress: ");
    scanf("%s", &emp.address);
    fflush(stdin);

    return emp;
}

bool insertUser(Dictionary *D, Schema_User data)
{
    PSU *trav;
    int hashVal = hash(data.userID);

    for (trav = &(D->UserD[hashVal]); strcmp(data.emailAddress, (*trav)->data.emailAddress) != 0 && *trav != NULL; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        trav = (PSU *)malloc(sizeof(Schema_User));
        if (*trav != NULL)
        {
            (*trav)->data = data;
            (*trav)->next = NULL;
        }
        D->count[4]++;
        return true;
    }
    else
    {
        return false;
    }
}

bool updateUser(Dictionary *D, Schema_User data, Schema_User *pointer)
{
    if (data.userID != pointer->userID)
    {
        return false;
    }
    else
    {
        *pointer = data;
        return true;
    }
}

bool deleteUser(Dictionary *D, ID userID)
{
    PSU *trav, temp;
    int hashVal = hash(userID);

    for (trav = &(D->UserD[hashVal]); *trav != NULL && (*trav)->data.userID != userID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        return false;
    }
    else
    {
        temp = *trav;
        *trav = (*trav)->next;
        free(temp);
        D->count[4]++;
        return true;
    }
}

Schema_User *searchUser(Dictionary D, ID userID)
{
    PSU trav, temp;
    int hashVal = hash(userID);

    for (trav = D.UserD[hashVal]; trav != NULL && trav->data.userID != userID; trav = trav->next)
    {
    }

    if (trav != NULL)
    {
        // Schema_User *data = (Schema_User *)malloc(sizeof(Schema_User));
        // *data = trav->data;
        return &trav->data;
    }
    else
    {
        return NULL;
    }
}

void displayUserInformation(int employeeID, Dictionary *D)
{
    Schema_User *emp = searchUser(*D, employeeID);

    printf("|  Employee ID:      \t%d  |", emp->userID);
    printf("|  First Name:       \t%d  |", emp->firstName);
    printf("|  Last Name:        \t%s  |", emp->lastName);
    printf("|  Gender:           \t%s  |", emp->gender);
    printf("|  Date of Birth     \t%s  |", emp->dateOfBirth);
    printf("|  Filipino:         \t%s  |", emp->filipinoCitizen);
    printf("|  Home Phone:       \t%s  |", emp->homePhone);
    printf("|  Mobile Phone:     \t%d  |", emp->mobilePhone);
    printf("|  Email:            \t%d  |", emp->emailAddress);
    printf("|  Address           \t%s  |", emp->address);
}

#endif