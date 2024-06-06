#include "threadpool.h"
#include "simpleworkerthread.h"

#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

ThreadPool::ThreadPool(int testCount, int threadCount) :
    QObject(),
    _testCount(testCount)
{
    qDebug() << QString("Will perform %1 iterations with %2 threads").arg(testCount).arg(threadCount);
    for(int i = 0;i < threadCount;i++) {
        SimpleWorkerThread* thread = new SimpleWorkerThread(QString("Thread %1").arg(i + 1));
        connect(thread, &SimpleWorkerThread::finished, this, &ThreadPool::onChildFinished);
        _threads.append(thread);
    }
}

void ThreadPool::start()
{
    QTimer::singleShot(0, this, &ThreadPool::startTestCycle);
}

void ThreadPool::die(const QString& message)
{
    qDebug() << "FATAL: " << message;
    QCoreApplication::quit();
}


void ThreadPool::startTestCycle()
{
    qDebug() << "********** Starting next cycle " << _testCount << " left to go";

    _finishedCount = 0;

    // Start all the threads
    for(SimpleWorkerThread* thread : _threads) {
        if(thread->thread()->isRunning()) {
            // Sanity check.... this never happens
            die("Thread was still running");
        }
        thread->start();
    }
}

void ThreadPool::onChildFinished()
{
    SimpleWorkerThread* thread = static_cast<SimpleWorkerThread*>(sender());
    if(thread->thread()->wait(1000) == false) {
        // Sanity check.... this never happens
        die("Never joined");
    }

    _finishedCount++;
    if(_finishedCount >= _threads.count()) {
        if(--_testCount <= 0) {
            qDebug() << "All cycles complete successfully";
            QCoreApplication::quit();
        }
        else {
            QTimer::singleShot(0, this, &ThreadPool::startTestCycle);
        }
    }
}
