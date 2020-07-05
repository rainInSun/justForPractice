#include "threadconsumer.h"

#include <QMutex>
#include <QWaitCondition>
#include <QTime>

extern QMutex g_mutex;
extern QWaitCondition g_newdataAvailable;
extern int g_seq;
extern int g_diceValue;

ThreadConsumer::ThreadConsumer()
{

}

ThreadConsumer::~ThreadConsumer()
{

}

void ThreadConsumer::stopThread()
{
    m_stop = true;
}

void ThreadConsumer::run()
{
    m_stop = false;
    while (!m_stop)
    {
        g_mutex.lock();
        g_newdataAvailable.wait(&g_mutex);
        emit newValue(g_seq, g_diceValue);
        g_mutex.unlock();
    }
}
