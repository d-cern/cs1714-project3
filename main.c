#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "medicalRecord.h"

int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    int recordsNum = 0;
    
    CmdLineParams *ptrParams = (CmdLineParams*)malloc(sizeof(CmdLineParams));
    
    if (argc > 1)
    {
        parseParams(argc, argv, ptrParams);
        //cmd parameter error
        if (ptrParams->boolCodeCount == TRUE && ptrParams->boolFileName == TRUE) // -r and -c mutually exclusive
        {
            printf("ERROR: -r and -c are mutually exclusive\n");
            return 1;
        }
    }
    
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

    }

    // conditional for params
    if (ptrParams->boolCodeCount == TRUE)
    {
        printf("Creating new record with %d ICD code(s)...\n", ptrParams->codeCount);
        createNewRecord(ptrParams->codeCount, recordsNum);
    }
    else if (ptrParams->boolFileName == TRUE)
    {
        printf("Loading record...\n");
        loadRecord(ptrParams->fileName, fp);
    }
    else
    {
        printf("Creating new record...\n");
        createNewRecord(0, recordsNum);
    }
    
    return 0;
}