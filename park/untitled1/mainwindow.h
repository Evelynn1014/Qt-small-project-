#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "car.h"
#include "myQueue.h"
#include <QMainWindow>
#include <QTime>
#include <qtimer.h>
#include<QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    int pks = 10;
    void outpk();
    myQueue qcar;
    int park[10][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},};
    int r1[10] = {4,5,3,6,8,1,2,9,0,7};
    int r2[10] = {4,1,7,8,9,2,6,0,3,5};
    int r3[10] = {7,2,4,6,9,1,3,0,8,5};
    car thecars[100];
    int carnum = 0;
    int x = 100;
    int y = 200;
    int choice = -1;
    void setpksize(int p );
    double getmoney();
    void outputin();
    int qn = 0;
private slots:
    void on_pushButton_clicked();
    void doThings();
     bool pkFull();
     void addAcar();
     void on_pushButton_2_clicked();
     void move11();
     void usein(int p);
     void useout(int p);


     void run();
     void in1();
     void in2();
     void in3();
     void in4();
     void in5();
     void in6();
     void in7();
     void in8();
     void in9();
     void in10();
     void out10();
     void out1();
     void out2();
     void out3();
     void out4();
     void out5();
     void out6();
     void out7();
     void out8();
     void out9();
     void setchoice(int p);
private:
    Ui::MainWindow *ui;
    QPixmap carR = QPixmap("::/carr.png");
    QPixmap carU = QPixmap(":/new/res/car1.png");
    void paintEvent(QPaintEvent *);
};
#endif // MAINWINDOW_H
