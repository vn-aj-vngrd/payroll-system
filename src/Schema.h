#ifndef SCHEMA_H
#define SCHEMA_H

#define MD_MAX 200      // medium MAX
#define SM_MAX 50       // small MAX
#define DATE 8          // mm/dd/yy
#define MOBILE_PHONE 11 // ## ### ### ####
#define HOME_PHONE 7    // ### ####

// DIY FORMAT GUIDE OF SCHEMA
//     example.
//     --> *PSEE = Pointer Schema Employee
//     --> *PSER = Pointer Schema Employer
//     --> *PSJI = Pointer Schema Job Information
//     etc.

enum Gender
{
    MALE,
    FEMALE
};

enum UserType
{
    EMPLOYEE,
    EMPLOYER
};

typedef struct node
{
    int userID;
    char firstName[SM_MAX];
    char lastName[SM_MAX];
    Gender gender;
    char dateOfBirth[DATE];
    bool filipinoCitizen;
    char homePhone[MOBILE_PHONE];
    char mobilePhone[HOME_PHONE];
    char emailAddress[MD_MAX];
    char address[MD_MAX];
    UserType userType;
    struct node *next;
} Schema_User, *PSU;

typedef struct node
{
    int employmentID;
    int employeeID;
    char jobPosition[SM_MAX];
    char jobLocation[MD_MAX];
    char jobPhone[MOBILE_PHONE];
    char startDate[DATE];
    char department[SM_MAX];
    char jobEmail[SM_MAX];
    float basicSalary;
    float pagibigDeposit;
    struct node *next;
} Schema_JobInformation, *PSJI;

typedef struct node
{
    int attendanceID;
    int employeeID;
    int present;
    int absent;
    int excused;
    int overtime;
    char period[SM_MAX];
    struct node *next;
} Schema_Attendance, *PSA;

typedef struct node
{
    int issueID;
    int employeeID;
    int bonusID;
    int balance;
    char period[SM_MAX];
    struct node *next;
} Schema_IssueSalary, *PSIS;

typedef struct node
{
    int bonusID;
    char bonusName[SM_MAX];
    int amount;
    struct node *next;
} Schema_Bonus, *PSB;

#endif