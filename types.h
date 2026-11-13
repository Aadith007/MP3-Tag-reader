#ifndef TYPES_H
#define TYPES_H

#include<stdio.h>

typedef unsigned int uint;

typedef enum
{
    e_success,
    e_failure
} Status;

typedef struct{
    char *mp3_fname;
    FILE *fptr_mp3;

}mp3info;


typedef enum
{
    mp3_view,
    mp3_edit,
    e_unsupported
} OperationType;

#endif

