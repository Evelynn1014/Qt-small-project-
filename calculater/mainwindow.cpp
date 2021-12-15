//20301107 Jiayao Liu 2021.10.5
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stackDo.h"
#include <string>
#include<math.h>
using namespace std ;
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

// binary to D
double btoD(double n) {
    stackDo sk ;
    //split integer and decimal
    int integer;
    int o = 0;
    //judge
    if(n<0) {
        o = 1;n = -n;
    }
    integer = (int) n ;
    int ii = integer;
   double ans = 0 ;

    int k;
    int ju = 1;
    while (integer!=0)
    {
    k=integer%10;
    int r = k;
    if(r != 0 && r !=1 ){
        return 0xffffffff;
        //error!
    }
    ans += (r*ju);
    ju*=2;
    integer=integer/10;
    }

    double decimal = n - (double)ii;
    int count=0;
    double jud = 0.5;
    while (count<8)
    {
    decimal*=10;
    int r = (int)decimal;
    if(r != 0 && r !=1 ){
        return 0xffffffff;
        //error!
    }
    ans+=(r*jud);
    jud*=0.5;
    count++;
    if (decimal>=1.0)
    decimal-=1.0;


    }

    if(o == 1) {
        ans = -ans;
    }
    return ans;
}
double dtoB(double n) {
    stackDo sk ;
    int integer;
    int o = 0;
    //judge
    if(n<0) {
        o = 1;n = -n;
    }
    //split integer and decimal
    integer = (int) n ;
    int ii = integer;

    string ans = {0};
    int j = 0;
    if(o == 1) {
        ans[j] = '-';
        j++;
    }
    int k,a=0;
    int b[32];
    while (integer!=0)
    {
    k=integer%2;
    b[a++]=k;
    integer=integer/2;
    }
    while (a>0)
    {
    ans[j] = b[--a]+48;
    j++;
    }
    ans[j] = '.';
    j++;
    double decimal = n - (double)ii;
    int i=0;
    int count=0;
    int ad[8]={0};
    while (count<8)
    {
    decimal*=2;
    ad[count++]=(int)decimal;
    if (decimal>=1.0)
    decimal-=1.0;
    }
    while (i<8)
    {
    ans[j] = ad[i++] + 48;
    j++;
    }
    for(int l = 0; l < j;l++){
    }
    char ins[j] = {0};
    for(int q = 0; q< j; q++){
        ins[q] = ans[q];
    }
    string str1(ins);
    n = sk.stringToDouble(ins);
    return n;
}

//some basical calculate

int bascal(char c, double* num, int top) {
    stackDo k;
    double m;
    double n;
    m = num[top];
    top = k.popd(num,top);
    n =  num[top];
    top = k.popd(num,top);
    switch (c) {
    case '+' : top = k.pushd(num,top,m+n);break;
    case '-' : top = k.pushd(num,top,n-m);break;
    case '*' : top = k.pushd(num,top,m*n);break;
    case '/' : top = k.pushd(num,top,n/m);break;
    case '^' : top = k.pushd(num,top,pow(n,m));break;
    }
    return top;
}

// main calculation
double cal(QString qs){

    stackDo k;
    int p = 0;
    char str[50] = {0};
    double num[100];
    int topn = 0;
    char optr[50];
    int topr = 0;
// convert type
    string s = qs.toStdString();

//main alg
    for (int i = 0; i < (int)s.length(); i++) {
         if(s[i] == '1' || s[i] == '2'|| s[i] == '3'|| s[i] == '4'|| s[i] == '5'|| s[i] == '6'|| s[i] == '7'|| s[i] == '8'|| s[i] == '9'|| s[i] == '0'|| s[i] == '.') {
             str[p] = s[i];
             p++;
         } else if (s[i] == '/'|| s[i] == '*'){

             if(i == 0 ||  s[i-1] =='-'|| s[i-1] =='*'|| s[i-1] =='/' || s[i-1] == '+'|| s[i-1] == '('|| s[i-1] == '^'){
                return 0xffffffff;
                //error!
             }

             else{

             if(s[i-1] != ')') {
                 double n;
                 char ins[p+1] = {0};
                 for(int q = 0; q< p; q++){
                     ins[q] = str[q];
                 }
                 string str1(ins);
                 n = k.stringToDouble(str1);
                 topn = k.pushd(num,topn,n);
                 p = 0;
             }

             int j = 0;
             int c = 0;
             while(j == 0) {
                if(optr[topr] == '*' || optr[topr] == '/'|| optr[topr] == '^' ) {
                    topn = bascal(optr[topr], num, topn);
                     c++;
                    topr = k.popc(optr,topr);
                }else j = 1;
          }
             topr = k.pushc(optr,topr,s[i]);
    }
         }

         else if (s[i] == '^'){
             if(i == 0 ||  s[i-1] =='-'|| s[i-1] =='*'|| s[i-1] =='/' || s[i-1] == '+'|| s[i-1] == '('){
                return 0xffffffff;
                //error!
             }

             else{

             if(s[i-1] != ')') {
                 double n;
                 char ins[p+1] = {0};
                 for(int q = 0; q< p; q++){
                     ins[q] = str[q];
                 }
                 string str1(ins);
                 n = k.stringToDouble(str1);
                 topn = k.pushd(num,topn,n);
                 p = 0;
             }

             int j = 0;
             int c = 0;
             while(j == 0) {
                if(optr[topr] == '^') {
                    return 0xffffffff;
                }else j = 1;
          }
             topr = k.pushc(optr,topr,s[i]);
    }
         }

         else if (s[i] == '-') {
             if(i == 0 ||  s[i-1] =='+'|| s[i-1] =='*'|| s[i-1] =='/'|| s[i-1] =='^'){
                return 0xffffffff;
//error!
             }

             if(s[i-1] == '-'){
             }else{

             if(s[i-1] == '(') {
                 str[p] = '-';
                 p++;
             }else {
                  if(s[i-1] != ')') {
                      double n;
                      char ins[p+1] = {0};
                      for(int q = 0; q< p; q++){
                          ins[q] = str[q];
                      }
                      string str1(ins);
                      n = k.stringToDouble(str1);
                      topn = k.pushd(num,topn,n);
                      p = 0;
                  }

                 int j = 0;
                 int c = 0;
                 while(j == 0) {
                     if(optr[topr] == '*' || optr[topr] == '/' || optr[topr] == '+'||optr[topr] == '-'||optr[topr] == '^') {
                        topn = bascal(optr[topr], num, topn);
                        c++;
                        topr = k.popc(optr,topr);
                     }else j = 1;
                 }
                 topr = k.pushc(optr,topr,'-');
             }
         }
         }else if (s[i] == '+') {


             if(i == 0 ||  s[i-1] =='-'|| s[i-1] =='*'|| s[i-1] =='/'|| s[i-1] == '('||s[i-1] == '^'){
                return 0xffffffff;
//error!
             }

             if(s[i-1] == '+'){


             }else{
                 if(s[i-1] != ')') {
                     double n;
                     char ins[p+1] = {0};
                     for(int q = 0; q< p; q++){
                         ins[q] = str[q];
                     }
                     string str1(ins);
                     n = k.stringToDouble(str1);
                     topn = k.pushd(num,topn,n);
                     p = 0;
                 }

                int j = 0;
                int c = 0;
                while(j == 0) {
                    if(optr[topr] == '*' || optr[topr] == '/' || optr[topr] == '+'||optr[topr] == '-'||optr[topr] == '^') {
                       topn = bascal(optr[topr], num, topn);
                       c++;
                       topr = k.popc(optr,topr);
                    }else j = 1;
                }

                topr = k.pushc(optr,topr,'+');
             }

         }else if (s[i] == '(') {
             if(i != 0){
                 if(s[i-1] == ')'){
                     return 0xffffffff;
//error!
                 }
             }

             topr = k.pushc(optr,topr,'(');

         }else if (s[i] == ')') {

             if(p != 0) {
                 double n;
                 char ins[p+1] = {0};
                 for(int q = 0; q< p; q++){
                     ins[q] = str[q];
                 }
                 string str1(ins);
                 n = k.stringToDouble(str1);
                 topn = k.pushd(num,topn,n);
                 p = 0;
                 while(optr[topr] != '(') {
                     topn = bascal(optr[topr], num, topn);
                     topr = k.popc(optr,topr);
                 }
                 topr = k.popc(optr,topr);
             }else return 0xffffffff;
//error!
         }
    }

    if(p != 0) {

        double n;
        char ins[p+1] = {0};
        for(int q = 0; q<p; q++){
            ins[q] = str[q];
        }
        string str1(ins);
        n = k.stringToDouble(str1);
        topn = k.pushd(num,topn,n);
        p = 0;


    }
    if(topn - topr != 1){
            return 0xffffffff;
//main error!
}
    while(topr != 0) {
        topn = bascal(optr[topr], num, topn);
        topr = k.popc(optr,topr);
//finally cal
    }

    if(topn == 1 ) {
       return num[1];
     //the answer
    }

}

// == 算法
void MainWindow::on_pushButton_12_clicked()
{
    QString qs  = ui->lineEdit->text();
    double n = cal(qs);

    QString p;

    p = QString :: number(n,'f',6);
    if(p == "4294967295.000000") {
         ui->lineEdit->setText(qs+ " -> " + "grammar error!");
    }else ui->lineEdit->setText(qs+ " = " + p);


}

// output
void MainWindow::on_pushButton_2_clicked()
{
   ui->lineEdit->insert("1");
}

// <--
void MainWindow::on_pushButton_20_clicked()
{
    QString s = ui->lineEdit->text();
    s = s.mid(0,s.length()-1);
    ui->lineEdit->setText(s);
}

//clear
void MainWindow::on_pushButton_17_clicked()
{   QString s = ui->lineEdit->text();
    int j = 0;
    for (int i = 0;i<s.length() ;i++ ) {
        if(s[i] == '=' || s[i] == '>'){
            j = 1;
        }
    }
    if(j == 1) {

         ui->textEdit->insertPlainText(s + "\n");
    }
    ui->lineEdit->setText("");
}


void MainWindow::on_pushButton_7_clicked()
{
     ui->lineEdit->insert("2");
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->lineEdit->insert("3");
}


void MainWindow::on_pushButton_8_clicked()
{

    ui->lineEdit->insert("0");
}


void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->insert(".");
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->insert("4");
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEdit->insert("5");
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->lineEdit->insert("6");
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit->insert("7");
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit->insert("8");
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEdit->insert("9");
}


void MainWindow::on_pushButton_16_clicked()
{
   ui->lineEdit->insert("+");
}


void MainWindow::on_pushButton_15_clicked()
{
    ui->lineEdit->insert("-");
}


void MainWindow::on_pushButton_14_clicked()
{
    ui->lineEdit->insert("*");
}


void MainWindow::on_pushButton_13_clicked()
{
    ui->lineEdit->insert("/");
}


void MainWindow::on_pushButton_18_clicked()
{
    ui->lineEdit->insert("(");
}


void MainWindow::on_pushButton_19_clicked()
{
    ui->lineEdit->insert(")");
}


void MainWindow::on_pushButton_30_clicked()
{
    ui->textEdit->setText("");

}

//x^-1
void MainWindow::on_pushButton_21_clicked()
{
    QString qs  = ui->lineEdit->text();
    double n = cal(qs);
    QString p;
    p = QString :: number(n,'f',6);
    if(p == "4294967295.000000") {
         ui->lineEdit->setText(qs+ " -> " + "grammar error!");

    }else {
        double s = 1/n;
        p = QString :: number(s,'f',6);
        ui->lineEdit->setText("("+qs+ ")^-1 " +" = "+ p);
    }
}

//^
void MainWindow::on_pushButton_22_clicked()
{
    ui->lineEdit->insert("^");
}

//ln
void MainWindow::on_pushButton_23_clicked()
{   stackDo k;
    QString qs  = ui->lineEdit->text();
    double n = cal(qs);
    QString p;
    p = QString :: number(n,'f',6);
    if(p == "4294967295.000000") {
         ui->lineEdit->setText(qs+ " -> " + "grammar error!");

    }else {
        double s = log(n);
        p = QString :: number(s,'f',6);
        ui->lineEdit->setText("ln("+qs+ ")" +" = "+ p);
    }
}

//lg
void MainWindow::on_pushButton_31_clicked()
{   stackDo k;
    QString qs  = ui->lineEdit->text();
    double n = cal(qs);
    QString p;
    p = QString :: number(n,'f',6);
    if(p == "4294967295.000000") {
         ui->lineEdit->setText(qs+ " -> " + "grammar error!");

    }else {
        double s = k.logab(10,n);
        p = QString :: number(s,'f',6);
        ui->lineEdit->setText("lg("+qs+ ")" +" = "+ p);
    }
}

//sin
void MainWindow::on_pushButton_25_clicked()
{
    QString qs  = ui->lineEdit->text();
    double n = cal(qs);
    QString p;
    p = QString :: number(n,'f',6);
    if(p == "4294967295.000000") {
         ui->lineEdit->setText(qs+ " -> " + "grammar error!");

    }else {
        double s = sin(n);
        p = QString :: number(s,'f',6);
        ui->lineEdit->setText("sin("+qs+ ")" +" = "+ p);
    }
}

//cos
void MainWindow::on_pushButton_26_clicked()
{
    QString qs  = ui->lineEdit->text();
    double n = cal(qs);
    QString p;
    p = QString :: number(n,'f',6);
    if(p == "4294967295.000000") {
         ui->lineEdit->setText(qs+ " -> " + "grammar error!");

    }else {
        double s = cos(n);
        p = QString :: number(s,'f',6);
        ui->lineEdit->setText("cos("+qs+ ")" +" = "+ p);
    }
}

//tan
void MainWindow::on_pushButton_27_clicked()
{
    QString qs  = ui->lineEdit->text();
    double n = cal(qs);
    QString p;
    p = QString :: number(n,'f',6);
    if(p == "4294967295.000000") {
         ui->lineEdit->setText(qs+ " -> " + "grammar error!");

    }else {
        double s = sin(n)/cos(n);
        p = QString :: number(s,'f',6);
        ui->lineEdit->setText("tan("+qs+ ")" +" = "+ p);
    }
}

//root
void MainWindow::on_pushButton_24_clicked()
{
    QString qs  = ui->lineEdit->text();
    double n = cal(qs);
    QString p;
    p = QString :: number(n,'f',6);
    if(p == "4294967295.000000") {
         ui->lineEdit->setText(qs+ " -> " + "grammar error!");

    }else {
        double s = sqrt(n);
        p = QString :: number(s,'f',6);
        ui->lineEdit->setText("sqrt("+qs+ ")" +" = "+ p);
    }
}

//use d to b
void MainWindow::on_pushButton_28_clicked()
{
    QString qs  = ui->lineEdit->text();
    double n = cal(qs);
    QString p;
    p = QString :: number(n,'f',6);
    if(p == "4294967295.000000") {
         ui->lineEdit->setText(qs+ " -> " + "grammar error!");

    }else {
        double s = dtoB(n);
        p = QString :: number(s,'f',6);
        ui->lineEdit->setText("D("+qs+ " )" +" = "+ "B(" +p + ")");
    }
}

//use b to d
void MainWindow::on_pushButton_29_clicked()
{
    QString qs  = ui->lineEdit->text();
    double n = cal(qs);
    QString p;
    p = QString :: number(n,'f',6);
    if(p == "4294967295.000000") {
         ui->lineEdit->setText(qs+ " -> " + "grammar error!");

    }else {
        double s = btoD(n);
        p = QString :: number(s,'f',6);
        if(p == "4294967295.000000")  {
            ui->lineEdit->setText("("+qs+ ")" +" is a wrong binary number " );
        } else
        ui->lineEdit->setText("B("+qs+ ")" +" = "+ "D(" +p + ")");
    }
}

