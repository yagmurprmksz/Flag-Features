#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct file
{
    FILE* fPtr;
    FILE* fTempPtr;
    char path[256];
    int currentLine;

} file_t;

void    fop_init            (file_t* file, const char* fPath);
void    fop_release         (file_t* file);
void    fop_write_line      (file_t* file, const char* str);
char*   fop_read_line       (file_t* file);
void    fop_replace_line    (file_t* file, const char* str, const int lineNum);
void    fop_delete_line     (file_t* file, const int lineNum);
void    fop_dump_file       (file_t* file);




#endif // FILEOPERATOR_H
