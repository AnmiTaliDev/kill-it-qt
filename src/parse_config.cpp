#include "parse_config.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

ParseResult parseConfig() {
    ParseResult result;
    
    // Get home directory
    const char* home = std::getenv("HOME");
    if (!home) {
        std::cerr << "Error: HOME environment variable not set" << std::endl;
        result.success_parse = false;
        // Set default commands
        result.suspend_command = "suspend";
        result.reboot_command = "reboot";
        result.hibernate_command = "systemctl hibernate";
        result.poweroff_command = "shutdown now";
        return result;
    }
    
    std::string configPath = std::string(home) + "/.config/kill-it/kill-it.conf";
    std::ifstream configFile(configPath);
    
    if (!configFile.is_open()) {
        std::cout << "Config file not found, using default commands" << std::endl;
        result.success_parse = false;
        // Set default commands
        result.suspend_command = "suspend";
        result.reboot_command = "reboot";
        result.hibernate_command = "systemctl hibernate";
        result.poweroff_command = "shutdown now";
        return result;
    }
    
    std::string line;
    while (std::getline(configFile, line)) {
        // Remove trailing newline and whitespace
        if (!line.empty() && line.back() == '\n') {
            line.pop_back();
        }
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // Find the '=' character
        size_t equalPos = line.find('=');
        if (equalPos == std::string::npos) {
            continue; // Skip lines without '='
        }
        
        // Split into key and value
        std::string key = line.substr(0, equalPos);
        std::string value = line.substr(equalPos + 1);
        
        // Trim whitespace from key and value
        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);
        
        // Parse configuration options
        if (key == "poweroff") {
            result.poweroff_command = value;
        } else if (key == "reboot") {
            result.reboot_command = value;
        } else if (key == "suspend") {
            result.suspend_command = value;
        } else if (key == "hibernate") {
            result.hibernate_command = value;
        } else if (key == "poweroff-enabled") {
            result.poweroff_enabled = (value == "true" || value == "1" || value == "yes");
        } else if (key == "reboot-enabled") {
            result.reboot_enabled = (value == "true" || value == "1" || value == "yes");
        } else if (key == "suspend-enabled") {
            result.suspend_enabled = (value == "true" || value == "1" || value == "yes");
        } else if (key == "hibernate-enabled") {
            result.hibernate_enabled = (value == "true" || value == "1" || value == "yes");
        }
    }
    
    configFile.close();
    result.success_parse = true;
    
    // If commands are empty, set defaults
    if (result.poweroff_command.empty()) {
        result.poweroff_command = "shutdown now";
    }
    if (result.reboot_command.empty()) {
        result.reboot_command = "reboot";
    }
    if (result.suspend_command.empty()) {
        result.suspend_command = "suspend";
    }
    if (result.hibernate_command.empty()) {
        result.hibernate_command = "systemctl hibernate";
    }
    
    return result;
}