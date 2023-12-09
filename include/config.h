#ifndef __CONFIG__
#define __CONFIG__

#define OUTPUT_FILE "archived.arch"


enum APP_CODES
{
    SUCCESS_CODE = 0,
    WRONG_INPUT_CODE,
    CANT_OPEN_FILE_CODE,
    CANT_CREATE_FILE_CODE,
    CANT_READ_HEADER_CODE,
    CANT_READ_FILE_CODE
};

#endif // !__CONFIG__
