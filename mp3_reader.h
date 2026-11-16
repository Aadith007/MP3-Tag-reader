
#ifndef MP3_READER_H
#define MP3_READER_H

#include "types.h"

Status read_and_validate_args(int argc, char *argv[], mp3info *mp3Info);


Status view_meta_data(mp3info *mp3Info);



Status edit_meta_data(mp3info *mp3Info);

OperationType check_operation_type(char opt);

unsigned int  endian_to_lower(unsigned char *size_buff);

#endif
