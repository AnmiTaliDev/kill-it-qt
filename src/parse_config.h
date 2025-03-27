#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

typedef struct 
{
    bool poweroff_enabled;
    bool suspend_enabled;
    bool reboot_enabled;
    bool hibernate_enabled;

    char poweroff_command[256];
    char suspend_command[256];
    char reboot_command[256];
    char hibernate_command[256];

    bool success_parse;
} parse_result;

parse_result parse_config ();

#endif

