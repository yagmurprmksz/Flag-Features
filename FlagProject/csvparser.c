#include "csvparser.h"

static int csv_count_fields(const char *strline) {
    const char *ptr;
    int count;

    for(count = 1, ptr = strline; *ptr; ptr++)
    {
        if(*ptr == ',')
        {
            count++;
        }
    }

    return count;
}


int csv_parse_line(char*** dest, const char* source)
{
    char* strtemp   = strdup(source);
    int field_count = csv_count_fields(source);
    char** parsed   = malloc(sizeof(char*) * field_count);

    if(field_count == 1)
    {
        free(strtemp);
        csv_free_line(parsed, field_count);
        return -1;
    }

    parsed[0] = strdup(strtok(strtemp,CSV_DELIMITER));

    for(int i=1; i<field_count; i++)
        parsed[i] = strdup(strtok(NULL,CSV_DELIMITER));

    *dest = parsed;
    free(strtemp);
    return field_count;
}

void csv_free_line (char **parsed, int fieldCount)
{
    char** p = parsed;

    for(int i = 0; i < fieldCount; i++)
        free(p[i]);
    

    free(parsed);
}