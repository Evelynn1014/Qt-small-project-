#include "mainwindow.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
int main(int argc, char *argv[])
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("11111.db");     //如果本目录下没有该文件,则会在本目录下生成,否则连接该文件
    if (!db.open()) {
         cout<<"sss";
           return false;
    }else{
        QSqlQuery query(db);
         cout<<"sss";


//            0西操 100 50 100 一个大操场
//            1思源楼 210 300 100 一栋大教学楼
//            2知行碑 210 200 100 一块碑
//            3学活 30 370 100 学生活动中心
//            4校史馆 140  350 100 交大校史馆
//            5图书馆 420 270 100 交大图书馆是一个图书馆
//            6明湖 330 250 100 明湖是一潭死水
//            7逸夫楼 530 280 100 很大的一栋教学楼
//            8爱知亭 330 200 100 明湖里的一个亭子
//            9南门小树林 210 480 100 荒凉


    }


////    query.exec("INSERT INTO aaa (name, X,Y,time,message) "
////                   "VALUES ('0西操', 100, 50,100, '一个大操场')");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
