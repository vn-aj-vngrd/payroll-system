#ifndef PERSON_H
#define PERSON_H

#define MD_MAX 200
#define SM_MAX 50
#define DATE 8

#include <stdbool.h>

typedef enum
{
    MALE,
    FEMALE
} Gender;

typedef struct
{
    int employeeID;
    char firstName[SM_MAX];
    char lastName[SM_MAX];
    Gender gender;
    char dateOfBirth[DATE];
    
} EmployeeType;

#endif