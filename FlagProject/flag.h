#ifndef FLAG_H
#define FLAG_H

#include <stdbool.h>
#include "fileoperator.h"
#include "csvparser.h"

/*
   1. name  Name of the country concerned
   2. landmass  1=N.America, 2=S.America, 3=Europe, 4=Africa, 4=Asia, 6=Oceania
   3. zone  Geographic quadrant, based on Greenwich and the Equator (1=NE, 2=SE, 3=SW, 4=NW)
   4. area  in thousands of square km
   5. population    in round millions
   6. language 1=English, 2=Spanish, 3=French, 4=German, 5=Slavic, 6=Other Indo-European, 7=Chinese, 8=Arabic, 9=Japanese/Turkish/Finnish/Magyar, 10=Others
   7. religion 0=Catholic, 1=Other Christian, 2=Muslim, 3=Buddhist, 4=Hindu, 5=Ethnic, 6=Marxist, 7=Others

*/

#define FILENAME "flag.data"


typedef struct flag
{
    char* name;
    long  area;
    long  population;
    short landmass;
    short zone;
    short language;
    short religion;

} flag_t;


void flag_add       (const flag_t* flag);
void flag_update    (const char* countryName, const flag_t* flag);
bool flag_delete    (const char* countryName);
flag_t* flag_search (const char* countryName);
void flag_print     (const flag_t* flag);
void flag_release   (flag_t* flag);
void flag_list_all  (void);

short str_to_lanmass    (const char* str);
short str_to_zone       (const char* str);
short str_to_area       (const char* str);
short str_to_population (const char* str);
short str_to_language   (const char* str);
short str_to_religion   (const char* str);

char* landmass_to_str (short landmass);
char* zone_to_str     (short zone);
char* language_to_str (short language);
char* religion_to_str (short religion);


#endif // FLAG_H