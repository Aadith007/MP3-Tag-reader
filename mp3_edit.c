#include<stdio.h>
#include "mp3_reader.h"
#include "types.h"
#include<string.h>
#include<stdlib.h>

Status read_and_validate_edit_args(int argc,char *argv[],mp3info *mp3Info){
    if(strcmp(argv[1],"-e")!=0){
        printf("Error: Invalid operation\n");
        return e_failure;
    }
    if(argc!=5){
        printf("Error: Invalid argument count\n");
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
    mp3Info->edit_option = argv[2];
    mp3Info->new_value = argv[3];
    mp3Info->mp3_fname = argv[4];
Status edit_meta_data(mp3info *mp3Info){

    mp3Info->fptr_temp=fopen("temp.mp3","wb");
    if(mp3Info->fptr_temp==NULL){
        printf("Error: Unable to create temporary file\n");
        return e_failure;

    }

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

    while(1){

    char frame_ID[5];
    if(fread(frame_ID,4,1,mp3Info->fptr_mp3)!=1){
      printf("Error: Target frame not found\n");
      return e_failure;
    }

    frame_ID[4]='\0';
    if(frame_ID[0]=='\0'){
        printf("Error: Target frame not founf\n");
        return e_failure;
    }
  
    unsigned char size_buff[4];
    if(fread(size_buff,4,1,mp3Info->fptr_mp3)!=1){
        printf("Error: Failed to read tag size\n");
        return e_failure;
    }
    int frame_size=endian_to_lower(size_buff);
    if(fseek(mp3Info->fptr_mp3, 3, SEEK_CUR) != 0){
    printf("Error: Failed to skip bytes\n");
    return e_failure;
    }

    char selected_frame[5];
    if(strcmp(mp3info->edit_option,"-t")==0){
        strcpy(selected_frame,"TIT2");
    }
     else if(strcmp(mp3info->edit_option,"-a")==0){
        strcpy(selected_frame,"TPE1");
    }

    else if(strcmp(mp3info->edit_option,"-A")==0){
        strcpy(selected_frame,"TALB");
    }
    else if(strcmp(mp3info->edit_option,"-y")==0){
        strcpy(selected_frame,"TYER");
    }
    else if(strcmp(mp3info->edit_option,"-c")==0){
        strcpy(selected_frame,"TCON");
    }
    else if(strcmp(mp3info->edit_option,"-M")==0){
        strcpy(selected_frame,"TCOMM");
    }


    
    



}

}

unsigned int endian_to_lower(unsigned char *size_buff){
    unsigned char temp;
    temp=size_buff[0];
    size_buff[0]=size_buff[3];
    size_buff[3]=temp;

    temp = size_buff[1];
    size_buff[1] = size_buff[2]; 
    size_buff[2] = temp;

    unsigned int frame_size;

    frame_size = ((unsigned int)size_buff[3] << 24) | ((unsigned int)size_buff[2] << 16) |((unsigned int)size_buff[1] << 8) |(unsigned int)size_buff[0];
    return frame_size;
}


    







