#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myQueue.h"
#include <QPainter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QTimer *timer = new QTimer;
    connect( timer, SIGNAL(timeout()),SLOT(run()));

    timer->start(20);
    ui->car1->setVisible(false);
    ui->car1_2->setVisible(false);
    ui->car1_3->setVisible(false);
    ui->car1_4->setVisible(false);
    ui->car1_5->setVisible(false);
    ui->car1_6->setVisible(false);
    ui->car1_7->setVisible(false);
    ui->car1_8->setVisible(false);
    ui->car1_9->setVisible(false);
    ui->car1_10->setVisible(false);
    ui->car1_11->setVisible(false);
    ui->car1_12->setVisible(false);
    ui->car1_13->setVisible(false);
    ui->car1_14->setVisible(false);
    ui->car1_15->setVisible(false);
    ui->car1_16->setVisible(false);
    ui->car1_17->setVisible(false);
    ui->car1_18->setVisible(false);
    ui->car1_19->setVisible(false);
    ui->car1_20->setVisible(false);
    ui->car1_21->setVisible(false);
    ui->car1_22->setVisible(false);

    ui->carr_2->setVisible(false);
    ui->carr_3->setVisible(false);
    ui->carr_4->setVisible(false);
    ui->carr_5->setVisible(false);
    ui->carr_6->setVisible(false);
    ui->carr_7->setVisible(false);
    ui->carr_8->setVisible(false);
    ui->carr_9->setVisible(false);
    ui->carr_10->setVisible(false);
    ui->carr_11->setVisible(false);
    ui->carr_12->setVisible(false);
    ui->carr_13->setVisible(false);

}


MainWindow::~MainWindow()
{
    delete ui;
}

int  rnumber()
{
    srand((int)time(nullptr));  // 产生随机种子  把0换成NULL也行

    return rand()%3;
}

bool MainWindow::pkFull(){
    int i = 0;

    for(int j = 0; j<= 9;j++){
        if(park[j][0] != 0 ){
            i++;
        }
    }

    if (i == pks) return true;
    return false;
}

void MainWindow::setchoice(int p){
    choice = p;
}

void MainWindow::outputin(){
    int i = 0;
    for(int j = 0; j<= 9;j++){
        if(park[j][0] != 0 ){
            i++;
        }
    }

    ui->inpk->setText( " 空车位 "+ QString::number(pks-i,10,2)+"\n");
    if(qcar.isEmpty()){
      ui->inpk->insertPlainText(" 队列空 \n");
    }else if(qn >= qcar.size){
         ui->inpk->insertPlainText(" 队列满 \n");
    }else{
    ui->inpk->insertPlainText( " 正在排队的车数： "+ QString::number(qcar.size-qn,10,0)+"\n");
}




}
void MainWindow::addAcar(){

    if(pkFull()){
        if(qcar.isFull()){
            ui->pretext->insertPlainText("queue is full， the car go away\n");
        }else{
            car newcar;
            qcar.enQueue(newcar);
             qn++;
            thecars[carnum] = newcar;
            carnum++;
            ui->pretext->insertPlainText(QString::fromStdString(newcar.msg1()));
        }
    }else{
        move11();
        car newcar;
        int k = 0;
        int ju = newcar.cartime%3;
        for(int i = 0; k == 0;i++){
            if (ju == 0){

             if (park[r1[i]][0] == 0){
                  newcar.setPk(r1[i]);
                  park[newcar.pk][0]  = carnum+1;
                  setchoice(newcar.pk);
                  k = 1;

                    cout<<newcar.pk;
              }
            }else if(ju == 1){

                if (park[r2[i]][0] == 0){
                    newcar.setPk(r2[i])  ;
                    park[newcar.pk][0] = carnum+1;
                    k = 1;

                    cout<<newcar.pk;
                }

            }else if(ju == 2){
                if (park[r3[i]][0] == 0){
                    newcar.setPk(r3[i]);
                    park[newcar.pk][0] = carnum+1;
                    k = 1;

                    cout<<newcar.pk;
                }
            }
        }
        usein(newcar.pk);
        thecars[carnum] = newcar;
        carnum++;


        ui->pretext->insertPlainText(QString::fromStdString(newcar.msg2()));
    }

    outputin();
}

void MainWindow::doThings(){

   outpk();

    if(!qcar.isEmpty()){
        if(!pkFull()){
            car newcar = qcar.deQueue();
            qn--;
            int k = 0;
            int ju = newcar.cartime%3;
            cout<<newcar.cartime<<endl;
            cout<<ju<<endl;
            for(int i = 0; k == 0;i++){
                if (ju == 0){

                 if (park[r1[i]][0] == 0){
                      newcar.setPk(r1[i]);
                      park[newcar.pk][0]  = carnum+1;
                      k = 1;
                        cout<<newcar.pk;
                  }
                }else if(ju == 1){

                    if (park[r2[i]][0] == 0){
                        newcar.setPk(r2[i])  ;
                        park[newcar.pk][0] = carnum+1;
                        k = 1;
                    }

                }else if(ju == 2){
                    if (park[r3[i]][0] == 0){
                        newcar.setPk(r3[i]);
                        park[newcar.pk][0] = carnum+1;
                        k = 1;
                    }
                }
            }
            thecars[carnum] = newcar;
            carnum++;
            usein(newcar.pk);
            ui->pretext->insertPlainText(QString::fromStdString(newcar.msg2()));
        }

    }
    outputin();
}

void MainWindow::outpk(){
    time_t nowt = clock();
    for(int i = 0; i<=9; i++) {
        if(park[i][0] == 0){
        }else if(park[i][0] != 0){
           if(nowt - thecars[park[i][0]-1].starttime >= thecars[park[i][0]-1].cartime){
               ui->fintext->insertPlainText(QString::fromStdString(thecars[park[i][0]-1].msg3()));
               useout(thecars[park[i][0]-1].pk);
               park[i][0] = 0;
           }
        }
    }
outputin();
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit_2->text() != nullptr){
        qcar.setQusize(ui->lineEdit_2->text().toInt());
    }
    (ui->lineEdit_2->setEnabled(false));
    if(ui->lineEdit->text() != nullptr){
        if(1<= ui->lineEdit->text().toInt() && ui->lineEdit->text().toInt()<=10)
        setpksize(ui->lineEdit->text().toInt());
    }
    (ui->lineEdit->setEnabled(false));

   addAcar();
}
void MainWindow::setpksize(int p){
    this->pks = p;
}

void MainWindow::move11(){

//    cout<<"sdasdsaadas"<<endl;
//    ui->car1->show();
//    ui->car1->setVisible(true);
//    QPropertyAnimation animation(ui->car1, "geometry");
//    animation.setDuration(1000);
//    for(int i = 1; i <= 100 ;i++){

//    ui->car1->setGeometry(0, i, ui->car1->width(),  ui->car1->height());
//    }

////    animation.setStartValue(QRect(0, 0, ui->car1->width(),  ui->car1->height()));

////    animation.setEndValue(QRect(0, 20, ui->car1->width(),  ui->car1->height()));
////    animation.start();
}

void MainWindow::on_pushButton_2_clicked()
{
   ui->sales->setText(QString::number(this->getmoney(),10,2));
}

void MainWindow::paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.drawPixmap(x,y,carR.width(),carR.height(),carR);
}

void MainWindow::usein(int p){
    if(p == 0){
        in1();


    }else if(p == 1){
        in2();
    }else if(p == 2){
        in3();
    }else if(p == 3){
        in4();
    }else if(p == 4){
        in5();
    }else if(p == 5){
        in6();
    }else if(p == 6){
        in7();
    }else if(p == 7){
        in8();
    }else if(p == 8){
        in9();
    }else if(p == 9){
        in10();
    }
}
void MainWindow::useout(int p){
    if(p == 0){
        out1();

    }else if(p == 1){
        out2();
    }else if(p == 2){
        out3();
    }else if(p == 3){
        out4();
    }else if(p == 4){
        out5();
    }else if(p == 5){
        out6();
    }else if(p == 6){
        out7();
    }else if(p == 7){
        out8();
    }else if(p == 8){
        out9();
    }else if(p == 9){
        out10();
    }
}

void MainWindow::run(){
    doThings();
}

void MainWindow::in1(){
     ui->car1->show();
}

void MainWindow::in2(){
     ui->car1_2->show();
}
void MainWindow::in3(){
    ui->car1_3->show();
}
void MainWindow::in4(){
    ui->car1_4->show();
}
void MainWindow::in5(){
    ui->car1_5->show();
}
void MainWindow::in6(){
ui->car1_6->show();
}
void MainWindow::in7(){
ui->car1_7->show();
}
void MainWindow::in8(){
    ui->car1_8->show();
}
void MainWindow::in9(){
    ui->car1_9->show();
}
void MainWindow::in10(){
    ui->car1_10->show();
}

void MainWindow::out1(){
     ui->car1->hide();
}
void MainWindow::out2(){
    ui->car1_2->hide();
}
void MainWindow::out3(){
     ui->car1_3->hide();
}
void MainWindow::out4(){
 ui->car1_4->hide();
}
void MainWindow::out5(){
     ui->car1_5->hide();
}
void MainWindow::out6(){
     ui->car1_6->hide();
}
void MainWindow::out7(){
     ui->car1_7->hide();
}
void MainWindow::out8(){
     ui->car1_8->hide();
}
void MainWindow::out9(){
     ui->car1_9->hide();
}
void MainWindow::out10()
 {ui->car1_10->hide();
}
double MainWindow::getmoney(){
    ifstream infile;   //输入流
    ofstream outfile;   //输出流
    string x;
    int i = 0;
    double a[100];
    int p =0;
       infile.open("D:\\homework_cxd\\park\\untitled1\\data.txt", ios::in);
       if(!infile.is_open ()){
           cout << "Open file failure" << endl;
       }
          else{
           while (!infile.eof())            // 若未到文件结束一直循环
           {
               infile >> x >>p>>a[i];
               i++;

           }
           infile.close();   //关闭文件

          double k = 0;
          for(int u  = 0; u<=i;u++){
              k+=a[u];
          }
           ui->pp->setText(QString::number(k,10,2));
           ui->qq->setText(QString::number(i+1,10,2));
          return k/(i+1);

       }

      return 0;
}

