#include<stdio.h>
#include "mp3_reader.h"
#include "types.h"
#include<string.h>

 Status read_and_validate_args(int argc,char *argv[],mp3info *mp3Info){
    if(argc!=3){
        printf("Invalid input format\n");
        return e_failure;
    }
    if(argv[1][0]!='-' || argv[1][1]!='v'||argv[1][2] !='\0'){
        printf("Invalid input format\n");
        return e_failure;
    }
    int len=strlen(argv[2]);

    if((len<4)||(argv[2][len-4]!='.')||(argv[2][len-3]!='m') ||(argv[2][len-2]!='p'||(argv[2][len-1]!='3'))){
        printf("Error:Invalid file extension\n");
        return e_failure;
    }
    mp3Info->fptr_mp3 = fopen(argv[2], "rb");
    if(mp3Info->fptr_mp3==NULL){
        printf("Error: File not found\n");
        return e_failure;
    }
    mp3Info->mp3_fname=argv[2];
    return e_success;

 }
 Status view_meta_data(mp3info *mp3Info)
{
    printf("View operation started\n");
    char buff[10];
    if(fread(buff,10,1,mp3Info->fptr_mp3)!=1){
        printf("Error: Incomplete header file\n");
        return e_failure;
    }
    if(strncmp(buff,"ID3",3)!=0){
        printf("Error: Header mismatch\n");
        return e_failure;
    }
    if(buff[3]!=3 || buff[4]!=0){
        printf("Invalid version\n");
        return e_failure;
    }
/// frame header start
   if(fseek(mp3Info->fptr_mp3, 10, SEEK_SET) != 0)
    {
    printf("Error: Failed to seek file\n");
    return e_failure;
    }
    char frame_ID[5];
    if(fread(buff,4,1,mp3Info->fptr_mp3)!=1){
        printf("Error:Failed to read tag name\n");
        return e_failure;
    }
    frame_ID[4]='\0';

    unsigned char size_buff[4];
    if(fread(size_buff,4,1,mp3Info->fptr_mp3)!=1){
        printf("Error: Failed to read tag size\n");
        return e_failure;
    }
    unsigned char temp;
    temp=size_buff[0];
    size_buff[0]=size_buff[3];
    size_buff[3]=temp;

    temp = size_buff[1];
    size_buff[1] = size_buff[2];
    size_buff[2] = temp;

    unsigned int frame_size;

    frame_size=((unsigned int)size_buff[0]<<24)|((unsigned int)size_buff[1]<<16)|((unsigned int)size_buff[2]<<8)|((unsigned int)size_buff[3]);
    printf("%u\n",frame_size);

    fseek(mp3Info->fptr_mp3,2,SEEK_CUR); ///skip 2 bytes of flag

    unsigned int text_size=frame_size-1;
    char *data=malloc(text_size+1);
    if(data==NULL){
        printf("Error: Memory allocation failed\n");
        return e_failure;
    }      

    if(fread(data,text_size,1,mp3Info->fptr_mp3)!=1){
        printf("Error: Failed to read meta data\n");
        free(data);
        return e_failure;
    }
    data[text_size]='\0';

    














}