#pragma once

#include <QApplication>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QSoundEffect>
#include <QPixmap>

class LobotomyApp : public QApplication {
    Q_OBJECT
public:
    LobotomyApp(int& argc, char** argv);

private slots:
    void scheduleNextShow();
    void initiateImageSearch();
    void showOnAllScreens(const QPixmap& pixmap);

private:
    QStringList findImageFiles(const QStringList& directories);
    QSystemTrayIcon* trayIcon;
    QTimer* showTimer;
    QSoundEffect* soundEffect;
};
