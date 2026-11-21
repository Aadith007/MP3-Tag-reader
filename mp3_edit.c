#include<stdio.h>
#include "mp3_reader.h"
#include "types.h"
#include<string.h>
#include<stdlib.h>

Status read_and_validate_edit_args(int argc,char *argv[],mp3info *mp3Info){
    if(argc!=5){
        prntf("Error: Invalid argument count\n");
        return e_failure;
    }
    if(strcmp(argv[2],"-t")!=0 && strcmp(argv[2],"-A")!=0 && strcmp(argv[2],"-y")!=0 && strcmp(argv[2],"-c")!=0 && strcmp(argv[2],"-M")!=0 && strcmp(argv[2],"-a")!=0){
        printf("Error: Invalid edit mode selected\n");
        return e_failure;
    }

     int len=strlen(argv[4]);

    if((len<4)||(argv[4][len-4]!='.')||(argv[4][len-3]!='m') ||(argv[4][len-2]!='p'||(argv[4][len-1]!='3'))){
        printf("Error:Invalid file extension\n");
        return e_failure;
    }

    mp3Info->fptr_mp3 = fopen(argv[4], "rb");
    if(mp3Info->fptr_mp3==NULL){
        printf("Error: File not found\n");
        return e_failure;
    }

    mp3Info->mp3_fname = argv[4];
    return e_success;

}

