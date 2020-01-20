#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTime>

    MainWindow::MainWindow(QWidget *parent) :
        QObject(parent),
        num(0)
    {
        thread_class *object_class = new thread_class;
        QThread *thread = new QThread;
        object_class->moveToThread(thread);
        thread->start();
        connect(&time,&QTimer::timeout,this,&slot_send);
        connect(this,SIGNAL(signal_send()),object_class,SLOT(dosomething()));
        time.start(1000);
    }
    MainWindow::~MainWindow()
    {

    }
    void MainWindow::slot_send()
    {
        if(num++ == 100)  time.stop();
        qDebug()<<"主线程:"<<QThread::currentThreadId();
        emit signal_send();
    }
    thread_class::thread_class(QObject *obj):QObject(obj),
        num(0),
        _block(false)
    {

    }
    void thread_class::dosomething()
    {
            if (_block) return;
            else _block = true;
            qDebug()<<"子线程:"<<QThread::currentThreadId();
            QTimer time;
            time.setSingleShot(true);
            //模拟耗时的操作.
            QEventLoop loop;
            connect(&time,SIGNAL(timeout()),&loop,SLOT(quit()));
            time.start(6000);
            qDebug()<<"阻塞5S中...";
            loop.exec();
            qDebug()<<"阻塞完毕...";
            _block = false;
    }
