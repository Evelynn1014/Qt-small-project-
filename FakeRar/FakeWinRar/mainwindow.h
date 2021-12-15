#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"compression.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QList>
#include <QDrag>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void display();
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);


private slots:
    void on_openButton_clicked();

    void on_codeButton_clicked();

    void on_decodeButton_2_clicked();

    void on_progressBar_valueChanged(int value);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    Compression *process;
    Compression *processes[10];
    QStringList qsl;
    QString path;
    int z;

};

#endif // MAINWINDOW_H
