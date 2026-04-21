/*
 * SPDX-FileCopyrightText: AnmiTaliDev <anmitalidev@nuros.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <QApplication>
#include "kill_it_widget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Kill It");
    app.setApplicationVersion("1.4");
    app.setOrganizationName("AnmiTaliDev");
    
    KillItWidget widget;
    widget.show();
    
    return app.exec();
}
