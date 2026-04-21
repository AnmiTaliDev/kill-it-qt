/*
 * SPDX-FileCopyrightText: AnmiTaliDev <anmitalidev@nuros.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef KILL_IT_WIDGET_HPP
#define KILL_IT_WIDGET_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <memory>
#include "core/parse_config.hpp"
#include "core/power_manager.hpp"

class KillItWidget : public QWidget {
    Q_OBJECT

public:
    explicit KillItWidget(QWidget *parent = nullptr);

private slots:
    void onPoweroffClicked();
    void onRebootClicked();
    void onSuspendClicked();
    void onHibernateClicked();
    void onCancelClicked();

private:
    void setupUI();
    void centerWindow();
    void connectSignals();

    ParseResult config;
    std::unique_ptr<PowerManager> powerManager;
    
    QPushButton *cancelButton;
    QPushButton *poweroffButton;
    QPushButton *rebootButton;
    QPushButton *suspendButton;
    QPushButton *hibernateButton;
    QLabel *titleLabel;
};

#endif // KILL_IT_WIDGET_HPP
