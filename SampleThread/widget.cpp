#include "widget.h"

#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    iniUI();
    m_producer = new ThreadProducer;
    m_consumer = new ThreadConsumer;

    iniCon();
}

Widget::~Widget()
{
    m_producer->terminate();
    m_producer->wait();
    m_consumer->terminate();
    m_consumer->wait();
}

void Widget::iniUI()
{
    m_grpBox = new QGroupBox(tr("线程"));

    m_startBtn = new QPushButton(tr("启动线程"));
    m_stopBtn = new QPushButton(tr("结束线程"));
    m_stopBtn->setEnabled(false);
    m_clearBtn = new QPushButton(tr("清空文本"));

    m_msgTextEdit = new QPlainTextEdit;

    m_picLabel = new QLabel;
    m_picLabel->setMinimumSize(QSize(200, 200));
    m_producerStaLabel = new QLabel;
    m_consumerStaLabel = new QLabel;

    QHBoxLayout *hLayoutOne = new QHBoxLayout;
    hLayoutOne->addWidget(m_startBtn);
    hLayoutOne->addWidget(m_stopBtn);
    hLayoutOne->addWidget(m_clearBtn);

    QHBoxLayout *hLayoutTwo = new QHBoxLayout;
    hLayoutTwo->addWidget(m_msgTextEdit);
    hLayoutTwo->addWidget(m_picLabel);

    QHBoxLayout *hLayoutThree = new QHBoxLayout;
    hLayoutThree->addWidget(m_producerStaLabel);
    hLayoutThree->addWidget(m_consumerStaLabel);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayoutOne);
    vLayout->addLayout(hLayoutTwo);
    vLayout->addLayout(hLayoutThree);

    m_grpBox->setLayout(vLayout);

    QHBoxLayout *hLayoutFour = new QHBoxLayout;
    hLayoutFour->addWidget(m_grpBox);

    setLayout(hLayoutFour);

}

void Widget::iniCon()
{
    connect(m_consumer, SIGNAL(newValue(int, int)),
            this, SLOT(onNewValue(int, int)));
    connect(m_startBtn, SIGNAL(clicked()),
            this, SLOT(onStartClick()));
    connect(m_stopBtn, SIGNAL(clicked()),
            this, SLOT(onStopClick()));
    connect(m_clearBtn, SIGNAL(clicked()),
            this, SLOT(onClearClick()));
}

void Widget::onStartClick()
{
    m_consumer->start();
    m_producer->start();

    m_startBtn->setEnabled(false);
    m_stopBtn->setEnabled(true);
    m_producerStaLabel->setText(QString::asprintf("ThreadProducer: Start"));
    m_consumerStaLabel->setText(QString::asprintf("ThreadProducer: Start"));
}

void Widget::onStopClick()
{
    m_producer->terminate();
    m_producer->wait();
    m_consumer->terminate();
    m_consumer->wait();

    m_startBtn->setEnabled(true);
    m_stopBtn->setEnabled(false);

    m_producerStaLabel->setText(QString::asprintf("ThreadProducer: Finish"));
    m_consumerStaLabel->setText(QString::asprintf("ThreadProducer: Finish"));
}

void Widget::onClearClick()
{
    m_msgTextEdit->clear();
}

void Widget::onNewValue(int seq, int diceValue)
{
    QString tmpStr = QString::asprintf("第 %d 次掷骰子， 点数为：%d", seq, diceValue);

    m_msgTextEdit->appendPlainText(tmpStr);

    QString nameStr = QString::asprintf(":/image/images/d%d.jpg", diceValue);
    QPixmap pic;
    pic.load(nameStr);
    m_picLabel->setPixmap(pic);
}

