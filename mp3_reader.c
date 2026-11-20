#include<stdio.h>
#include "mp3_reader.h"
#include "types.h"
#include<string.h>
#include<stdlib.h>


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

    char frame_id[6][5]={"TIT2","TPE1","TALB","TYER","TCON","TCOM"};
    char tag_names[6][10] = {"Title", "Artist", "Album", "Year", "Genre", "Composer"};
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
  printf("-------------------------------------\n");
    printf("ID3 Version: ID3v2.%d.%d\n", buff[3], buff[4]);
    printf("-------------------------------------\n");
    if(fseek(mp3Info->fptr_mp3, 10, SEEK_SET) != 0)
    {
    printf("Error: Failed to seek file\n");
    return e_failure;
    }

    // while loop start//

    while(1){

       char frame_ID[5];
/// frame header start
if(fread(frame_ID,4,1,mp3Info->fptr_mp3)!=1){
      
        break;
    }
   
  
    frame_ID[4]='\0';
  

    unsigned char size_buff[4];
    if(fread(size_buff,4,1,mp3Info->fptr_mp3)!=1){
        printf("Error: Failed to read tag size\n");
        return e_failure;
    }

    int frame_size=endian_to_lower(size_buff);




    if(fseek(mp3Info->fptr_mp3,2,SEEK_CUR)!=0){
        printf("Error: Failed to seek file\n");
        return e_failure;
    } ///skip 2 bytes of flag

    if(strcmp(frame_ID, "TIT2") == 0 ||
   strcmp(frame_ID, "TPE1") == 0 ||
   strcmp(frame_ID, "TALB") == 0 ||
   strcmp(frame_ID, "TYER") == 0 ||
   strcmp(frame_ID, "TCON") == 0 ||
   strcmp(frame_ID, "TCOM") == 0){

    unsigned char encoding;

    if(fread(&encoding, 1, 1, mp3Info->fptr_mp3) != 1){
    printf("Error: Failed to read encoding\n");
    return e_failure;
    
}
   // printf("Encoding: %u\n", encoding);
    if(frame_size<1){
        printf("Invalid frame size\n");
        return e_failure;
    }


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


    for(int i=0;i<6;i++){
        if(strcmp(frame_ID,frame_id[i])==0){
            printf("%s: %s\n",tag_names[i],data);
            break;
        }
    }
    // if(strcmp(frame_ID,"TIT2")==0){
    //     printf("%s : %s\n",frame_ID,data);
    //     printf("Frame ID: %s\n", frame_ID);
       
    // }
    // else if(strcmp(frame_ID,"TPE1")==0){
    //     printf("%s:  %s\n",frame_ID,data);
    //     printf("Frame ID: %s\n", frame_ID);
    // }
    // else if(strcmp(frame_ID,"TALB")==0){
    //     printf("%s: %s\n",frame_ID,data);
    //     printf("Frame ID: %s\n", frame_ID);
    // }
    // else if(strcmp(frame_ID,"TYER")==0){
    //     printf("%s: %s\n",frame_ID,data);
    //     printf("Frame ID: %s\n", frame_ID);
    // }

    
    
    //  else if(strcmp(frame_ID,"TCON")==0){
    //     printf("%s: %s\n",frame_ID,data);
    //     printf("Frame ID: %s\n", frame_ID);

      
    // }

    //  else if(strcmp(frame_ID,"TCOM")==0){
    //     printf("%s: %s\n",frame_ID,data);
    //     printf("Frame ID: %s\n", frame_ID);
    // }
    printf("-------------------------------------\n");
      free(data);
     
}
else{
    fseek(mp3Info->fptr_mp3,frame_size,SEEK_CUR);
}


}

    
    fclose(mp3Info->fptr_mp3);
      return e_success; 
    
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