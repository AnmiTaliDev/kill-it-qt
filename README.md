# Kill It: Power Management App (Qt6 for Linux)

![GitHub License](https://img.shields.io/github/license/AnmiTaliDev/kill-it-qt?style=for-the-badge)
![GitHub Release](https://img.shields.io/github/v/release/AnmiTaliDev/kill-it-qt?style=for-the-badge)
![GitHub commits since latest release](https://img.shields.io/github/commits-since/AnmiTaliDev/kill-it-qt/latest?style=for-the-badge&color=red)

**Kill It** is a simple Qt6 application that allows you to manage your Linux computer's power. It supports the following features:
- Shutdown
- Reboot
- Suspend
- Hibernate

The application works both with and without `systemd`, using commands like `loginctl suspend`, `suspend`, and others. It also supports a configuration file for customizing commands.

## Requirements

To build and run the application, you will need:
- `g++` compiler with C++17 support
- Qt6 library (`qt6-base-dev`)
- `meson` build system
- `ninja` build backend

Install dependencies on Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential qt6-base-dev meson ninja-build
```

Install dependencies on Fedora:
```bash
sudo dnf install gcc-c++ qt6-qtbase-devel meson ninja-build
```

Install dependencies on Arch Linux:
```bash
sudo pacman -S base-devel qt6-base meson ninja
```

## Build and Run
```bash
# Clone the repository:
git clone https://github.com/AnmiTaliDev/kill-it-qt.git
cd kill-it-qt

# Setup build directory:
meson setup builddir

# Build the application:
meson compile -C builddir

# Run the application:
./builddir/kill-it-qt

# Install the application:
sudo meson install -C builddir

# Uninstall the application:
sudo ninja uninstall -C builddir
```

## Usage

After launching the application, you will see an interface with buttons for power management:

- **Shutdown**: Powers off the system.
- **Reboot**: Restarts the computer.
- **Suspend**: Puts the system into sleep mode.
- **Hibernate**: Puts the system into hibernation mode.
- **Cancel**: Closes the application without performing any action.

Select the desired option, and the application will execute the corresponding command and close automatically.

## Supported Commands

The application automatically detects which commands are available on your system:

- **For systems with systemd**: `systemctl poweroff`, `systemctl reboot`, `systemctl suspend`, `systemctl hibernate`.
- **For systems without systemd**: `loginctl suspend`, `loginctl hibernate`, `poweroff`, `reboot`, `suspend`.

## Configuration File

You can customize the commands used by the application via a configuration file:

```
~/.config/kill-it/kill-it.conf
```

Example configuration file:
```ini
# Power management commands
poweroff=systemctl poweroff
reboot=systemctl reboot
suspend=systemctl suspend
hibernate=systemctl hibernate

# Enable/disable buttons (optional)
poweroff-enabled=true
reboot-enabled=true
suspend-enabled=true
hibernate-enabled=false
```

### Configuration Options:

- **Commands**: `poweroff`, `reboot`, `suspend`, `hibernate`
- **Enable/Disable**: `poweroff-enabled`, `reboot-enabled`, `suspend-enabled`, `hibernate-enabled`
- **Values for enable/disable**: `true`/`false`, `1`/`0`, `yes`/`no`
- **Comments**: Lines starting with `#` are ignored

If the configuration file is missing, the application uses default commands and all buttons are enabled.

## Features

- **Modern Qt6 Interface**: Clean and responsive user interface
- **Fast Build System**: Uses Meson for quick compilation
- **Configurable**: Customize commands and button visibility
- **Cross-platform**: Works on any Linux distribution
- **Lightweight**: Minimal dependencies and small footprint
- **Safe**: Confirmation required before executing power commands

## Development

### Project Structure
```
kill-it-qt/
├── src/
│   ├── main.cpp           # Main application and UI
│   ├── parse_config.cpp   # Configuration file parser
│   └── parse_config.h     # Configuration structures
├── meson.build            # Meson build configuration
├── README.md              # This file
├── LICENSE                # GPL v3 license
└── .gitignore            # Git ignore rules
```

### Building for Development
```bash
# Setup debug build
meson setup builddir --buildtype=debug

# Build with verbose output
meson compile -C builddir -v

# Clean build directory
rm -rf builddir
```

## License

This project is licensed under the GNU General Public License v3.0 (GPLv3). See the [LICENSE](LICENSE) file for details.

## Contributing

If you would like to contribute to the project, please:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeatureName`).
3. Commit your changes (`git commit -m 'Add some feature'`).
4. Push your changes (`git push origin feature/YourFeatureName`).
5. Create a Pull Request.

## Issues and Support

If you encounter any issues or have questions:

1. Check the [Issues](https://github.com/AnmiTaliDev/kill-it-qt/issues) page
2. Create a new issue if your problem isn't already reported
3. Provide detailed information about your system and the issue

## Author

**AnmiTaliDev**  
Based on the original GTK version by Jaroslav Mihailenko

## Acknowledgments

- The Qt6 developers for their excellent framework
- The Meson developers for the fast build system
- The Linux community for inspiration and support
- Original GTK version developers

## Changelog

### v1.4
- Ported from GTK4 to Qt6
- Switched from Make to Meson build system
- Improved configuration file parsing
- Added support for enable/disable flags
- Enhanced error handling
- Modern C++17 codebase

---

### Key Features:
1. **Modern**: Built with Qt6 and C++17 for performance and maintainability
2. **Fast**: Meson build system provides quick compilation
3. **Configurable**: Extensive customization through configuration files
4. **Cross-platform**: Works on all major Linux distributions
5. **Lightweight**: Minimal resource usage and dependencies
