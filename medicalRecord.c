#include <stdio.h>
#include "medicalRecord.h"

void parseParams(int argc, char *argv[])
{
    
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
