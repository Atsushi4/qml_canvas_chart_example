#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <QtCore/QFileSystemWatcher>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include "qpainterchart.h"

QStringList qmlFiles(const QString &parent)
{
    QStringList files;
    for (auto entry : QDir{parent}.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries)) {
        if (entry.isDir())
            files.append(qmlFiles(entry.absoluteFilePath()));
        else {
            auto targets = QStringList{QStringLiteral("qml"), QStringLiteral("js")};
            auto info = QFileInfo{entry.absoluteFilePath()};
            if (targets.contains(info.suffix()))
                files.append(entry.absoluteFilePath());
        }
    }
    return files;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    // [4]
    qmlRegisterType<QPainterChart>("atsushi.examples", 0, 1, "PainterChart");
    // [1]
    auto relativeQmlDir = app.platformName() == QStringLiteral("windows")
            ? QStringLiteral("/../qml/")
            : QStringLiteral("/qml/");
    auto qmlRoot = app.applicationDirPath() + relativeQmlDir;
    QFileSystemWatcher watcher(qmlFiles(qmlRoot));
    auto reload = [&]{
        QThread::msleep(100);
        qDebug() << "\n\n\nreload";
        view.engine()->clearComponentCache();
        view.setSource(QUrl::fromLocalFile(qmlRoot + QStringLiteral("main.qml")));
        watcher.removePaths(watcher.files());
        watcher.addPaths(qmlFiles(qmlRoot));
    };
    QObject::connect(&watcher, &QFileSystemWatcher::fileChanged,
                     &app, reload, Qt::QueuedConnection);
    // [1]

    reload();
    view.show();
    return app.exec();
}
