#include<stdio.h>
#include "mp3_reader.h"
#include "types.h"


   
int main(int argc, char *argv[])
{
    mp3info mp3Info;

    if (argc < 2 || argv[1][0] != '-' || argv[1][2] != '\0')
    {
        printf("Incorrect command line format\n");
        return 1;
    }

    OperationType op = check_operation_type(argv[1][1]);

    if (op == mp3_view)
    {
        if (read_and_validate_args(argc, argv, &mp3Info) == e_success)
        {
           

            if (view_meta_data(&mp3Info) == e_failure){
            
                printf("Meta data read failed\n");
                return 1;
            }

            
        }
        else{
        
            printf(" Argument validation failed\n");
            return 1; 
              }
        }
        else
        {
            printf("Argument validation failed\n");
            return 1;
        }
    
    // else
    // {
    //     printf("Unsupported operation\n");
    //     return 1;
    // }

    return 0;
}

OperationType check_operation_type(char opt){
    if(opt=='v')
    return  mp3_view;
    if(opt=='e')
    return mp3_edit;
    else
    return e_unsupported;
}
