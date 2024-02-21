#include "fileoperator.h"
#define BUFFER_SIZE 1024


static char tmpBuffer[BUFFER_SIZE];

void fop_init (file_t* file, const char* fPath)
{
    file->fPtr      = NULL;
    file->fTempPtr  = NULL;

    memcpy(file->path, fPath, strlen(fPath)+1);
    file->currentLine = 0;

}

void fop_release (file_t* file)
{
    file->fPtr      = NULL;
    file->fTempPtr  = NULL;
    file->currentLine = 0;
    memset(file->path, '\0', 256);
}

void fop_write_line (file_t* file, const char* str)
{
    file->fPtr  = fopen(file->path, "a+");
    if (file->fPtr == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        exit(EXIT_SUCCESS);
    }

    fputs("\n", file->fPtr);
    fputs(str, file->fPtr);

    file->currentLine = 0;
    fclose(file->fPtr);

}

char* fop_read_line (file_t* file)
{
    file->fPtr  = fopen(file->path, "r");
    if (file->fPtr == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        exit(EXIT_SUCCESS);
    }

    int count = -1;
    while(count <= file->currentLine)
    {
        if((fgets(tmpBuffer, BUFFER_SIZE, file->fPtr)) != NULL)
            count++;
        else
        {
            fclose(file->fPtr);
            return NULL;
        }
    }

    file->currentLine++;

    fclose(file->fPtr);    

    return strdup(tmpBuffer);
}

void fop_delete_line (file_t* file, const int lineNum)
{
    file->fPtr      = fopen(file->path, "r");
    file->fTempPtr  = fopen("tmpfile", "w");

    if (file->fPtr == NULL || file->fTempPtr == NULL)
    {
        printf("\nUnable to open file.\n");
        exit(EXIT_SUCCESS);
    }

    int last = 0;
    while (fgets(tmpBuffer, BUFFER_SIZE, file->fPtr) != NULL) {
        last++;
    }
    last--;

    fseek(file->fPtr, 0, SEEK_SET);

    int count = -1;
    while ((fgets(tmpBuffer, BUFFER_SIZE, file->fPtr)) != NULL)
    {
        count++;

        if (count == lineNum)
            continue;
        else if (count+1 == last)
        {
            if (lineNum == last)
            {
                tmpBuffer[strlen(tmpBuffer) - 1] = '\0';
                fputs(tmpBuffer, file->fTempPtr);
            }
            else
                fputs(tmpBuffer, file->fTempPtr);
        }
        else
            fputs(tmpBuffer, file->fTempPtr);
    }


    fclose(file->fPtr);
    fclose(file->fTempPtr);

    remove(file->path);

    rename("tmpfile", file->path);
}

void fop_replace_line (file_t* file, const char* str, const int lineNum)
{
    file->fPtr      = fopen(file->path, "r");
    file->fTempPtr  = fopen("tmpfile", "w");

    if (file->fPtr == NULL || file->fTempPtr == NULL)
    {
        printf("\nUnable to open file.\n");
        exit(EXIT_SUCCESS);
    }

    int last = 0;
    while (fgets(tmpBuffer, BUFFER_SIZE, file->fPtr) != NULL) {
        last++;
    }
    last--;

    fseek(file->fPtr, 0, SEEK_SET);

    int count = -1;
    while ((fgets(tmpBuffer, BUFFER_SIZE, file->fPtr)) != NULL)
    {
        count++;

        if (count == lineNum)
        {
            if (lineNum == last)
                fputs(str, file->fTempPtr);
            else
            {
                fputs(str, file->fTempPtr);
                fputs("\n", file->fTempPtr);
            }
        }
        else
        {
            fputs(tmpBuffer, file->fTempPtr);
        }
    }

    fclose(file->fPtr);
    fclose(file->fTempPtr);

    remove(file->path);

    rename("tmpfile", file->path);
}

void fop_dump_file (file_t* file)
{
    file->fPtr  = fopen(file->path, "r");
    if (file->fPtr == NULL)
    {
        printf("\nUnable to open file.\n");
        exit(EXIT_SUCCESS);
    }

    printf("\n");
    while((fgets(tmpBuffer, BUFFER_SIZE, file->fPtr)) != NULL)
    {
        printf("%s", tmpBuffer);
    }

    fclose(file->fPtr);
}