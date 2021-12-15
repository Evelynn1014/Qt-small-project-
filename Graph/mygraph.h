#ifndef MYGRAPH_H
#define MYGRAPH_H
#include <QMainWindow>
#include <QWidget>
#include <vex.h>
#include <stack>
#include <queue>
#include <fstream>
#define Num 10
#define Max 999999
typedef struct point{
    point(int x,int y){
        this->x = x;
        this->y = y;
    }
    int x,y;
}point;
class mygraph
{
public:
    mygraph();
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

    void getMapFromFile(string filename);
    int getPosition(int row,int column);
};

#endif // MYGRAPH_H
