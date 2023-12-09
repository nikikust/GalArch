#include <headers.h>
#include <config.h>

#include <string.h>


int write_header(int files_cnt, char* file_names[], FILE* output_file)
{
    for (int i = 0; i < files_cnt; ++i)
    {
        FILE* input_file = fopen(file_names[i], "rb");

        if (input_file == NULL)
        {
            printf("Can't open file '%s' to read.\n", file_names[i]);

            return CANT_OPEN_FILE_CODE;
        }

        int result_code = generate_subheader(input_file, output_file, file_names[i]);

        fclose(input_file);

        if (result_code != SUCCESS_CODE)
            return result_code;
    }

    fputc('|', output_file);

    return SUCCESS_CODE;
}

int generate_subheader(FILE* input_file, FILE* output_file, char* file_name)
{
    long size = -1;

    if (fseek(input_file, 0, SEEK_END))
    {
        return CANT_READ_FILE_CODE;
    }

    size = ftell(input_file);
    char size_str[256] = "\0";
    sprintf(size_str, "%d", size);

    printf("File: %s, size: %ld\n", file_name, size);

    fwrite(file_name, 1, sizeof(char) * strlen(file_name), output_file);
    fputc(':', output_file);

    fwrite(size_str,  1, sizeof(char) * strlen(size_str),  output_file);
    fputc('|', output_file);

    return SUCCESS_CODE;
}

int proceed_to_data_section(FILE* input_file, long* size)
{
    char c = fgetc(input_file);
    long found_end_of_subheader = 0;
    long pos = 1;

    while (c != EOF)
    {
        if (c == '|' && found_end_of_subheader + 1 != pos)
        {
            found_end_of_subheader = pos;
        }
        else if (c == '|' )
        {
            *size = pos;

            return SUCCESS_CODE;
        }

        c = fgetc(input_file);
        ++pos;
    }

    printf("Archive is corrupted, exiting!\n");

    return CANT_READ_HEADER_CODE;
}

int read_header(FILE* input_file, char* file_name, long* data_size)
{
    file_name[0] = '\0';
    *data_size = 0;

    char c = fgetc(input_file);

    if (c == '|')
    {
        return SUCCESS_CODE;
    }

    while (c != ':')
    {
        int len = strlen(file_name);
        file_name[len] = c;
        file_name[len + 1] = '\0';

        c = fgetc(input_file);
    }

    c = fgetc(input_file);

    while (c != '|')
    {
        *data_size *= 10;
        *data_size += atoi(&c);

        c = fgetc(input_file);
    }

    printf("File: %s, size: %ld\n", file_name, *data_size);

    return SUCCESS_CODE;
}
