#ifndef MYPOINT_H
#define MYPOINT_H

#include <qdebug.h>
class MyPoint
{
public:
    MyPoint();
    MyPoint(int xa, int ya);
    MyPoint(const MyPoint &other);
    ~MyPoint(){}
    MyPoint &operator=(const MyPoint &other);
    bool MyPoint::operator==(const MyPoint& r)
    {
        return ((this->x == r.x) && (this->y == r.y));
    }
    int x,y,g,f,h;
    MyPoint* parent;
    bool walkable = true;
    int getX();
    int getY();
    int getHScore(MyPoint *p, int evr);
    int getGScore(MyPoint *p);
    int getGScore();
    int getHScore();
    int getFScore();
    void setParent(MyPoint *p);
    bool hasParent();
    MyPoint *getParent();
    int getDScore(MyPoint *p);
};

#endif // MYPOINT_H
