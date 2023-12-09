#include <packer.h>
#include <headers.h>


int archive_files(char* output_file_name, int files_cnt, char* file_names[])
{
    FILE* output_file = fopen(output_file_name, "wb");

    if (output_file == NULL)
    {
        printf("Can't create file '%s'.\n", output_file_name);

        return CANT_CREATE_FILE_CODE;
    }

    int result_code = SUCCESS_CODE;
    
    result_code = write_header(files_cnt, file_names, output_file);
    if (result_code != SUCCESS_CODE)
    {
        fclose(output_file);
        return result_code;
    }

    for (int i = 0; i < files_cnt; ++i)
    {
        FILE* input_file = fopen(file_names[i], "rb");

        if (input_file == NULL)
        {
            printf("Can't open file '%s'.\n", file_names[i]);

            return CANT_OPEN_FILE_CODE;
        }

        result_code = store_file(input_file, output_file);

        fclose(input_file);

        if (result_code != SUCCESS_CODE)
        {
            fclose(output_file);

            return result_code;
        }
    }
    
    fclose(output_file);
        
    return SUCCESS_CODE;
}

int store_file(FILE* input_file, FILE* output_file)
{
    long size = -1;

    if (fseek(input_file, 0, SEEK_END))
        return CANT_READ_FILE_CODE;

    size = ftell(input_file);

    rewind(input_file);

    while (size > 0)
    {
        fputc(fgetc(input_file), output_file);

        --size;
    }

    return SUCCESS_CODE;
}

int dearchive_files(char* file_name)
{
    // Open archive for reading
    FILE* input_file_header = fopen(file_name, "rb");
    FILE* input_file_data   = fopen(file_name, "rb");

    if (input_file_header == NULL || input_file_data == NULL)
    {
        printf("Can't open archive '%s' to read.\n", file_name);

        return CANT_OPEN_FILE_CODE;
    }

    // Move file pointer to data section
    int result_code = SUCCESS_CODE;
    long header_size = 0;

    result_code = proceed_to_data_section(input_file_data, &header_size);

    if (result_code != SUCCESS_CODE)
    {
        fclose(input_file_data);
        fclose(input_file_header);

        return result_code;
    }

    if (header_size == 0)
    {
        fclose(input_file_data);
        fclose(input_file_header);

        printf("Can't read header of archive '%s'.\n", file_name);

        return CANT_READ_HEADER_CODE;
    }

    // Unpack files
    long data_size = 0;
    char archived_file_name[256] = "\0";
    int file_name_length = 0;
    do
    {
        result_code = read_header(input_file_header, archived_file_name, &data_size);

        if (result_code != SUCCESS_CODE)
        {
            fclose(input_file_data);
            fclose(input_file_header);

            return result_code;
        }

        if (strcmp(archived_file_name, "") == 0)
        {
            break;
        }

        result_code = restore_file(input_file_data, archived_file_name, data_size);

        if (result_code != SUCCESS_CODE)
        {
            fclose(input_file_data);
            fclose(input_file_header);

            return result_code;
        }

    } while (strcmp(archived_file_name, "") != 0);

    return SUCCESS_CODE;
}

int restore_file(FILE* input_file, char* file_name, long size)
{
    FILE* restored_file = fopen(file_name, "wb");

    if (restored_file == NULL)
    {
        printf("Can't open file '%s' to write.\n", file_name);

        return CANT_OPEN_FILE_CODE;
    }

    while (size > 0)
    {
        fputc(fgetc(input_file), restored_file);

        --size;
    }

    return SUCCESS_CODE;
}
