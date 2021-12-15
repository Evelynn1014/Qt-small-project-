#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <vex.h>
#include <stack>
#include <queue>
#include "mygraph.h"

//typedef struct point{
//    point(int x,int y){
//        this->x = x;
//        this->y = y;
//    }
//    int x,y;
//}point;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool showG = false;
    Vex vexs[Num];
    int n = 0;
    int matrix[Num*Num] = {0};
    int path[Num] = {0};
    int length = 0;
    stack<point> stk;
    QPixmap pix = QPixmap("c://users//Tooooo//Desktop//Graph(1)//2.png");


    bool findPath = false;
    //Dijkstra
    int S[Num] = {0};
    int D[Num] = {0};
    int DjPath[Num] = {0};
    int DjLength = 0;
    bool findDjPath = false;

    //Kruskal
    int parent[Num] = {0};
    queue<point> que;
    queue<point> pathQue;
    int matrix1[Num*Num] = {0};
    bool findSpanTree = false;
    void Kruskal();
    void sort();
    int Find(int v);
    void Union(int v,int e);
    int getPos(int row,int column);


    void mousePressEvent(QMouseEvent *event);
    void updateD(int temp);
    void updateS(int dex);
    int findminD();
    void lightPath();
    void toStk(int a);
    void insertPath(point p);
    int Dijkstra(int begin,int end);
    void iniVis();
    void DFS(int begin);
    int Dijkstrak (int begin,int end);
    void getMapFromFile(string filename);
    int getPosition(int row,int column);
    void paintEvent(QPaintEvent *);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
