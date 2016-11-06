#include "mypoint.h"
#include <cmath>
#include <qdebug.h>
#include <algorithm>
//#include <mainwindow.h>
MyPoint::MyPoint()
{
    parent = 0;

    x = y = f = g = h = 0;
}

MyPoint::MyPoint(int xa, int ya)
{
    x=xa;
    y=ya;
}
void MyPoint::setParent(MyPoint *p)
{
    parent = p;
}
int MyPoint::getGScore()
{
    return g;
}

int MyPoint::getHScore()
{
    return h;
}

int MyPoint::getFScore()
{
    return f;
}

int MyPoint::getX()
{
    return x;
}
int MyPoint::getGScore(MyPoint *p)
{
    return p->g + ((x == p->x || y == p->y) ? 10 : 14);
}
int MyPoint::getDScore(MyPoint *p)
{
    return ((x == p->x || y == p->y) ? 10 : 14);
}
int MyPoint::getHScore(MyPoint *p, int evr)
{
    if (evr==0)
    return (abs(p->x - x) + abs(p->y - y)) * 10;
    if (evr==1)
    {
        return sqrt(pow((x - (p->x)),2) + pow((y - (p->y)),2));
    }
    if (evr==2)
    {
        int dx = abs((x) - p->x);
        int dy = abs((y) - p->y);
        return ((dx + dy) - std::min(dx, dy));
    }
    else return 0;
}
int MyPoint::getY()
{
    return y;
}
bool MyPoint::hasParent()
{
    return parent != 0;
}
MyPoint* MyPoint::getParent()
{
    return parent;
}
