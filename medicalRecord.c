#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "medicalRecord.h"

void parseParams(int argc, char *argv[], CmdLineParams *params)
{
    /* 
        number of icd codes:    -c
        file name:              -r
        help                    -h
        *-c and -r are mutually exclusive*
    */
       
    int i;
    
    for (i = 1; i < argc; i++)
    {

        char parser[20];
        strcpy(parser, argv[i]);

        if (parser[0] == '-') //parameter signifier
        {
            switch (parser[1])
            {
                case 'h':
                    printHelp();
                    break;
                case 'c':
                    params->boolCodeCount = TRUE;
                    params->codeCount = atoi(argv[i + 1]);
                    if (params->codeCount < 1)
                    {
                        printf("ERROR: -c value must be greater than 0\n");
                        exit(1);
                    }
                    break;
                case 'r':
                    params->boolFileName = TRUE;
                    params->fileName = (char*)malloc(sizeof(char) * strlen(argv[i + 1]));
                    strcpy(params->fileName, argv[i + 1]); //stack dump - solved
                    break;
                default:
                    params->boolFileName = FALSE;
                    params->boolCodeCount = FALSE;
                    break;
            }
        }
    }

}

void createNewRecord(int icdCount, int recordsNum)
{
    FILE *fp = NULL;
    char buffer[BUFFER_LEN];
    char fileName[BUFFER_LEN];
    char userSelect[1];
    int i;

    char *firstName = NULL;
    char *lastName = NULL;

    unsigned int streetNum;
    char *streetName = NULL;
    char *city = NULL;
    State state;
    char strState[2];
    int validState = 0;
    unsigned int zipCode, zipPlusFour;

    PHONE *phone = NULL;
    ICD *icdList = NULL;

    // first name
    do
    {
        printf("Enter first name: ");

        scanf("%s", buffer);
        if (strlen(buffer) == 0)
        {
            printf("ERROR: must enter a name\n");
        }
        else if (strlen(buffer) > MAX_NAME_LEN)
        {
            printf("ERROR: name must not exceed %d characters\n", MAX_NAME_LEN);
        }
    } while (strlen(buffer) == 0 || strlen(buffer) > MAX_NAME_LEN);

    firstName = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(firstName, buffer);

    // clear buffer
    strcpy(buffer, clearBuffer(buffer));

    // last name
    do
    {
        printf("Enter last name: ");

        scanf("%s", buffer);
        if (strlen(buffer) == 0)
        {
            printf("ERROR: must enter a name\n");
        }
        else if (strlen(buffer) > MAX_NAME_LEN)
        {
            printf("ERROR: name must not exceed %d characters\n", MAX_NAME_LEN);
        }
    } while (strlen(buffer) == 0 || strlen(buffer) > MAX_NAME_LEN);

    lastName = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(lastName, buffer);

    // clear buffer
    strcpy(buffer, clearBuffer(buffer));

    // street address
    do
    {
        printf("Enter street address: ");
        scanf("%u %[^\n]", &streetNum, buffer);
        if (streetNum < 1 || streetNum > 999999)
        {
            printf("ERROR: street number must be between 1 and 999999\n");
        }
        if (strlen(buffer) == 0)
        {
            printf("ERROR: must enter street name");
        }
        else if (strlen(buffer) > MAX_STREET_LEN)
        {
            printf("ERROR: street name must not exceed %d characters\n", MAX_STREET_LEN);
        }
    } while (streetNum < 1 || streetNum > 999999 || strlen(buffer) == 0 || strlen(buffer) > MAX_NAME_LEN);

    streetName = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(streetName, buffer);

    // clear buffer
    strcpy(buffer, clearBuffer(buffer));

    // city
    do
    {
        printf("Enter city: ");
        fgetc(stdin);
        scanf("%[^\n]", buffer);
        if (strlen(buffer) == 0)
        {
            printf("ERROR: must enter a city\n");
        }
        else if (strlen(buffer) > MAX_CITY_LEN)
        {
            printf("ERROR: name must not exceed %d characters\n", MAX_CITY_LEN);
        }
    } while (strlen(buffer) == 0 || strlen(buffer) > MAX_CITY_LEN);

    city = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(city, buffer);

    // state
    i = 0;
    do
    {
        // clear buffer
        strcpy(buffer, clearBuffer(buffer));

        if (i > 0 && validState == 0)
        {
            printf("Invalid state\n");
        }
        printf("Enter state: ");
        scanf("%s", buffer);

        if (buffer == 0)
        {
            printf("ERROR: must enter state");
        }
        else if (strlen(buffer) > 2)
        {
            printf("ERROR: state must not exceed 2 characters");
        }
        else
        {
            validState = checkState(buffer[0], buffer[1], &state);
        }

    } while (validState == 0);
    strcpy(strState, buffer);

    // zip code
    i = 0;
    do
    {
        // clear buffer
        strcpy(buffer, clearBuffer(buffer));

        if (i > 0)
        {
            printf("Invalid ZIP code");
        }

        printf("Enter ZIP code in format \"XXXXX-XXXX\": ");
        scanf("%u-%u", &zipCode, &zipPlusFour);
        i++;

    } while (zipCode < 1000 || zipCode > 99950 || zipPlusFour < 1000 || zipPlusFour > 9999);

    // phone number
    phone = (PHONE *)malloc(sizeof(PHONE));
    do
    {
        printf("Enter phone number in format XXX-XXXXXXX: ");
        scanf("%hu-%u", &phone->areaCode, &phone->num);
    } while (phone->areaCode < 200 || phone->areaCode > 999 || phone->num < 2010000 || phone->num > 9999999);

    // phone type
    i = 0;
    do
    {
        if (i > 0)
        {
            printf("Invalid input");
        }

        printf("Enter 0 for \"Cell\" or 1 for \"Landline\": ");
        scanf("%u", &phone->type);
        i == 0 ? i++ : i; //increment 'i' if 'i == 0'

    } while (phone->type != 0 && phone->type != 1);

    // icd codes
    icdList = (ICD *)malloc(sizeof(ICD) * icdCount);

    for (i = 0; i < icdCount; i++)
    {
        printf("Enter ICD code #%d: ", i + 1);

        do
        {
            scanf("%s", buffer);

            printf("Enter date (YYYYMMDD): ");
            scanf("%u", &icdList[i].date);
            if (strlen(buffer) == 0)
            {
                printf("ERROR: must enter an ICD code\n");
            }
            else if (strlen(buffer) > MAX_ICD_LEN)
            {
                printf("ERROR: ICD code must not exceed %d characters\n", MAX_ICD_LEN);
            }
        } while (strlen(buffer) == 0 || strlen(buffer) > MAX_ICD_LEN);

        icdList[i].codeLen = strlen(buffer);
        icdList[i].code = (char *)malloc(sizeof(char) * icdList[i].codeLen);
        strcpy(icdList[i].code, buffer);
    }

    // clear buffer
    strcpy(buffer, clearBuffer(buffer));

    // print/confirm data
    // name
    printf("\nName: %s, %s\n", lastName, firstName);

    // street add
    printf("\nAddress:\n");
    printf("%u %s,\n", streetNum, streetName);
    printf("%s, ", city);
    printf("%s, ", strState);
    printf("%u-%u\n", zipCode, zipPlusFour);

    // phone number
    printf("\nPhone number: (%hu)-%u\n", phone->areaCode, phone->num);
    // phone type
    printf("Phone type: ");
    if (phone->type == Cell)
    {
        printf("Cell\n");
    }
    else
    {
        printf("Landline\n");
    }

    // icd
    printf("\nICD codes and dates:\n");
    if (icdCount != 0)
    {
        for (i = 0; i < 4; i++)
        {
            printf("%.*s | %u\n", 10, icdList[i].code, icdList[i].date);
        }
    }

    printf("\n test 123\n");

    //save record to file
    do
    {
        printf("\nWould you like to save this information to a file? (Y/N): ");
        scanf("%s", buffer);
        if(strlen(buffer) == 0)
        {
            printf("ERROR: must enter input");
        }
        else if (strcmp(buffer, "Y") != 0 && strcmp(buffer,"N") != 0 && strcmp(buffer,"y") != 0 && strcmp(buffer,"n") != 0)
        {
            printf("ERROR: input must be 'Y' or 'N'");
        }

    } while ( (strlen(buffer) == 0 || strlen(buffer) > BUFFER_LEN) || (strcmp(buffer, "Y") != 0 && strcmp(buffer,"N") != 0 && strcmp(buffer,"y") != 0 && strcmp(buffer,"n") != 0));

    strcpy(userSelect, buffer);

    //clear buffer
    strcpy(buffer, clearBuffer(buffer));

    if (strcmp(userSelect, "Y") == 0 || strcmp(userSelect, "y") == 0)
    {
        fp = fopen("ICD.idx", "w");
        fprintf(fp, "%d", ++recordsNum);
        fclose(fp);

                    
        //making file name
        snprintf(fileName, BUFFER_LEN, "%s_%s_%d.icd", lastName, firstName, recordsNum);

        fp = fopen(fileName, "w");

        //check file opened
        if (fp == NULL)
        {
            printf("ERROR: opening of file failed\n");
            exit(1);
        }
        else
        {
            printf("File created: %s\n", fileName);
            printf("Number of records: %d\n", recordsNum);
        }


        //print data to file
        //name
        fprintf(fp, "Name: %s, %s\n", lastName, firstName);

        //street add
        fprintf(fp, "\nAddress:\n");
        fprintf(fp, "%u %s,\n", streetNum, streetName);
        fprintf(fp, "%s, ", city);
        fprintf(fp, "%s, ", strState);
        fprintf(fp, "%u-%u\n", zipCode, zipPlusFour);

        //phone number
        fprintf(fp, "\nPhone number: (%hu)-%u\n", phone->areaCode, phone->num);
        //phone type
        fprintf(fp, "Phone type: ");
        if (phone->type == Cell)
        {
            fprintf(fp, "Cell\n");
        }
        else
        {
            fprintf(fp, "Landline\n");
        }

            //icd
        fprintf(fp, "\nICD codes and dates:\n");
        for (i = 0; i < icdCount; i++)
        {
            fprintf(fp, "%.*s | %u\n", 10, icdList[i].code, icdList[i].date);
        }

        //close file
        fclose(fp);

    }
    else
    {
        exit(0);
    }
    

    //free memory
    free(firstName);
    free(lastName);
    free(icdList);
    free(phone);
}

void loadRecord(char *fileName, FILE *fp)
{
    char buffer[BUFFER_LEN];

    fp = fopen(fileName, "r");

    if (fp == NULL)
    {
        printf("ERROR: record does not exist\n");
        exit(1);
    }
    else
    {
        printf("Reading file name: %s\n", fileName);
    }

    // printing file contents
    while (fgets(buffer, BUFFER_LEN, fp))
    {
        printf("%s\n", buffer);
    }

    // close file
    fclose(fp);
}

void printHelp()
{
    printf("Usage:\n");
    printf("\t-c [ICD count]\n");
    printf("\t  Specify number of ICD codes to enter\n");
    printf("\t-r [File name]\n");
    printf("\t   Specify record file to open\n");
    exit(0);
}

char* clearBuffer(char* buffer)
{
    int i;

    for (i = 0; i < BUFFER_LEN; i++)
    {
        buffer[i] = '\0';
    }

    return buffer;
}

int checkState(char char1, char char2, enum State* state)
{
    int valid = 0;

    switch(char1)
    {
    case 'A':
        switch(char2)
        {
        case 'R':
            valid = 1;
            *state = AR;
            break;

        case 'L':
            valid = 1;
            *state = AL;
            break;

        case 'K':
            valid = 1;
            *state = AK;
            break;

        case 'Z':
            valid = 1;
            *state = AZ;
            break;

        default:
            valid = 0;
            break;

        }
        break;

    case 'C':
        switch(char2)
        {
        case 'A':
            valid = 1;
            *state = CA;
            break;

        case 'O':
            valid = 1;
            *state = CO;
            break;

        case 'T':
            valid = 1;
            *state = CT;
            break;

        default:
            valid = 0;
            break;

        }
        break;

    case 'D':
        switch(char2)
        {
        case 'E':
            valid = 1;
            *state = DE;
            break;

        default:
            valid = 0;
            break;

        }
        break;

    case 'F':
        switch(char2)
        {
        case 'L':
            valid = 1;
            *state = FL;
            break;

        default:
            valid = 0;
            break;

        }
        break;

    case 'G':
        switch(char2)
        {
        case 'A':
            valid = 1;
            *state = GA;
            break;

        default:
            valid = 0;
            break;

        }
        break;

    case 'H':
        switch(char2)
        {
        case 'I':
            valid = 1;
            *state = HI;
            break;

        default:
            valid = 0;
            break;
        }
        break;

    case 'I':
        switch(char2)
        {
        case 'D':
            valid = 1;
            *state = ID;
            break;

        case 'L':
            valid = 1;
            *state = IL;
            break;

        case 'N':
            valid = 1;
            *state = IN;
            break;

        case 'A':
            valid = 1;
            *state = IA;
            break;

        default:
            valid = 0;
            break;
        }
        break;

    case 'K':
        switch(char2)
        {
        case 'S':
            valid = 1;
            *state = KS;
            break;

        case 'Y':
            valid = 1;
            *state = KY;
            break;

        default:
            valid = 0;
            break;
        }
        break;

    case 'L':
        switch(char2)
        {
        case 'A':
            valid = 1;
            *state = LA;
            break;

        default:
            valid = 0;
            break;
        }
        break;

    case 'M':
        switch(char2)
        {
        case 'E':
            valid = 1;
            *state = ME;
            break;

        case 'D':
            valid = 1;
            *state = MD;
            break;

        case 'A':
            valid = 1;
            *state = MA;
            break;

        case 'I':
            valid = 1;
            *state = MI;
            break;

        case 'N':
            valid = 1;
            *state = MN;
            break;

        case 'O':
            valid = 1;
            *state = MO;
            break;

        case 'T':
            valid = 1;
            *state = MT;
            break;

        default:
            valid = 0;
            break;
        }
        break;

    case 'N':
        switch(char2)
        {
        case 'E':
            valid = 1;
            *state = NE;
            break;

        case 'V':
            valid = 1;
            *state = NV;
            break;

        case 'J':
            valid = 1;
            *state = NJ;
            break;

        case 'M':
            valid = 1;
            *state = NM;
            break;

        case 'Y':
            valid = 1;
            *state = NY;
            break;

        case 'C':
            valid = 1;
            *state = NC;
            break;

        case 'D':
            valid = 1;
            *state = ND;
            break;

        default:
            valid = 0;
            break;
        }
        break;

    case 'O':
        switch(char2)
        {
        case 'H':
            valid = 1;
            *state = OH;
            break;

        case 'K':
            valid = 1;
            *state = OK;
            break;

        case 'R':
            valid = 1;
            *state = OR;
            break;

        default:
            valid = 0;
            break;
        }
        break;

    case 'P':
        switch(char2)
        {
        case 'A':
            valid = 1;
            *state = PA;
            break;

        case 'R':
            valid = 1;
            *state = PR;
            break;

        default:
            valid = 0;
            break;
        }
        break;

    case 'R':
        switch(char2)
        {
        case 'I':
            valid = 1;
            *state = RI;
            break;

        default:
            valid = 0;
            break;
        }
        break;

    case 'S':
        switch(char2)
        {
        case 'C':
            valid = 1;
            *state = SC;
            break;

        case 'D':
            valid = 1;
            *state = SD;
            break;

        default:
            valid = 0;
            break;
        }
        break;

    case 'T':
        switch(char2)
        {
        case 'N':
            valid = 1;
            *state = TN;
            break;

        case 'X':
            valid = 1;
            *state = TX;
            break;

        default:
            valid = 0;
            break;
        }
        break;

    case 'U':
        switch(char2)
        {
        case 'T':
            valid = 1;
            *state = UT;
            break;

        default:
            valid = 0;
            break;
        }
        break;

    case 'V':
        switch(char2)
        {
        case 'T':
            valid = 1;
            *state = VT;
            break;

        case 'A':
            valid = 1;
            *state = VA;
            break;

        case 'I':
            valid = 1;
            *state = VI;
            break;

        default:
            valid = 0;
            break;
        }
        break;

    case 'W':
        switch(char2)
        {
        case 'A':
            valid = 1;
            *state = WA;
            break;

        case 'V':
            valid = 1;
            *state = WV;
            break;

        case 'I':
            valid = 1;
            *state = WI;
            break;

        case 'Y':
            valid = 1;
            *state = WY;
            break;

        default:
            valid = 0;
            break;
        }
        break;

    default:

        valid = 0;
        break;

    }

    return valid;
}
