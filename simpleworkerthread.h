#ifndef SIMPLEWORKERTHREAD_H
#define SIMPLEWORKERTHREAD_H
#include <QObject>
#include <QThread>

class SimpleWorkerThread : public QObject
{
    Q_OBJECT
public:
    SimpleWorkerThread(const QString& name);

    void start();

private:
    QThread _thread;

signals:
    void finished();

private slots:
    void onThreadStarted();
    void onThreadFinished();
};

#endif // SIMPLEWORKERTHREAD_H
