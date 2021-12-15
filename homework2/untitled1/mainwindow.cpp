// 刘佳垚 20301107 2021.9.16
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include"Ltodo.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//路径转HTML的函数
void imgPathToHtml(QString &path) {
    path = QString("<img src=\"%1\"/>").arg(path);
}

void MainWindow::on_pushButton_clicked()
{
    Ltodo l ;
    ui->textBrowser_2->setText("");
    ui->textBrowser->setPlainText("");
    int n = ui->lineEdit->text().toInt();
    int m = ui->lineEdit_2->text().toInt();

    ListNode *head = new ListNode();
    ListNode *end ;

    end = head;
    //构建一个链表
    end = l.build(end,n);
    //首尾相连
    end->next = head->next;

    ListNode *temp ;
    temp = head->next;
    //分类讨论，m = 1 为特殊情况
    if(m != 1) {
    for(int i = 1; i < n; i++) {
        temp = l.jump(temp,m);
        //在控制台同时输出
        std::cout << temp->next->num << " ";
        //在ui中插入数字，图片
        ui->textBrowser->insertPlainText( QString::number( temp->next->num));
        QString  imgPath = QString("C:\\Users\\Tooooo\\Desktop\\111\\untitled1\\2.png");
        imgPathToHtml(imgPath);
        ui->textBrowser->insertHtml(imgPath);
         //在ui中插入空格
        ui->textBrowser->insertPlainText("  ");
        fflush(stdout);
        //删除节点
        temp =l.delNode(temp);
    }
    //在ui中插入数字和图片
    ui->textBrowser_2->insertPlainText(QString::number( temp->next->num));
    QString  imgPath = QString("C:\\Users\\Tooooo\\Desktop\\111\\untitled1\\2.png");
    imgPathToHtml(imgPath);
    ui->textBrowser_2->insertHtml(imgPath);
    } else {
        //特殊情况 m = 1
        for(int i = 1; i < n; i++) {
            //在ui中插入数字和图片
            ui->textBrowser->insertPlainText( QString::number( temp->num));
            QString  imgPath = QString("C:\\Users\\Tooooo\\Desktop\\111\\untitled1\\2.png");
            imgPathToHtml(imgPath);
            ui->textBrowser->insertHtml(imgPath);
            ui->textBrowser->insertPlainText(" ");
            temp = temp->next;
        }
        //在ui中插入数字和图片
        ui->textBrowser_2->insertPlainText(QString::number( temp->num));
        QString  imgPath = QString("C:\\Users\\Tooooo\\Desktop\\111\\untitled1\\2.png");
        imgPathToHtml(imgPath);
        ui->textBrowser_2->insertHtml(imgPath);
    }
}




