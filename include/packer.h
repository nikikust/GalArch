#ifndef __PACKER__
#define __PACKER__

#include <config.h>

#include <stdio.h>
#include <stdlib.h>


int archive_files(char* output_file_name, int files_cnt, char* file_names[]);

int store_file(FILE* input_file, FILE* output_file);

int dearchive_files(char* file_name);

int restore_file(FILE* input_file, char* file_name, long size);

#endif // !__PACKER__
