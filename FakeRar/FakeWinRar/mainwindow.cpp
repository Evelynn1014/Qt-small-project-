#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QMessageBox>
#include<QString>
#include<QDebug>
#include<QTime>
#include<QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i =0; i<10; i++){
        processes[i] = NULL;
    }

    process=NULL;
    this->setAcceptDrops(true);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
    z=0;
    if(process==NULL)
        process=new Compression();
    for(int i =0; i<10; i++){
        if(processes[i]==NULL)
            processes[i]=new Compression();
    }

    //接受信号用于进度条
     connect(process,&Compression::mysigals,this,&MainWindow::display);
     for(int i =0; i<10; i++){

         connect(processes[i],&Compression::mysigals,this,&MainWindow::display);
     }

}

MainWindow::~MainWindow()
{
    delete ui;
    process->quit();
    if(process!=NULL)
        delete process;
    for(int i =0; i<10; i++){
        processes[i]->quit();
        if(processes[i]!=NULL)
            delete processes[i];
    }

}

//当用户拖动文件到窗口部件上时候，就会触发dragEnterEvent事件
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    //如果为文件，则支持拖放
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

//当用户放下这个文件后，就会触发dropEvent事件
void MainWindow::dropEvent(QDropEvent *event)
{

    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return;

    //往文本框中追加文件名
    foreach(QUrl url, urls) {
        QString file_name = url.toLocalFile();
        ui->lineEdit->setText(file_name);
        path=file_name;

        QFileInfo info(path);
        qint64 size = info.size();
                 //qint64 转QString
        QString size2 = tr("%1").arg(size);;
        ui->textEdit1->setText(size2);
    }
}

//进度条
void MainWindow::display()
{


        z++;
        ui->progressBar->setValue(z);





}


void MainWindow::on_openButton_clicked()
{   ui->textEdit1->setText("");

    qsl=QFileDialog::getOpenFileNames(this,QString("选择文件"),QString("../.."),"Images (*.png *.xpm *.jpg  *.bmp);;"
                                                                            "Text files (*.txt *.hole);;XML files (*.xml);;"
                                    " (*.*);;");

    qint64 size  = 0;
    QString size2;
    for (int i = 0;i<qsl.size();i++ ) {
        path  = qsl.at(i);
        ui->lineEdit->setText(path);
        QFileInfo info(path);
         size += info.size();
                 //qint64 转QString
        size2 = tr("%1").arg(size);;

    }
    ui->textEdit1->setText(size2);
}

//压缩
void MainWindow::on_codeButton_clicked()
{

       qDebug()<<"1122";
    for (int i = 0;i<qsl.size();i++ ) {
        path  = qsl.at(i);
        ui->progressBar->setValue(0);
        z=0;
        qDebug()<<"1212";
        processes[i]->MYpath=path;
        processes[i]->condition=coding;
        processes[i]->start();
        qDebug()<<"开始压缩";
        path = path + QString(".FakeRar");
    }



}

void MainWindow::on_decodeButton_2_clicked()
{

    QString size2;
 for (int i = 0;i<qsl.size();i++ ) {
     ui->progressBar->setValue(0);
     z=0;
     path  = qsl.at(i);
     processes[i]->condition=decoding;
     processes[i]->MYpath=path;

     processes[i]->start();
     qDebug()<<"开始解压";
     path.erase(path.end()-8, path.end());
 }

}

void MainWindow::on_progressBar_valueChanged(int value)
{

}


void MainWindow::on_pushButton_clicked()
{
    ui->progressBar->setValue(0);
    z=0;
    process->MYpath=path;
    process->condition=coding1;
    process->start();
    qDebug()<<"开始压缩文件夹";
}


void MainWindow::on_pushButton_2_clicked()
{

        ui->progressBar->setValue(0);
        z=0;
        process->condition=decoding1;
        process->MYpath=path;

        process->start();
        qDebug()<<"开始解压";


}


void MainWindow::on_pushButton_3_clicked()
{

    QString pas[10];
    qint64 size = 0;
    QString size2;
    for (int i = 0;i<qsl.size();i++ ) {
       pas[i] = qsl.at(i);


        qDebug()<<pas[i];
       if(pas[i].endsWith(".FakeRar")){
            pas[i].erase(pas[i].end()-8, pas[i].end());
       }else{
            pas[i].append(".FakeRar");
       }
       qDebug()<<pas[i];
       QFileInfo info(pas[i]);
       size += info.size();
       size2 = tr("%1").arg(size);
    }



             //qint64 转QString

    ui->textEdit_2->setText(size2);

    long long int a,b;
    a = ui->textEdit1->toPlainText().toInt();
    b = ui->textEdit_2->toPlainText().toInt();
    double k;
    if (a<=b){
        k = a*100.0000/b;
    }else  {
        k = b*100.0000/a;
    }
    ui->lineEdit_2->setText(QString::number(k, 10, 4) + "%");

}

