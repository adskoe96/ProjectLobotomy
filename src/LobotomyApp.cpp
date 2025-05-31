#include "LobotomyApp.h"
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QScreen>
#include <QPainter>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QTimer>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>

class OverlayWidget : public QWidget {
    Q_OBJECT
public:
    explicit OverlayWidget(QScreen* screen, const QPixmap& pixmap)
        : QWidget(nullptr), pixmap(pixmap)
    {
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::ToolTip);
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setGeometry(screen->geometry());
        setWindowOpacity(0.0);
    }

    void startAnimation() {
        auto showAnim = new QPropertyAnimation(this, "windowOpacity");
        showAnim->setDuration(1500);
        showAnim->setStartValue(0.0);
        showAnim->setEndValue(1.0);

        auto hideAnim = new QPropertyAnimation(this, "windowOpacity");
        hideAnim->setDuration(1500);
        hideAnim->setStartValue(1.0);
        hideAnim->setEndValue(0.0);

        connect(showAnim, &QPropertyAnimation::finished, [this, hideAnim]() {
            QTimer::singleShot(2000, [hideAnim]() { hideAnim->start(); });
            });

        connect(hideAnim, &QPropertyAnimation::finished, [this]() {
            this->close();
            this->deleteLater();
            });

        showAnim->start();
        this->show();
    }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter painter(this);
        painter.setOpacity(0.6);
        painter.drawPixmap(rect(), pixmap);
    }

private:
    QPixmap pixmap;
};

LobotomyApp::LobotomyApp(int& argc, char** argv)
    : QApplication(argc, argv)
{
    QIcon appIcon(":/icon.png");
    setWindowIcon(appIcon);

    soundEffect = new QSoundEffect(this);
    soundEffect->setSource(QUrl("qrc:/sound.wav"));
    soundEffect->setVolume(0.5f);

    trayIcon = new QSystemTrayIcon(appIcon, this);
    QMenu* menu = new QMenu();
    QAction* quitAction = new QAction("Exit from lobotomy", this);
    connect(quitAction, &QAction::triggered, this, &QApplication::quit);
    menu->addAction(quitAction);
    trayIcon->setContextMenu(menu);
    trayIcon->show();

    showTimer = new QTimer(this);
    connect(showTimer, &QTimer::timeout, this, &LobotomyApp::initiateImageSearch);
    scheduleNextShow();
}

void LobotomyApp::scheduleNextShow() {
    // Random time to show the lobotomy
    int delaySeconds = 30 + QRandomGenerator::global()->bounded(60);
    showTimer->start(delaySeconds * 1000);
}

void LobotomyApp::initiateImageSearch() {
    QStringList directories = {
        // If you want, you can add more directories
        QStandardPaths::writableLocation(QStandardPaths::DownloadLocation),
        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
    };

    QStringList imageFiles = findImageFiles(directories);

    if (!imageFiles.isEmpty()) {
        int index = QRandomGenerator::global()->bounded(imageFiles.size());
        QString imagePath = imageFiles.at(index);
        QPixmap pixmap(imagePath);
        if (!pixmap.isNull()) {
            showOnAllScreens(pixmap);
            soundEffect->stop();
            soundEffect->play();
        }
        else {
            qWarning() << "Failed to load image:" << imagePath;
        }
    }
    else {
        qWarning() << "No images found in the user's directories.";
    }

    scheduleNextShow();
}


void LobotomyApp::showOnAllScreens(const QPixmap& pixmap) {
    for (QScreen* screen : screens()) {
        OverlayWidget* overlay = new OverlayWidget(screen, pixmap);
        overlay->startAnimation();
    }
}

QStringList LobotomyApp::findImageFiles(const QStringList& directories)
{
    QStringList imageFiles;
    QStringList nameFilters = { "*.png", "*.jpg", "*.jpeg", "*.bmp", "*.gif" };

    for (const QString& dirPath : directories) {
        QDir dir(dirPath);
        if (!dir.exists())
            continue;

        QFileInfoList entries = dir.entryInfoList(nameFilters, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDir::Time);
        for (const QFileInfo& fileInfo : entries) {
            imageFiles << fileInfo.absoluteFilePath();
        }

        QFileInfoList subdirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
        for (const QFileInfo& subdirInfo : subdirs) {
            imageFiles.append(findImageFiles({ subdirInfo.absoluteFilePath() }));
        }
    }

    return imageFiles;
}

#include "LobotomyApp.moc"