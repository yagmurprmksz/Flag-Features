/*
   1. name  Name of the country concerned
   2. landmass  1=N.America, 2=S.America, 3=Europe, 4=Africa, 4=Asia, 6=Oceania
   3. zone  Geographic quadrant, based on Greenwich and the Equator (1=NE, 2=SE, 3=SW, 4=NW)
   4. area  in thousands of square km
   5. population    in round millions
   6. language 1=English, 2=Spanish, 3=French, 4=German, 5=Slavic, 6=Other Indo-European, 7=Chinese, 8=Arabic, 9=Japanese/Turkish/Finnish/Magyar, 10=Others
   7. religion 0=Catholic, 1=Other Christian, 2=Muslim, 3=Buddhist, 4=Hindu, 5=Ethnic, 6=Marxist, 7=Others

*/

#include "flag.h"
flag_t* m_flag;
char buffer[64];

void display_help()
{
    system("clear");
    printf("\n####################################\n");
    printf("\n#                Menu              #\n");
    printf("\n####################################\n");
    printf("\n1 - Add flag\n");
    printf("2 - Search flag\n");
    printf("3 - Update flag\n");
    printf("4 - Delete flag\n");
    printf("Enter '0' for exit\n\n");
    
}

void new_flag()
{

    m_flag = malloc(sizeof(flag_t));
    printf("Country Name: ");
    scanf("%s", buffer);
    m_flag->name = strdup(buffer);
    printf("Landmass: ");
    scanf("%hd", &m_flag->landmass);
    printf("Zone: ");
    scanf("%hd", &m_flag->zone);
    printf("Area:");
    scanf("%ld", &m_flag->area);
    printf("Population:");
    scanf("%ld", &m_flag->population);
    printf("Language:");
    scanf("%hd", &m_flag->language);
    printf("Religion:");
    scanf("%hd", &m_flag->religion);

    flag_add(m_flag);

    flag_release(m_flag);
}

void update_flag_info()
{
    m_flag = malloc(sizeof(flag_t));
    printf("Country Name: ");
    scanf("%s", buffer);
    m_flag->name = strdup(buffer);
    printf("Landmass: ");
    scanf("%hd", &m_flag->landmass);
    printf("Zone: ");
    scanf("%hd", &m_flag->zone);
    printf("Area:");
    scanf("%ld", &m_flag->area);
    printf("Population:");
    scanf("%ld", &m_flag->population);
    printf("Language:");
    scanf("%hd", &m_flag->language);
    printf("Religion:");
    scanf("%hd", &m_flag->religion);

    flag_update(buffer,m_flag);

    flag_release(m_flag);
}

void search_flag()
{
    printf("Country Name: ");
    scanf("%s", buffer);

    m_flag =  flag_search(buffer);

    if(m_flag != NULL)
    {
        flag_print(m_flag);
        flag_release(m_flag);
    }
    else
        printf("Could not found record!\n");
    
}

void delete_flag()
{
    printf("Country Name: ");
    scanf("%s", buffer);
    
    bool result = flag_delete(buffer);
    if(result)
        printf("Has been removed successfully!\n");
    else
        printf("Could not found record!\n");
}

int main()
{
    int selection = 0;
    bool loop = true;

    while(loop)
    {

        display_help();
        printf("Please select one: ");
        scanf("%d", &selection);
        fflush(stdin);
        printf("%d\n", selection);

        switch(selection)
        {
            case 0: loop = false; break;
            case 1: new_flag(); break;
            case 2: search_flag(); break;
            case 3: update_flag_info(); break;
            case 4: delete_flag(); break;
        }

        if(loop != false)
        {
            printf("Press enter to continue");
            getchar();
            getchar();
        }
    }

    return 0;
}