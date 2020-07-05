#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "threadproducer.h"
#include "threadconsumer.h"

class QGroupBox;
class QPushButton;
class QPlainTextEdit;
class QLabel;


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void iniUI();
    void iniCon();

private:
    QGroupBox *m_grpBox;
    QPushButton *m_startBtn;
    QPushButton *m_stopBtn;
    QPushButton *m_clearBtn;
    QPlainTextEdit *m_msgTextEdit;
    QLabel *m_picLabel;
    QLabel *m_producerStaLabel;
    QLabel *m_consumerStaLabel;

    ThreadProducer *m_producer;
    ThreadConsumer *m_consumer;

private slots:

    void onStartClick();
    void onStopClick();
    void onClearClick();
    void onNewValue(int seq, int diceValue);


};
#endif // WIDGET_H
