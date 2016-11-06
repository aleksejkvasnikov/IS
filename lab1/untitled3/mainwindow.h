#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QGraphicsScene>
#include <QStringList>
#include <mypoint.h>
//class MyPoint;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MyPoint *getPoint(int x, int y);
    bool mycontains(QList<MyPoint *> list, MyPoint *point);
    void isDiagWall(int x, int y, MyPoint *point, MyPoint *chil);
private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();


private:
    Ui::MainWindow *ui;
    int xval,yval,sx,sy,fx,fy,wx,wy=0;
   // int checkers[8][8];
    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
    MyPoint *spoint;
    MyPoint *fpoint;
    QStringList walls;
  //  QList<MyPoint> wList;
};

#endif // MAINWINDOW_H
