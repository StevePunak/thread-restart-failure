#include "threadpool.h"

#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ThreadPool test(500, 10);
    test.start();
    a.exec();
    return 0;
}
