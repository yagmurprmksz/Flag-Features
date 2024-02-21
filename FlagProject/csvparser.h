#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define CSV_DELIMITER ","

int     csv_parse_line      (char*** dest, const char* source);
void    csv_free_line       (char** parsed, int fieldCount);


#endif // CSVPARSER_H