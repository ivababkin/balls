#ifndef BALL_H
#define BALL_H

#include <QGLWidget>
#include "wall.h"

class ball
{
    public:
        ball(double x, double y, double newspeed, double direction, ball* pnextball, double radius, int newmass);
        // Рисование шара в текущем положении
        void draw();
        // Изменение положения шара в предположении, что с момента
        // предыдущего изменения прошел единичный промежуток времени
        void update(ball * ballmain, wall * bottom_wall);
        // Извещение шара о том, что в него попал другой шар
        void hitbyball( ball* pball );
        // Функции-члены для доступа к переменным
        void setx( double newx ) { this->x = newx;}
        void sety( double newy ) { this->y = newy;}
        void setspeed( double newspeed ) { this->speed = newspeed;}
        void setdir( double dir );// { this->dir = dir;}
        ball* getlink() const { return this->link;}
        double getspeed() const { return this->speed;}
        double getx() const { return this->x;}
        double gety() const { return this->y;}
        double getdir() const { return this->dir;}
        double getspeedx() const { return (this->getspeed() * cos(this->getdir()));}
        double getspeedy() const { return (this->getspeed() * sin(this->getdir()));}
        double getradius() const { return this->radius;}
        void hitbyballvector( ball* that );
        void getcentrevector(ball otherball, double &axisx, double &axisy);
        int getmass() { return this->mass;}
        double getcentreangle(ball ball2);
        double angleofdir(double vx, double vy);
        ball * hasitbeenhitbyball(ball * ballmain);
        void hasitbeenhitbywall(wall * bottom_ball);
        bool areballsnearing( ball * that) const;
        void gravity(ball * ballmain);
        double distance(ball otherball);

    private:
        ball* link;
        double speed;
        double dir;
        double x;
        double y;
        int mass;
        double radius;
};


#endif // BALL_H
