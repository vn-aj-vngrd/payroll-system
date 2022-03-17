#ifndef SCHEMA_H
#define SCHEMA_H

#define MD_MAX 200      // medium MAX
#define SM_MAX 50       // small MAX
#define DATE 10         // mm/dd/yy
#define MONTH 5         // mm/yy
#define MOBILE_PHONE 20 // ## ### ### ####
#define HOME_PHONE 20   // ### ####

// MALE, FEMALE
typedef enum
{
    MALE,
    FEMALE
} Gender;

// EMPLOYEE, EMPLOYER
typedef enum
{
    EMPLOYEE,
    EMPLOYER
} UserType;

// NO, YES
typedef enum
{
    NO,
    YES
} Response;

typedef struct
{
    int attendanceID;
    int employeeID;
    int present;
    int absent;
    int leave;
    int overtime;
    char period[MONTH];
} Schema_Attendance;

typedef struct
{
    int bonusID;
    int employeeID;
    char bonusName[SM_MAX];
    double amount;
    char period[MONTH];
} Schema_Bonus;

typedef struct
{
    int issueID;
    int employeeID;
    double balance;
    char period[SM_MAX];
} Schema_IssueSalary;

typedef struct
{
    int employmentID;
    int employeeID;
    char jobPosition[SM_MAX];
    char jobLocation[MD_MAX];
    char jobPhone[MOBILE_PHONE];
    char startDate[DATE];
    char department[SM_MAX];
    char jobEmail[SM_MAX];
    double basicSalary;
    double pagibigDeposit;
} Schema_JobInformation;

typedef struct
{
    int userID;
    char firstName[SM_MAX];
    char lastName[SM_MAX];
    Gender gender;
    char dateOfBirth[DATE];
    Response filipinoCitizen;
    char homePhone[HOME_PHONE];
    char mobilePhone[MOBILE_PHONE];
    char emailAddress[MD_MAX];
    char address[MD_MAX];
    UserType userType;
} Schema_User;

#endif