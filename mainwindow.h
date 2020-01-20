#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include<QThread>
#include<QDebug>


class MainWindow : public QObject
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void slot_send();
signals:
    void signal_send();
private:
    QTimer time;
    int num ;

};


class thread_class: public QObject
{
    Q_OBJECT
public:
    explicit  thread_class(QObject *obj = nullptr);
    int num;
    volatile bool _block;
public slots:
    void dosomething();
};
#endif // MAINWINDOW_H
