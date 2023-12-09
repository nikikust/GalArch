#ifndef __HEADERS__
#define __HEADERS__

#include <config.h>

#include <stdio.h>
#include <stdlib.h>


int write_header(int files_cnt, char* file_names[], FILE* output_file);

int generate_subheader(FILE* input_file, FILE* output_file, char* file_name);

int proceed_to_data_section(FILE* input_file, long* size);

int read_header(FILE* input_file, char* file_name, long* data_size);

#endif // !__HEADERS__
