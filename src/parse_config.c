#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parse_config.h"

parse_result
parse_config ()
{
    char* file_name = "/home/ruzen42/.config/killit/killit.conf";

    parse_result result =
    {
        .poweroff_enabled = true,
        .suspend_enabled = true,
        .reboot_enabled = true,
        .hibernate_enabled = true,
    };

    FILE* config_file = fopen (file_name, "r");

    if (config_file == NULL)
    {
        printf ("Error with parsing file\n");

        strcpy (result.suspend_command, "suspend");
        strcpy (result.reboot_command, "reboot");
        strcpy (result.hibernate_command, "systemctl hibernate");
        strcpy (result.poweroff_command, "shutdown now");

        result.success_parse = false;
        perror ("fopen");
        return result;
    }

    char line[512];

    while (fgets (line, sizeof (line), config_file))
    {
        line[strcspn (line, "\n")] = 0;
        char* equal = strchr (line, '=');

        if (!equal) 
            continue;    

        *equal = '\0';
        char* key = line;
        char* value = equal + 1;

       if (strcmp (key, "poweroff") == 0) 
       {
            strncpy(result.poweroff_command, value, sizeof(result.poweroff_command));
       } 

       if (strcmp (key, "reboot") == 0)
       {
        strncpy (result.reboot_command, value, sizeof(result.reboot_command));
       }
      
       
       if (strcmp (key, "suspend") == 0) 
       {
           strncpy(result.suspend_command, value, sizeof(result.suspend_command));
       }

       if (strcmp (key, "hibernate") == 0)
       {
           strncpy(result.hibernate_command, value, sizeof(result.hibernate_command));
       }

       if (strcmp (key, "hibernate-enabled") == 0)
       {
       }
    }

    fclose (config_file);
    return result;
}
