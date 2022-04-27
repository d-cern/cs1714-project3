#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

#define MAX_NAME_LEN 32
#define MAX_STREET_LEN 64
#define MAX_CITY_LEN 64
#define MAX_ICD_LEN 10
#define BUFFER_LEN 1024

#define TRUE 1
#define FALSE 0

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
    unsigned int boolCodeCount;
    unsigned int boolFileName;
    char *fileName;
} CmdLineParams;

//function prototypes
void parseParams(int argc, char *argv[], CmdLineParams *params);

void createNewRecord(int icdCount, int recordsNum);

void loadRecord(char *fileName, FILE *fp);

void printHelp();

char *clearBuffer(char *buffer);

int checkState(char char1, char char2, enum State *state);

#endif
