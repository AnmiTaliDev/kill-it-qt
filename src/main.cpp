#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QProcess>
#include <QMessageBox>
#include <QScreen>
#include <iostream>
#include "parse_config.h"

class KillItWidget : public QWidget {
    Q_OBJECT

public:
    KillItWidget(QWidget *parent = nullptr) : QWidget(parent) {
        config = parseConfig();
        setupUI();
        connectSignals();
        applyStyles();
    }

private slots:
    void onPoweroffClicked() {
        executeCommand(config.poweroff_command);
        close();
    }
    
    void onRebootClicked() {
        executeCommand(config.reboot_command);
        close();
    }
    
    void onSuspendClicked() {
        executeCommand(config.suspend_command);
        close();
    }
    
    void onHibernateClicked() {
        executeCommand(config.hibernate_command);
        close();
    }
    
    void onCancelClicked() {
        close();
    }

private:
    void setupUI() {
        setWindowTitle("Kill It - Power Management");
        setFixedSize(420, 160);
        
        // Center window on screen
        centerWindow();
        
        // Create layouts
        auto *mainLayout = new QVBoxLayout(this);
        auto *headerLayout = new QVBoxLayout();
        auto *buttonLayout = new QHBoxLayout();
        auto *footerLayout = new QHBoxLayout();
        
        // Create title label
        titleLabel = new QLabel("Kill It", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setObjectName("titleLabel");
        
        // Create subtitle label
        subtitleLabel = new QLabel("Power Management v1.4", this);
        subtitleLabel->setAlignment(Qt::AlignCenter);
        subtitleLabel->setObjectName("subtitleLabel");
        
        // Create buttons with icons
        cancelButton = new QPushButton("✕  Cancel", this);
        poweroffButton = new QPushButton("⏻  Shutdown", this);
        rebootButton = new QPushButton("⟲  Restart", this);
        suspendButton = new QPushButton("⏸  Sleep", this);
        hibernateButton = new QPushButton("❄  Hibernate", this);
        
        // Set object names for styling
        cancelButton->setObjectName("cancelButton");
        poweroffButton->setObjectName("poweroffButton");
        rebootButton->setObjectName("rebootButton");
        suspendButton->setObjectName("suspendButton");
        hibernateButton->setObjectName("hibernateButton");
        
        // Set button sizes
        QSize buttonSize(90, 35);
        cancelButton->setFixedSize(buttonSize);
        poweroffButton->setFixedSize(buttonSize);
        rebootButton->setFixedSize(buttonSize);
        suspendButton->setFixedSize(buttonSize);
        hibernateButton->setFixedSize(buttonSize);
        
        // Add buttons to layout based on config
        buttonLayout->addStretch();
        
        if (config.suspend_enabled) {
            buttonLayout->addWidget(suspendButton);
            buttonLayout->addSpacing(8);
        }
        
        if (config.hibernate_enabled) {
            buttonLayout->addWidget(hibernateButton);
            buttonLayout->addSpacing(8);
        }
        
        if (config.reboot_enabled) {
            buttonLayout->addWidget(rebootButton);
            buttonLayout->addSpacing(8);
        }
        
        if (config.poweroff_enabled) {
            buttonLayout->addWidget(poweroffButton);
        }
        
        buttonLayout->addStretch();
        
        // Footer with cancel button
        footerLayout->addStretch();
        footerLayout->addWidget(cancelButton);
        footerLayout->addStretch();
        
        // Header layout
        headerLayout->addWidget(titleLabel);
        headerLayout->addWidget(subtitleLabel);
        headerLayout->addSpacing(15);
        
        // Main layout
        mainLayout->addLayout(headerLayout);
        mainLayout->addLayout(buttonLayout);
        mainLayout->addSpacing(10);
        mainLayout->addLayout(footerLayout);
        
        // Set margins
        mainLayout->setContentsMargins(20, 15, 20, 15);
    }
    
    void centerWindow() {
        QScreen *screen = QApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;
        move(x, y);
    }
    
    void applyStyles() {
        QString styleSheet = R"(
            QWidget {
                background-color: #f5f5f5;
                color: #333;
            }
            
            #titleLabel {
                color: #2c3e50;
                font-size: 20px;
                font-weight: bold;
                margin-bottom: 2px;
            }
            
            #subtitleLabel {
                color: #7f8c8d;
                font-size: 12px;
                margin-bottom: 5px;
            }
            
            QPushButton {
                background-color: #ecf0f1;
                border: 1px solid #bdc3c7;
                border-radius: 6px;
                color: #2c3e50;
                font-size: 11px;
                font-weight: bold;
                padding: 6px 8px;
            }
            
            QPushButton:hover {
                background-color: #d5dbdb;
                border: 1px solid #a2a8a8;
            }
            
            QPushButton:pressed {
                background-color: #bdc3c7;
            }
            
            #poweroffButton {
                background-color: #e74c3c;
                border: 1px solid #c0392b;
                color: white;
            }
            
            #poweroffButton:hover {
                background-color: #ec7063;
                border: 1px solid #e74c3c;
            }
            
            #poweroffButton:pressed {
                background-color: #c0392b;
            }
            
            #rebootButton {
                background-color: #f39c12;
                border: 1px solid #d68910;
                color: white;
            }
            
            #rebootButton:hover {
                background-color: #f5b041;
                border: 1px solid #f39c12;
            }
            
            #rebootButton:pressed {
                background-color: #d68910;
            }
            
            #suspendButton {
                background-color: #9b59b6;
                border: 1px solid #8e44ad;
                color: white;
            }
            
            #suspendButton:hover {
                background-color: #af7ac5;
                border: 1px solid #9b59b6;
            }
            
            #suspendButton:pressed {
                background-color: #8e44ad;
            }
            
            #hibernateButton {
                background-color: #1abc9c;
                border: 1px solid #16a085;
                color: white;
            }
            
            #hibernateButton:hover {
                background-color: #48c9b0;
                border: 1px solid #1abc9c;
            }
            
            #hibernateButton:pressed {
                background-color: #16a085;
            }
            
            #cancelButton {
                background-color: #95a5a6;
                border: 1px solid #7f8c8d;
                color: white;
                font-size: 10px;
            }
            
            #cancelButton:hover {
                background-color: #a9b9ba;
                border: 1px solid #95a5a6;
            }
            
            #cancelButton:pressed {
                background-color: #7f8c8d;
            }
        )";
        
        setStyleSheet(styleSheet);
    }
    
    void connectSignals() {
        connect(cancelButton, &QPushButton::clicked, this, &KillItWidget::onCancelClicked);
        connect(poweroffButton, &QPushButton::clicked, this, &KillItWidget::onPoweroffClicked);
        connect(rebootButton, &QPushButton::clicked, this, &KillItWidget::onRebootClicked);
        connect(suspendButton, &QPushButton::clicked, this, &KillItWidget::onSuspendClicked);
        connect(hibernateButton, &QPushButton::clicked, this, &KillItWidget::onHibernateClicked);
    }
    
    void executeCommand(const std::string& command) {
        if (command.empty()) {
            QMessageBox::warning(this, "Error", "Command not configured");
            return;
        }
        
        QProcess process;
        process.startDetached(QString::fromStdString(command));
    }
    
    ParseResult config;
    QPushButton *cancelButton;
    QPushButton *poweroffButton;
    QPushButton *rebootButton;
    QPushButton *suspendButton;
    QPushButton *hibernateButton;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Kill It");
    app.setApplicationVersion("1.4");
    app.setOrganizationName("AnmiTaliDev");
    
    KillItWidget widget;
    widget.show();
    
    return app.exec();
}

#include "main.moc"