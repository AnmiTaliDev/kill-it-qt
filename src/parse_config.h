#ifndef PARSE_CONFIG_H
#define PARSE_CONFIG_H

#include <string>

struct ParseResult {
    bool poweroff_enabled = true;
    bool suspend_enabled = true;
    bool reboot_enabled = true;
    bool hibernate_enabled = true;

    std::string poweroff_command;
    std::string suspend_command;
    std::string reboot_command;
    std::string hibernate_command;

    bool success_parse = false;
};

ParseResult parseConfig();

#endif // PARSE_CONFIG_H