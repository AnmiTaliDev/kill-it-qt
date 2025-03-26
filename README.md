# Kill It: Power Management App (GTK4 for Linux)

![GitHub License](https://img.shields.io/github/license/ruzen42/kill-it-gtk?style=for-the-badge)
![GitHub Release](https://img.shields.io/github/v/release/ruzen42/kill-it-gtk?style=for-the-badge)
![GitHub commits since latest release](https://img.shields.io/github/commits-since/ruzen42/kill-it-gtk/latest?style=for-the-badge&color=red)

**Kill It** is a simple GTK4 application that allows you to manage your Linux computer's power. It supports the following features:
- Shutdown
- Reboot
- Suspend
- Hibernate

The application works both with and without `systemd`, using commands like `loginctl suspend`, `suspend`, and others. It also supports a configuration file for customizing commands.

## Requirements

To build and run the application, you will need:
- `gcc` compiler
- GTK4 library (`libgtk-4-dev`)
- `make` utility

Install dependencies on Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential libgtk-4-dev make
```
Build and Run
``` Bash
# Clone the repository:

git clone https://github.com/ruzen42/kill-it-gtk.git
cd kill-it

# Build the application:

make

# Run the application:

./main

# Build a AppImage

make appimage
```
Usage

After launching the application, you will see an interface with buttons for power management:

    Shutdown: Powers off the system.

    Reboot: Restarts the computer.

    Suspend: Puts the system into sleep mode.

    Hibernate: Puts the system into hibernation mode.

Select the desired option, and the application will execute the corresponding command.
Supported Commands

The application automatically detects which commands are available on your system:

    For systems with systemd: systemctl poweroff, systemctl reboot, systemctl suspend, systemctl hibernate.

    For systems without systemd: loginctl suspend, loginctl hibernate, poweroff, reboot, suspend.

Configuration File

You can customize the commands used by the application via a configuration file:
bash
Copy

~/.config/kill-it/kill-it.conf

Example configuration file:
ini
Copy

poweroff=poweroff
reboot=reboot
suspend=loginctl suspend
hibernate=loginctl hibernate

If the configuration file is missing, the application uses default commands.
License

This project is licensed under the GNU General Public License v3.0 (GPLv3). See the LICENSE file for details.
Contributing

If you would like to contribute to the project, please:

    Fork the repository.

    Create a new branch (git checkout -b feature/YourFeatureName).

    Commit your changes (git commit -m 'Add some feature').

    Push your changes (git push origin feature/YourFeatureName).

    Create a Pull Request.

Author

Jaroslav Mihailenko
linuxmalledefer@gmail.com
Acknowledgments

    The GTK4 developers for their excellent library.

    The Linux community for inspiration and support.

---

### Key Features:
1. **Cross-platform**: Works on Linux systems with or without `systemd`.
2. **Customizable**: Commands can be configured via a simple configuration file.
3. **Lightweight**: Built with GTK4 for a modern and responsive UI.

This `README.md` is ready to be used in your project. Let me know if you need further adjustments! 😊
