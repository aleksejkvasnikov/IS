#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setAlignment(Qt::AlignCenter);
    ui->graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() //поле
{
    QPen blackpen(Qt::black);
    int width = ui->graphicsView->viewport()->width();
    int height = ui->graphicsView->viewport()->height();
    xval = ui->lineEdit->text().toInt();
    yval = ui->lineEdit_2->text().toInt();
    scene->setSceneRect(0,0,width,height);
    blackpen.setWidth(3);
    for (int i=0; i<xval; i++)
    {
        for (int j=0; j<yval; j++)
        {
            scene->addRect(0+((i*width)/xval),0+((j*height)/yval),width/xval,height/yval,blackpen);
        }
    }

}

void MainWindow::on_pushButton_2_clicked() // начальная точка
{
    QPen blackpen(Qt::black);
    QBrush greenBrush(Qt::green);
    sx = ui->lineEdit_3->text().toInt()-1;
    sy = ui->lineEdit_4->text().toInt()-1;
    int width = ui->graphicsView->viewport()->width();
    int height = ui->graphicsView->viewport()->height();
    scene->addRect(((sx*width)/xval),((sy*height)/yval),width/xval,height/yval,blackpen,greenBrush);
    spoint->x=sx;
    spoint->y=sy;
}

void MainWindow::on_pushButton_3_clicked() // конечная точка
{
    QPen blackpen(Qt::black);
    QBrush redBrush(Qt::red);
    fx = ui->lineEdit_5->text().toInt()-1;
    fy = ui->lineEdit_6->text().toInt()-1;
    int width = ui->graphicsView->viewport()->width();
    int height = ui->graphicsView->viewport()->height();
    scene->addRect(((fx*width)/xval),((fy*height)/yval),width/xval,height/yval,blackpen,redBrush);
    fpoint->x=fx;
    fpoint->y=fy;
}

void MainWindow::on_pushButton_4_clicked() // стена
{
    QPen blackpen(Qt::black);
    QBrush blueBrush(Qt::blue);
    wx = ui->lineEdit_7->text().toInt()-1;
    wy = ui->lineEdit_8->text().toInt()-1;
    int width = ui->graphicsView->viewport()->width();
    int height = ui->graphicsView->viewport()->height();
    scene->addRect(((wx*width)/xval),((wy*height)/yval),width/xval,height/yval,blackpen,blueBrush);
    QString str;
    QTextStream(&str) << wx << ", " << wy;
    walls.push_back(str);
}
bool MainWindow::mycontains(QList<MyPoint*> list, MyPoint* point) // функция для проверки наличия в списке
{
     QList<MyPoint*>::iterator i;
     bool val=false;
     for (i = list.begin(); i != list.end(); ++ i)
     {
         if ((point->x == (*i)->x) && (point->y == (*i)->y))
         {
             val = true;
         }
     }
     return val;
}

MyPoint* MainWindow::getPoint(int x, int y) // создание соседей
{
    MyPoint* newPoint = new MyPoint(x,y);
    if ((x<0) || (y<0) || (y>yval-1) || (x>xval-1)){
        newPoint->walkable=false;

    }
    QString str;
    QTextStream(&str) << x << ", " << y;
    if (walls.contains(str)){
        newPoint->walkable=false;
    }
    return newPoint;
}
void MainWindow::isDiagWall(int x, int y, MyPoint* point, MyPoint* chil) // проверка на диагональные шаги
{
    QString str;
    QTextStream(&str) << point->x + x << ", " <<  point->y;
    if (walls.contains(str)){
        chil->walkable=false;
    }
    QString str1;
    QTextStream(&str1) <<  point->x << ", " << point->y + y;
    if (walls.contains(str1)){
        chil->walkable=false;
    }
}
// рассчет пути
void MainWindow::on_pushButton_5_clicked()
{    
    int width = ui->graphicsView->viewport()->width();
    int height = ui->graphicsView->viewport()->height();
    QBrush redBrush(Qt::red);
    QPen blackpen(Qt::black);
    QList<MyPoint*> openlist;
    QList<MyPoint*> closedList;
    MyPoint *current;
    MyPoint *child;
    QList<MyPoint*>::iterator i;
    openlist.push_back(spoint);
    spoint->g = 0;
    int n=0;
    int tentativeScore;
    spoint->f = spoint->g + spoint->getHScore(fpoint, ui->comboBox->currentIndex());
    while (!openlist.isEmpty())
    {
        //Ищем в открытом списке клетку с наименьшей стоимостью F. Делаем ее текущей клеткой.
        for (i = openlist.begin(); i != openlist.end(); ++ i)
        {
            if (i == openlist.begin() || (*i)->getFScore() <= current->getFScore())
            {
                current = (*i);
            }
        }

        if (*current == *fpoint)
        {
            break;
        }
        openlist.removeOne(current);

        closedList.push_back(current);
        for (int x = -1; x <= 1; x ++)
        {
            for (int y = -1; y <= 1; y ++)
            {
                if (x == 0 && y == 0)
                {
                    continue;
                }

                child = getPoint(current->getX()+x, current->getY()+y);

                if (((x==-1) && (y==-1)) || ((x==1) && (y==1)) || ((x==1) && (y==-1)) ||((x==-1) && (y==1)))
                {
                    isDiagWall(x,y,current,child);
                }

                if (!child->walkable)
                {
                    continue;
                }

                tentativeScore = current->getGScore() + current->getDScore(child);
                if (mycontains(closedList, child))
                {
                    continue;
                }
                if (!mycontains(openlist, child))
                {
                    child->setParent(current);
                    child->g = tentativeScore;
                    child->f = child->g + child->getHScore(fpoint, ui->comboBox->currentIndex());
                       openlist.push_back(child);
                }else if (tentativeScore  < child->getGScore()){
                     child->setParent(current);
                     child->g = tentativeScore;
                }
            }
        }
        ui->textBrowser->append("Opened list");
        for (i = openlist.begin(); i != openlist.end(); ++ i)
        {
            QString str;
            QTextStream(&str) << (*i)->x << ", " << (*i)->y;
            ui->textBrowser->append(str);
        }
        ui->textBrowser->append("Closed list");
        for (i = closedList.begin(); i != closedList.end(); ++ i)
        {
            QString str;
            QTextStream(&str) << (*i)->x << ", " << (*i)->y;
            ui->textBrowser->append(str);
        }
    ui->textBrowser->append("Next iteration");
        n=n+1;
    }
    if (!(*current == *fpoint))
    {
        ui->textBrowser->append("NET PUTI");
    }
    ui->textBrowser->append("DONE");
    QString str;
    QTextStream(&str) << "n= " << n << " Rasstoyanie = " << current->g;
    ui->textBrowser->append(str);
    QBrush yellowBrush(Qt::yellow);
    while (current->hasParent() && current != spoint)
    {
        scene->addRect(((current->x*width)/xval),((current->y*height)/yval),width/xval,height/yval,blackpen,yellowBrush);
        current = current->getParent();
    }
    scene->addRect(((fx*width)/xval),((fy*height)/yval),width/xval,height/yval,blackpen,redBrush);
    openlist.clear();
    closedList.clear();
    walls.clear();
}

//очистка
void MainWindow::on_pushButton_6_clicked()
{
    scene->clear();
    ui->textBrowser->clear();
}

