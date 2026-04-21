/*
 * SPDX-FileCopyrightText: AnmiTaliDev <anmitalidev@nuros.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "kill_it_widget.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScreen>
#include <QApplication>

KillItWidget::KillItWidget(QWidget *parent) : QWidget(parent) {
    config = parseConfig();
    powerManager = std::make_unique<PowerManager>(config);
    setupUI();
    connectSignals();
}

void KillItWidget::onPoweroffClicked() {
    powerManager->shutdown();
    close();
}

void KillItWidget::onRebootClicked() {
    powerManager->restart();
    close();
}

void KillItWidget::onSuspendClicked() {
    powerManager->suspend();
    close();
}

void KillItWidget::onHibernateClicked() {
    powerManager->hibernate();
    close();
}

void KillItWidget::onCancelClicked() {
    close();
}

void KillItWidget::setupUI() {
    setWindowTitle("Kill It");
    
    centerWindow();
    
    auto *mainLayout = new QVBoxLayout(this);
    auto *headerLayout = new QVBoxLayout();
    auto *buttonLayout = new QHBoxLayout();
    auto *footerLayout = new QHBoxLayout();
    titleLabel = new QLabel("Kill It", this);
    titleLabel->setAlignment(Qt::AlignCenter);

    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleLabel->setFont(titleFont);

    cancelButton = new QPushButton("Cancel", this);

    poweroffButton = new QPushButton("Shutdown", this);
    rebootButton = new QPushButton("Restart", this);
    suspendButton = new QPushButton("Sleep", this);
    hibernateButton = new QPushButton("Hibernate", this);
    
    buttonLayout->addStretch();
    
    if (config.suspend_enabled) {
        buttonLayout->addWidget(suspendButton);
    }
    
    if (config.hibernate_enabled) {
        buttonLayout->addWidget(hibernateButton);
    }
    
    if (config.reboot_enabled) {
        buttonLayout->addWidget(rebootButton);
    }
    
    if (config.poweroff_enabled) {
        buttonLayout->addWidget(poweroffButton);
    }
    
    buttonLayout->addStretch();
    
    footerLayout->addStretch();
    footerLayout->addWidget(cancelButton);
    footerLayout->addStretch();
    
    headerLayout->addWidget(titleLabel);
    headerLayout->addSpacing(10);
    
    mainLayout->addLayout(headerLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(footerLayout);
}

void KillItWidget::centerWindow() {
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void KillItWidget::connectSignals() {
    connect(cancelButton, &QPushButton::clicked, this, &KillItWidget::onCancelClicked);
    connect(poweroffButton, &QPushButton::clicked, this, &KillItWidget::onPoweroffClicked);
    connect(rebootButton, &QPushButton::clicked, this, &KillItWidget::onRebootClicked);
    connect(suspendButton, &QPushButton::clicked, this, &KillItWidget::onSuspendClicked);
    connect(hibernateButton, &QPushButton::clicked, this, &KillItWidget::onHibernateClicked);
}
