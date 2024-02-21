#include "flag.h"


/*
    long  area;
    long  population;
    short landmass;
    short zone;
    short language;
    short religion;
    char* name;
*/
static bool flag_fill_container(flag_t* flag, char** parsedLine, int fieldCount)
{
    if(fieldCount < 5)
        return false;

    flag->name = malloc(sizeof(char) * (strlen(parsedLine[0])+1));
    memcpy(flag->name, parsedLine[0], (strlen(parsedLine[0])+1));
    flag->landmass      = atoi(parsedLine[1]);
    flag->zone          = atoi(parsedLine[2]);
    flag->area          = atoi(parsedLine[3]);
    flag->population    = atoi(parsedLine[4]);
    flag->language      = atoi(parsedLine[5]);
    flag->religion      = atoi(parsedLine[6]);

    return true;
}

void flag_add (const flag_t* flag)
{
    file_t flagFile;
    char line[1024];
    char buff[32];

    memset(line, 0, 1024);

    strcat(line, flag->name);
    strcat(line, ",");
    sprintf(buff,"%d",flag->landmass);
    strcat(line, buff);
    strcat(line, ",");
    sprintf(buff,"%d",flag->zone);
    strcat(line, buff);
    strcat(line, ",");
    sprintf(buff,"%ld",flag->area);
    strcat(line, buff);
    strcat(line, ",");
    sprintf(buff,"%ld",flag->population);
    strcat(line, buff);
    strcat(line, ",");
    sprintf(buff,"%d",flag->language);
    strcat(line, buff);
    strcat(line, ",");
    sprintf(buff,"%d",flag->religion);
    strcat(line, buff);

    fop_init(&flagFile, FILENAME);

    fop_write_line(&flagFile, line);

    fop_release(&flagFile);
}
void flag_update (const char* countryName, const flag_t* flag)
{
    file_t flagFile;
    char lineBuf[1024];
    char* newLine = NULL;
    char** parsedLine = NULL;
    flag_t* ptmpFlag = malloc(sizeof(flag_t));
    fop_init(&flagFile, FILENAME);

    while((newLine = fop_read_line(&flagFile)))
    {
        memset(lineBuf, 0, 1024);
        strcat(lineBuf, newLine);

        int fieldCount = csv_parse_line(&parsedLine, lineBuf);
        bool result = flag_fill_container(ptmpFlag, parsedLine, fieldCount);
        if(result)
        {
            if(strcmp(ptmpFlag->name, countryName) == 0)
            {
                memset(lineBuf, 0, 1024);
                char buff[32];

                strcat(lineBuf, flag->name);
                strcat(lineBuf, ",");
                sprintf(buff,"%d",flag->landmass);
                strcat(lineBuf, buff);
                strcat(lineBuf, ",");
                sprintf(buff,"%d",flag->zone);
                strcat(lineBuf, buff);
                strcat(lineBuf, ",");
                sprintf(buff,"%ld",flag->area);
                strcat(lineBuf, buff);
                strcat(lineBuf, ",");
                sprintf(buff,"%ld",flag->population);
                strcat(lineBuf, buff);
                strcat(lineBuf, ",");
                sprintf(buff,"%d",flag->language);
                strcat(lineBuf, buff);
                strcat(lineBuf, ",");
                sprintf(buff,"%d",flag->religion);
                strcat(lineBuf, buff);

                fop_replace_line(&flagFile, lineBuf, flagFile.currentLine);

                csv_free_line(parsedLine, fieldCount);
                free(newLine);
                fop_release(&flagFile);
                flag_release(ptmpFlag);

                return;
            }

            free(ptmpFlag->name);
            ptmpFlag->name = NULL;
            csv_free_line(parsedLine, fieldCount);
        }

        free(newLine);
    }
    free(ptmpFlag);
    fop_release(&flagFile);
}
bool flag_delete (const char* countryName)
{
    file_t flagFile;
    char lineBuf[1024];
    char* newLine = NULL;
    char** parsedLine = NULL;
    flag_t* ptmpFlag = malloc(sizeof(flag_t));
    fop_init(&flagFile, FILENAME);

    while((newLine = fop_read_line(&flagFile)))
    {
        //printf("%s\n\n", line);
        memset(lineBuf, 0, 1024);
        strcat(lineBuf, newLine);

        int fieldCount = csv_parse_line(&parsedLine, lineBuf);
        bool result = flag_fill_container(ptmpFlag, parsedLine, fieldCount);
        if(result)
        {
            if(strcmp(ptmpFlag->name, countryName) == 0)
            {

                fop_delete_line(&flagFile, flagFile.currentLine);

                csv_free_line(parsedLine, fieldCount);
                free(newLine);
                fop_release(&flagFile);
                flag_release(ptmpFlag);
                return true;
            }
            free(ptmpFlag->name);
            ptmpFlag->name = NULL;
            csv_free_line(parsedLine, fieldCount);
        }

        free(newLine);
    }
    flag_release(ptmpFlag);
    fop_release(&flagFile);

    return false;
}

flag_t* flag_search (const char* countryName)
{

    file_t flagFile;
    char lineBuf[1024];
    char* newLine = NULL;
    char** parsedLine = NULL;
    flag_t* ptmpFlag = malloc(sizeof(flag_t));
    fop_init(&flagFile, FILENAME);

    while((newLine = fop_read_line(&flagFile)))
    {
        memset(lineBuf, 0, 1024);
        strcat(lineBuf, newLine);

        int fieldCount = csv_parse_line(&parsedLine, lineBuf);
        bool result = flag_fill_container(ptmpFlag, parsedLine, fieldCount);
        if(result)
        {
            if(strcmp(ptmpFlag->name, countryName) == 0)
            {
                csv_free_line(parsedLine, fieldCount);
                free(newLine);
                fop_release(&flagFile);
                return ptmpFlag;
            }
            free(ptmpFlag->name);
            ptmpFlag->name = NULL;
            csv_free_line(parsedLine, fieldCount);
        }
        free(newLine);
    }

    flag_release(ptmpFlag);
    fop_release(&flagFile);
    return NULL;
}

void flag_print (const flag_t* flag)
{
    printf("\n\n");
    printf("\t Flag Info\n");
    printf("Country Name: \t%s\n", flag->name);
    printf("Landmass: \t%s\n", landmass_to_str(flag->landmass));
    printf("Zone: \t\t%s\n", zone_to_str(flag->zone));
    printf("Area: \t\t%ld square km\n", flag->area * 1000);
    printf("Population: \t%ld millions\n", flag->population);
    printf("Language: \t%s\n", language_to_str(flag->language));
    printf("Religion: \t%s\n", religion_to_str(flag->religion));
    printf("\n\n");
}

void flag_release (flag_t* flag)
{
    if(flag->name != NULL) free(flag->name);
    free(flag);
}

void flag_list_all ()
{

}

char* landmass_to_str (short landmass)
{
    switch(landmass)
    {
        case 1: return "N.America";
        case 2: return "S.America";
        case 3: return "Europe";
        case 4: return "Africa";
        case 5: return "Asia";
        case 6: return "Oceania";
    }
    return "Unknown";
}

char* zone_to_str (short zone)
{
    switch(zone)
    {
        case 1: return "NE";
        case 2: return "SE";
        case 3: return "SW";
        case 4: return "NW";
    }
    return "Unknown";
}

char* language_to_str (short language)
{
    switch(language)
    {
        case 1: return "English";
        case 2: return "Spanish";
        case 3: return "French";
        case 4: return "German";
        case 5: return "Slavic";
        case 6: return "Other Indo-European";
        case 7: return "Chinese";
        case 8: return "Arabic";
        case 9: return "Japanese/Turkish/Finnish/Magyar";
        case 10: return "Others";
    }
    return "Unknown";
}

char* religion_to_str (short religion)
{
    switch(religion)
    {
        case 0: return "Catholic";
        case 1: return "Other Christian";
        case 2: return "Muslim";
        case 3: return "Buddhist";
        case 4: return "Hindu";
        case 5: return "Ethnic";
        case 6: return "Marxist";
        case 7: return "Others";
    }
    return "Unknown";
}

short str_to_lanmass (const char* str)
{
    return atoi(str);
}
short str_to_zone (const char* str)
{
    return atoi(str);
}
short str_to_area (const char* str)
{
    return atoi(str);
}
short str_to_population (const char* str)
{
    return atoi(str);
}
short str_to_language (const char* str)
{
    return atoi(str);
}
short str_to_religion (const char* str)
{
    return atoi(str);
}