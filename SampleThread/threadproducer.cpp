#include "threadproducer.h"

#include <QMutex>
#include <QWaitCondition>
#include <QTime>

QMutex g_mutex;
QWaitCondition g_newdataAvailable;
int g_seq = 0;
int g_diceValue;

ThreadProducer::ThreadProducer()
{

}

ThreadProducer::~ThreadProducer()
{

}

void ThreadProducer::stopThread()
{
    m_stop = true;
}

void ThreadProducer::run()
{
    m_stop = false;
    g_seq = 0;
    qsrand(QTime::currentTime().msec());
    while (!m_stop)
    {
        g_mutex.lock();
        g_diceValue = qrand();
        g_diceValue = (g_diceValue % 6) + 1;
        g_seq++;
        g_mutex.unlock();

        g_newdataAvailable.wakeAll();
        msleep(500);
    }
}
