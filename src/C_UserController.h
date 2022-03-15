#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "H_Libraries.h"
#include "H_Schema.h"
#include "H_Model.h"
#include "C_DictionaryController.h"

void insertUser(Dictionary *D, Schema_User data)
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
        printf("User Inserted Successfully\n");
    }
    else
    {
        printf("User already exists\n");
    }
}

void updateUser(Dictionary *D, Schema_User data)
{
    PSU *trav;
    int hashVal = hash(data.userID);

    for (trav = &(D->UserD[hashVal]); *trav != NULL && (*trav)->data.userID != data.userID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        printf("User ID not found\n");
    }
    else
    {
        (*trav)->data = data;
        printf("User Updated Successfully\n");
    }
}

void deleteUser(Dictionary *D, ID userID)
{
    PSU *trav, temp;
    int hashVal = hash(userID);

    for (trav = &(D->UserD[hashVal]); *trav != NULL && (*trav)->data.userID != userID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        printf("User ID not found\n");
    }
    else
    {
        temp = *trav;
        *trav = (*trav)->next;
        free(temp);
        D->count[4]++;
        printf("User Deleted Successfully\n");
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
        printf("User ID not found\n");
        return NULL;
    }
}

#endif