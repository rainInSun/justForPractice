#ifndef THREADCONSUMER_H
#define THREADCONSUMER_H

#include <QThread>

class ThreadConsumer : public QThread
{
    Q_OBJECT;

public:
    ThreadConsumer();
    ~ThreadConsumer();

    void stopThread();

protected:
    virtual void run() override;

private:
    bool m_stop = false;

signals:
    void newValue(int seq, int diceValue);
};

#endif // THREADCONSUMER_H
