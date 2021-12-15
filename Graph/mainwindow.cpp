#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vex.h"
#include <QPixmap>
#include <QWidget>
#include <QPainter>
#include <fstream>
#include <iostream>
#include<QMouseEvent>
#include<QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#define Max 999999
QString j;

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getMapFromFile("c://users//Tooooo//Desktop//Graph(1)//t.txt");

    update();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPen pen = painter.pen();
    pen.setWidth(3);
    QColor color;
    color.setRgb(250,150,50,255);
    pen.setColor(color);
    painter.setPen(pen);
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            if(getPosition(i,j)!=Max){
                if(showG)
                    painter.drawLine(vexs[i].x+15,vexs[i].y+15,vexs[j].x+15,vexs[j].y+15);
            }
        }
    }

    painter.setPen(nullptr);
    for(int i = 0;i<n;i++){
        for(int j = 0;j<i;j++){
            if(getPosition(i,j)!=Max){
//                painter.drawText((vexs[i].x+vexs[j].x+30)/2,
//                                 (vexs[i].y+vexs[j].y+30)/2,
//                                 to_string(getPosition(i,j)).c_str());
            }
        }
    }
    for(int i = 0;i<n;i++){
        painter.drawText(vexs[i].x,vexs[i].y-10,vexs[i].vexName.c_str());
        painter.drawPixmap(vexs[i].x,vexs[i].y,30,30,pix);
    }
    if(findPath){
        pen.setWidth(2);
        color.setRgb(10,100,0,255);
        pen.setColor(color);
        painter.setPen(pen);
        for(int i = 0;i<n-1;i++){
            if(getPosition(path[i],path[i+1])!=Max){
                painter.drawLine(vexs[path[i]].x+15,vexs[path[i]].y+15,vexs[path[i+1]].x+15,vexs[path[i+1]].y+15);

                painter.drawText((vexs[path[i]].x+vexs[path[i+1]].x+30)/2,
                                               (vexs[path[i]].y+vexs[path[i+1]].y+30)/2,
                                               to_string(getPosition(path[i],path[i+1])).c_str());
            }else{
                for(int j = i-1;j>=0;j--){
                    cout<<1<<endl;
                    if(getPosition(path[j],path[i+1])!=Max){
                       cout<<2222<<endl;
                        painter.drawLine(vexs[path[j]].x+15,vexs[path[j]].y+15,vexs[path[i+1]].x+15,vexs[path[i+1]].y+15);
                        painter.drawText((vexs[path[i]].x+vexs[path[j]].x+30)/2,
                                                      (vexs[path[i+1]].y+vexs[path[i+1]].y+30)/2,
                                                       to_string(getPosition(path[j],path[i+1])).c_str());
                        break;
                    }
                }
            }
        }
        findPath = false;
    }
    if(findDjPath){
        pen.setWidth(2);
        color.setRgb(10,100,0,255);
        pen.setColor(color);
        painter.setPen(pen);
        for(int i = 0;i<DjLength-1;i++){
            painter.drawLine(vexs[DjPath[i]].x+15,vexs[DjPath[i]].y+15,vexs[DjPath[i+1]].x+15,vexs[DjPath[i+1]].y+15);
            painter.drawText((vexs[DjPath[i]].x+vexs[DjPath[i+1]].x+30)/2,
                                           (vexs[DjPath[i]].y+vexs[DjPath[i+1]].y+30)/2,
                                           to_string(getPosition(DjPath[i],DjPath[i+1])).c_str());

        }
        findDjPath = false;
    }
    if(findSpanTree){
        pen.setWidth(2);
        color.setRgb(10,100,0,255);
        pen.setColor(color);
        painter.setPen(pen);
        while(!pathQue.empty()){
            point p = pathQue.front();
            pathQue.pop();
            painter.drawLine(vexs[p.x].x+15,vexs[p.x].y+15,vexs[p.y].x+15,vexs[p.y].y+15);
            painter.drawText((vexs[p.x].x+vexs[p.y].x+30)/2,
                                                                  (vexs[p.x].y+vexs[p.y].y+30)/2,
                                                                  to_string(getPosition(p.x,p.y)).c_str());
        }
        findSpanTree = false;
    }
}
void MainWindow::getMapFromFile(string filename){
    ifstream readfile(filename);
    readfile>>n;
    QSqlQuery q ;
    q.exec("SELECT * FROM aaa");
    int i = 0;
    while(q.next()){
        vexs[i].vexName = q.value(0).toString().toStdString();
        vexs[i].x = q.value(1).toInt();
        vexs[i].y= q.value(2).toInt();
        vexs[i].fee= q.value(3).toInt();
        vexs[i].message = q.value(4).toString().toStdString();
        i++;
    }

//    for(int i = 0;i<n;i++){
//        readfile>>vexs[i].vexName;
//        readfile>>vexs[i].x;
//        readfile>>vexs[i].y;
//        readfile>>vexs[i].fee;
//        readfile>>vexs[i].message;
//    }
    int num;
    for(int i = 0;i<n*n;i++){
        matrix[i] = Max;
    }
    for(int i = 0;i<n*n;i++){
        readfile>>num;
        if(num!=0){
            matrix[i] = num;
        }
    }
    readfile.close();
}
int MainWindow::getPosition(int row,int column){
    return matrix[row*n+column];
}
int MainWindow::getPos(int row,int column){
    return matrix1[row*n+column];
}

void MainWindow::DFS(int begin){
ui->pt1->setPlainText("");
    path[0] = begin;

    if(stk.empty())
        toStk(begin);
    while(!stk.empty() && !findPath){
        point p = stk.top();
        stk.pop();
        insertPath(p);
        toStk(p.y);
    }
}
void MainWindow::toStk(int a){

    int x = 0;
    int vis[Num] = {0};
  //  ui->pt1->insertPlainText(QString::number(a));
    for(int i = 0;i<n;i++){
        if(path[i] == a){
            x = i;
            break;
        }
    }
    if(x == n-1){
        for(int i = 0;i<n;i++){
            cout<<path[i]<<" ";
            ui->pt1->insertPlainText(QString::number(path[i]));
            if(i != n-1)
            ui->pt1->insertPlainText("->");

        }
         ui->pt1->insertPlainText("\n");
        int dl[n];
        int all = 0;
        int j = 0;
        if(path[0] == 0)
            j++;
        for (int p = 0; p <n;p++ ) {
            if(path[p+1] == 0)
                j++;
            if(j != 2){
                if(getPosition(path[p],path[p+1])!=Max){
                    dl[p] = getPosition(path[p], path[p+1]);

                    ui->pt1->insertPlainText( QString::number(path[p]));
                    ui->pt1->insertPlainText("->");
                    ui->pt1->insertPlainText( QString::number(path[p+1]));
                    ui->pt1->insertPlainText("  " +QString::number(dl[p] )+ "\n");
                    all +=dl[p];
                }else{
                    for(int j = p-1;j>=0;j--){
                        if(getPosition(path[j],path[p+1])!=Max){
                            dl[p] = getPosition(path[j], path[p+1]);

                            ui->pt1->insertPlainText( QString::number(path[j]));
                            ui->pt1->insertPlainText("->");
                            ui->pt1->insertPlainText( QString::number(path[p+1]));
                            ui->pt1->insertPlainText("  " +QString::number(dl[p] )+ "\n");
                            all +=dl[p];
                        }

                 }
                }
            }

        }
        ui->pt1->insertPlainText("SUM: " +QString::number(all)+ "\n");
        cout<<endl;
        findPath = true;
    }
    for(int i = 0;i<x+1;i++){
        vis[path[i]] = 1;
    }
    bool exe = false;
    for(int i = 0;i<n;i++){
        if(vis[i] == 0 && getPosition(a,i)!=Max){
            exe = true;
            stk.push(point(a,i));

           // if(i != n-1)
          //  ui->pt1->insertPlainText("->");


        }
    }
    if(!exe){
        for(int i = x-1;i>=0 && !exe;i--){
            for(int j = 0;j<n;j++){
                if(getPosition(path[i],j)!=Max && vis[j] == 0){
                    stk.push(point(path[x],j));
                    exe = true;
                    break;
                }
            }
        }
    }
}
void MainWindow::insertPath(point p){
    for(int i = 0;i<n;i++){
        if(path[i] == p.x){
            path[i+1] = p.y;
            break;
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if((ui->lineEdit_3->text() != j)){
            while(!stk.empty()){
                stk.pop();
            }
}

    DFS(atoi(ui->lineEdit_3->text().toStdString().c_str()));
            j = ui->lineEdit_3->text();
    update();
}

int MainWindow::Dijkstra(int begin,int end){
    int temp = begin;
    int preEnd;
    int node = begin;
    memset(S,-1,sizeof(S));
    memset(D,-1,sizeof(D));
    S[begin] = 0;
    for(int i = 0;i<n;i++){
        if(S[i]==-1){
            D[i] = getPosition(begin,i);
        }
    }
    while(S[end]==-1){
        preEnd = D[end];
        updateD(temp);
        if(preEnd>D[end]){
            node = temp;
        }
        temp = findminD();
        updateS(temp);
    }
    return node;
}
void MainWindow::updateD(int temp){
    for(int i = 0;i<n;i++){
        if(S[i] == -1 && S[temp]+getPosition(temp,i) < D[i]){
            D[i] = S[temp]+getPosition(temp,i);
        }
    }
}
void MainWindow::updateS(int dex){
    S[dex] = D[dex];
    D[dex] = -1;
}
int MainWindow::findminD(){
    int min = Max;
    int minDex = 0;
    for(int i = 0;i<n;i++){
        if(D[i]!=-1 && D[i]<min){
            min = D[i];
            minDex = i;
        }
    }
    return minDex;
}

void MainWindow::on_pushButton_3_clicked()
{   ui->pt1->setPlainText("");

    int begin = atoi(ui->lineEdit->text().toStdString().c_str());
    int end = atoi(ui->lineEdit_2->text().toStdString().c_str());
    if(begin == end){
        QMessageBox::about(NULL,"WARNING","====WRONG====");
        return;
    }
    DjLength = 0;
    DjPath[DjLength] = end;DjLength++;
    int k = Dijkstra(begin,end);
    ui->lineEdit_4->setText(QString::number(S[end]));
    DjPath[DjLength] = k;DjLength++;
    while(k!=begin){
        k = Dijkstra(begin,k);
        DjPath[DjLength] = k;DjLength++;
    }
    int dl[DjLength];
    int all = 0;
    for (int p = 0; p <DjLength-1;p++ ) {
        dl[p] = getPosition(DjPath[p], DjPath[p+1]);
        ui->pt1->insertPlainText( QString::number(DjPath[p]));
        ui->pt1->insertPlainText("->");
        ui->pt1->insertPlainText( QString::number(DjPath[p+1]));
        ui->pt1->insertPlainText("  " +QString::number(dl[p] )+ "\n");
        all +=dl[p];
    }
    ui->pt1->insertPlainText("SUM: " +QString::number(all)+ "\n");
    findDjPath = true;
    update();
}
void MainWindow::Kruskal(){
    sort();
    for(int i = 0;i<n;i++){
        parent[i] = i;
    }
    while(!que.empty()){
        point p = que.front();
        que.pop();
        Union(p.x,p.y);
    }
}
void MainWindow::sort(){
    bool change = true;
    for(int i = 0;i<n*n;i++){
        matrix1[i] = matrix[i];
    }
    int min = Max;
    point p(0,0);
    while(change){
        change = false;
        min = Max;
        for(int i = 0;i<n;i++){
            for(int j = 0;j<i;j++){
                if(getPos(i,j)<min){
                    change = true;
                    min = getPos(i,j);
                    p.x = i;
                    p.y = j;
                }
            }
        }
        if(change){
            matrix1[p.x * n+p.y] = Max;
            que.push(p);
        }
    }
}
int MainWindow::Find(int v){
    while(parent[v] != v) {
            v = parent[v];
        }
        return v;
}
void MainWindow::Union(int s, int e){
    int sRoot = Find(s);
        int eRoot = Find(e);
        if(sRoot != eRoot) {
            parent[sRoot] = eRoot;
            pathQue.push(point(s,e));
        }
}

void MainWindow::on_pushButton_4_clicked()
{
    Kruskal();
    findSpanTree = true;
    update();
}


void MainWindow::on_pushButton_clicked()
{
    if(showG == true)
        showG = false;
    else
        showG = true;
    update();
}
void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        int x = event->x();
        int y = event->y();
        for(int i = 0;i<n;i++){
            if(x>vexs[i].x && x<vexs[i].x+30 && y>vexs[i].y && y<vexs[i].y+30){
                QMessageBox::about(NULL,"Position","Name: "+QString::fromStdString(vexs[i].vexName)+'\n'+
                                                  // "Fee: "+QString::number(vexs[i].fee)+'\n'+
                                                   "Message: "+QString::fromStdString(vexs[i].message));
                break;
            }
        }
    }
}

void MainWindow::on_pushButton_5_clicked()
{ui->pt1->setPlainText("");
     int be = atoi(ui->lineEdit->text().toStdString().c_str());
     int n = 0;

     for (int p = 0;p<Num ;p++ ) {
         if(p != be){
             if(getPosition(be,p) != Max){
                 n++;
             }
         }
     }
    int numbers[n];
    int l = 0;
    for (int p = 0;p<Num ;p++ ) {
        if(p != be){
            if(getPosition(be,p) != Max){
                numbers[l] = p;
                l++;
            }
        }
    }
    int ju = 0;
    for (int u = 0;u< n ;u++ ) {
      //
        int begin = numbers[u];
        int end = atoi(ui->lineEdit_2->text().toStdString().c_str());
        if(begin == end){
            break;
        }
        DjLength = 0;
        DjPath[DjLength] = end;DjLength++;
        int k = Dijkstra(begin,end);
        DjPath[DjLength] = k;DjLength++;
        while(k!=begin){
            k = Dijkstra(begin,k);
            DjPath[DjLength] = k;DjLength++;
        }
        int dl[DjLength];
        int all = 0;
        for (int p = 0; p <DjLength;p++ ) {
            if(DjPath[p] == be){
                ju = 1;
            }
        }
        if(ju == 1) break;
        for (int p = 0; p <DjLength-1;p++ ) {
            dl[p] = getPosition(DjPath[p], DjPath[p+1]);
            ui->pt1->insertPlainText( QString::number(DjPath[p]));
            ui->pt1->insertPlainText("->");
            ui->pt1->insertPlainText( QString::number(DjPath[p+1]));
            ui->pt1->insertPlainText("  " +QString::number(dl[p] )+ "\n");
            all +=dl[p];
        }
        ui->pt1->insertPlainText( QString::number(begin));

        ui->pt1->insertPlainText("->");
        ui->pt1->insertPlainText( QString::number(be));
        ui->pt1->insertPlainText("  " +QString::number(getPosition(be,begin) )+ "\n");

        ui->pt1->insertPlainText("SUM: " + QString::number(all + getPosition(be,begin))+ "\n");
        findDjPath = true;


    }//update();

}

int MainWindow::Dijkstrak (int begin,int end){
    int temp = begin;
    int preEnd;
    int node = begin;
    memset(S,-1,sizeof(S));
    memset(D,-1,sizeof(D));
    S[begin] = 0;
    for(int i = 0;i<n;i++){
        if(S[i]==-1){
            D[i] = getPosition(begin,i);
        }
    }
    while(S[end]==-1){
        preEnd = D[end];
        updateD(temp);
        if(preEnd>D[end]){
            node = temp;
        }
        temp = findminD();
        updateS(temp);
    }
    return node;
}
