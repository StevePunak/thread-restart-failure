#include "simpleworkerthread.h"
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QTimer>

SimpleWorkerThread::SimpleWorkerThread(const QString& name) :
    QObject()
{
    SimpleWorkerThread::setObjectName(name);
    connect(&_thread, &QThread::started, this, &SimpleWorkerThread::onThreadStarted);
    connect(&_thread, &QThread::finished, this, &SimpleWorkerThread::onThreadFinished);
    moveToThread(&_thread);
}

void SimpleWorkerThread::start()
{
    _thread.start();
}

void SimpleWorkerThread::onThreadStarted()
{
    qDebug() << QString("%1 %2 Started").arg(QDateTime::currentDateTimeUtc().toString("yyyy-MM-ddThh:mm:ss.zzzZ")).arg(objectName());

    // I tried introducing a delay, but it fails exactly the same way
    static const int delay = 1000;
    if(delay > 0) {
        QTimer::singleShot(delay, &_thread, &QThread::quit);
    }
    else {
        _thread.quit();
    }
}

void SimpleWorkerThread::onThreadFinished()
{
    qDebug() << QString("%1 %2 Finished").arg(QDateTime::currentDateTimeUtc().toString("yyyy-MM-ddThh:mm:ss.zzzZ")).arg(objectName());
    emit finished();
}
