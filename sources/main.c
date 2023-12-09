#include <packer.h>


int main(int argc, char *argv[])
{
    // argv[0]  = prog path;
    // argv[1]  = mode: a - archive, d - dearchive, h - print help
    // Mode archive:
    //   argv[2]  = output file path
    //   argv[3+] = input files
    // Mode dearchive:
    //   argv[2]  = archive file path

    if (argc <= 1)
    {
        printf("No input provided, exiting.\n");
        return WRONG_INPUT_CODE;
    }
    
    int result_code = SUCCESS_CODE;
    
    if (strcmp(argv[1], "a") == 0)
    {
        if (argc <= 3)
        {
            printf("Wrong files input provided, exiting.\n");
            return WRONG_INPUT_CODE;
        }

        result_code = archive_files(argv[2], argc - 3, argv + 3);
        if (result_code != SUCCESS_CODE)
            return result_code;
    }
    else if (strcmp(argv[1], "d") == 0)
    {
        if (argc <= 2)
        {
            printf("No file provided, exiting.\n");
            return WRONG_INPUT_CODE;
        }

        result_code = dearchive_files(argv[2]);
        if (result_code != SUCCESS_CODE)
            return result_code;
    }
    else if (strcmp(argv[1], "h") == 0)
    {
        printf("argv[1]  = mode: a - archive, d - dearchive, h - print help\n");
        printf("Mode archive:\n");
        printf("  argv[2]  = output file path\n");
        printf("  argv[3+] = input files\n");
        printf("Mode dearchive:\n");
        printf("  argv[2]  = archive file path\n");
    }
    else
    {
        printf("Wrong mode, exiting.\n");
        return WRONG_INPUT_CODE;
    }
    
    return result_code;
}
