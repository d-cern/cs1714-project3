#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

#define MAX_NAME_LEN 32
#define MAX_STREET_LEN 64
#define MAX_CITY_LEN 64
#define MAX_ICD_LEN 10
#define BUFFER_LEN 1024

//enums
typedef enum State {  AK, AL, AR, AZ, CA, CO, CT, DE, FL, GA, HI, IA, ID, IL, IN, KS, KY, LA, MA, MD, ME, MI, MN, MP, MS, MT, MO, NC, ND, NE, NV, NH, NJ, NM, NY, OH, OK, OR, PA, PR, RI, SC, SD, TN, TX, UT, VI, VT, VA, WA, WV, WI, WY  } State;

typedef enum PhoneType { Cell, Landline } PhoneType;

//structs
typedef struct PHONE_INFO
{
    unsigned short areaCode;
    unsigned int num;
    PhoneType type;

} PHONE;

typedef struct ICD_INFO
{
    char* code;
    size_t codeLen;
    unsigned int date;

} ICD;

typedef struct __PARAMS
{
    unsigned int codeCount;
    char* workingDir;
    size_t dirLen;

} CmdLineParams;

CmdLineParams params;  // global

//function prototypes
int checkState(char char1, char char2, enum State* state);

char* clearBuffer(char* buffer);

void parseParams(int argc, char *argv[]);

#endif
