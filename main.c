#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "medicalRecord.h"

int main(int argc, char *argv[])
{
    int i;
    char buffer[BUFFER_LEN];
    int recordsNum = 0;
    FILE* fp = NULL;
    char fileName[BUFFER_LEN];
    char userSelect[1];
    int userInt;
    
    char* firstName = NULL;
    char* lastName = NULL;

    unsigned int streetNum;
    char* streetName = NULL;
    char* city = NULL;
    State state;
    char strState[2];
    int validState = 0;
    unsigned int zipCode, zipPlusFour;

    PHONE* phone = NULL;
    ICD* icdList = NULL;


    printf("Patient Records Application\n\n");
    
    //check for ICD.idx
    if (fopen("ICD.idx", "r") == NULL)  //if no ICD.idx => create ICD.idx + set recordsNum to 0
    {
        printf("No previous records. Creating file for number of records...\n");
        fp = fopen("ICD.idx", "w");
        fprintf(fp, "%d", recordsNum);
            
        fclose(fp);
    }
    else    //if ICD.idx found => read value
    {
        fp = fopen("ICD.idx", "r");
        fscanf(fp, "%d", &recordsNum);
        
        printf("ICD.idx found. Current number of records: %d\n", recordsNum);
        fclose(fp);

        //ask if would like to load previous record
        do
        {
            printf("\nWould you like to reload a previous record (Y/N): ");
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
    }
    
    //enter new record
    if (strcmp(userSelect, "N") == 0 || strcmp(userSelect, "n") == 0)
    {  
        //first name
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
        }
        while (strlen(buffer) == 0 || strlen(buffer) > MAX_NAME_LEN);

        firstName = (char*)malloc(sizeof(char) * strlen(buffer));
        strcpy(firstName, buffer);

        //clear buffer
        strcpy(buffer, clearBuffer(buffer));

        //last name
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
        }
        while (strlen(buffer) == 0 || strlen(buffer) > MAX_NAME_LEN);

        lastName = (char*)malloc(sizeof(char) * strlen(buffer));
        strcpy(lastName, buffer);

        //clear buffer
        strcpy(buffer, clearBuffer(buffer));

        //street address
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
        }
        while (streetNum < 1 || streetNum > 999999  ||  strlen(buffer) == 0 || strlen(buffer) > MAX_NAME_LEN);

        streetName = (char*)malloc(sizeof(char) * strlen(buffer));
        strcpy(streetName, buffer);

        //clear buffer
        strcpy(buffer, clearBuffer(buffer));

        //city
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
        }
        while (strlen(buffer) == 0 || strlen(buffer) > MAX_CITY_LEN);

        city = (char*)malloc(sizeof(char) * strlen(buffer));
        strcpy(city, buffer);

        //state
        i = 0;
        do
        {
            //clear buffer
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

        //zip code
        i = 0;
        do
        {
            //clear buffer
            strcpy(buffer, clearBuffer(buffer));

            if (i > 0)
            {
                printf("Invalid ZIP code");
            }

            printf("Enter ZIP code in format \"XXXXX-XXXX\": ");
            scanf("%u-%u", &zipCode, &zipPlusFour);
            i++;

        }
        while ( zipCode < 1000 || zipCode > 99950 || zipPlusFour < 1000 || zipPlusFour > 9999 );

        //phone number
        phone = (PHONE*)malloc(sizeof(PHONE));
        do
        {
            printf("Enter phone number in format XXX-XXXXXXX: ");
            scanf("%hu-%u", &phone->areaCode, &phone->num);
        }
        while (phone->areaCode < 200 || phone->areaCode >999 || phone->num <2010000 || phone->num >9999999);

        //phone type
        i = 0;
        do
        {
            if (i > 0)
            {
                printf("Invalid input");
            }

            printf("Enter 0 for \"Cell\" or 1 for \"Landline\": ");
            scanf("%u", &phone->type);
            i == 0 ? i++ : i;

        }
        while (phone->type != 0 && phone->type != 1);

        //icd codes
        icdList = (ICD*)malloc(sizeof(ICD) * 4);

        for (i = 0; i < 4; i++)
        {
            printf("Enter ICD code #%d: ", i + 1);

            do
            {
                scanf("%s",buffer);

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
            icdList[i].code = (char*)malloc(sizeof(char) * icdList[i].codeLen);
            strcpy(icdList[i].code, buffer);
        }

        //clear buffer
        strcpy(buffer,clearBuffer(buffer));


        //print/confirm data
            //name
        printf("\nName: %s, %s\n", lastName, firstName);

            //street add
        printf("\nAddress:\n");
        printf("%u %s,\n", streetNum, streetName);
        printf("%s, ", city);
        printf("%s, ", strState);
        printf("%u-%u\n", zipCode, zipPlusFour);

            //phone number
        printf("\nPhone number: (%hu)-%u\n", phone->areaCode, phone->num);
            //phone type
        printf("Phone type: ");
        if (phone->type == Cell)
        {
            printf("Cell\n");
        }
        else
        {
            printf("Landline\n");
        }

            //icd
        printf("\nICD codes and dates:\n");
        for (i = 0; i < 4; i++)
        {
            printf("%.*s | %u\n", 10, icdList[i].code, icdList[i].date);
        }

        printf("\n");

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
                return -1;
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
            for (i = 0; i < 4; i++)
            {
                fprintf(fp, "%.*s | %u\n", 10, icdList[i].code, icdList[i].date);
            }

            //close file
            fclose(fp);
        }
    
    }
    else if (strcmp(userSelect, "Y") == 0 || strcmp(userSelect, "y") == 0) //reload record
    {
        //first name
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
        }
        while (strlen(buffer) == 0 || strlen(buffer) > MAX_NAME_LEN);
        
        firstName = (char*)malloc(sizeof(char) * strlen(buffer));
        strcpy(firstName, buffer);
        
        //clear buffer
        strcpy(buffer, clearBuffer(buffer));

        //last name
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
        }
        while (strlen(buffer) == 0 || strlen(buffer) > MAX_NAME_LEN);

        lastName = (char*)malloc(sizeof(char) * strlen(buffer));
        strcpy(lastName, buffer);
        
        do
        {
            printf("Enter record number: ");
            scanf("%d", &userInt);
            
            if (userInt < 1 && userInt > 2000000)
            {
                printf("ERROR: must enter a valid number\n");
            }
        }
        while (userInt < 1 && userInt > 2000000);
        
        //making file name
        snprintf(fileName, BUFFER_LEN, "%s_%s_%d.icd", lastName, firstName, userInt);
        
        fp = fopen(fileName, "r");
        
        if (fp == NULL)
        {
            printf("ERROR: record does not exist\n");
            return 1;
        }
        else
        {
            printf("Reading file name: %s\n", fileName);
        }

        //printing file contents
        while( fgets(buffer, BUFFER_LEN, fp) )
        {
            printf("%s\n", buffer);
        }

        //close file
        fclose(fp);

    }
    //free memory
    free(firstName);
    free(lastName);
    free(icdList);
    free(phone);
    
    return 0;
}