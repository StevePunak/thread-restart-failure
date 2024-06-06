#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <QObject>

class SimpleWorkerThread;
class ThreadPool : public QObject
{
    Q_OBJECT
public:
    ThreadPool(int testCount, int threadCount);

    void start();

private:
    void die(const QString& message);

    int _testCount;
    int _finishedCount;

    QList<SimpleWorkerThread*> _threads;

private slots:
    void startTestCycle();
    void onChildFinished();
};

#endif // THREADPOOL_H
