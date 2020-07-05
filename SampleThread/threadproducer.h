#ifndef THREADPRODUCER_H
#define THREADPRODUCER_H

#include <QThread>

class ThreadProducer : public QThread
{
    Q_OBJECT

public:
    ThreadProducer();
    ~ThreadProducer();

    void stopThread();

protected:
    virtual void run() override;

private:
    bool m_stop = false;
};

#endif // THREADPRODUCER_H
