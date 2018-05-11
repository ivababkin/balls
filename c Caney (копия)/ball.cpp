#include <cmath>
#include <iostream>
#include "ball.h"

ball::ball(double x, double y, double newspeed, double direction, ball* pnextball, double radius, int newmass)
{
    this->x = x;
    this->y = y;
    setspeed(newspeed);
    setdir(direction);
    this->link = pnextball;
    this->radius = radius;
    this->mass = newmass;
}

void ball::setdir( double newdir )
{
    double dir1 = newdir;
    while(dir1 > 2 * M_PI)
    {
        dir1 = dir1 - 2 * M_PI;
    }
    while(dir1 < 0)
    {
        dir1 = dir1 + 2 * M_PI;
    }
    this->dir = dir1;
}

double ball::getcentreangle(ball otherball)//угол между центрами
{
    double y = otherball.gety() - this->gety();
    double x = otherball.getx() - this->getx();
    if ((x > 0) && (y > 0))
        return atan(abs(y/x));

    if ((x < 0) && (y > 0))
        return (M_PI - atan(abs(y/x)));

    if ((x > 0) && (y < 0))
        return (2 * M_PI - atan(abs(y/x)));

    if ((x < 0) && (y < 0))
        return (M_PI + atan(abs(y/x)));

    if ((x = 0) && (y < 0))
        return 3 * M_PI / 2;

    if ((x = 0) && (y > 0))
        return M_PI / 2;

    if ((x > 0) && (y = 0))
        return 228;

    if ((x < 0) && (y = 0))
        return M_PI;

    //std::cout << "angle = 0" << std::endl;
    return 0;
}

double ball::angleofdir(double vx, double vy)//костыльно считает угол по двум проекциям скорости
{

    if ((vx = 0) && (vy = 0))
        return  0;
    if ((vx = 0) && (vy < 0))
        return  3 * M_PI / 2;
    if ((vx = 0) && (vy > 0))
        return  M_PI / 2;
    if ((vx < 0) && (vy = 0))
        return  M_PI;
    if ((vx > 0) && (vy = 0))
        return  0;

    if ((vx > 0) && (vy > 0))
        return atan(vy/vx);
    if ((vx < 0) && (vy > 0))
        return  M_PI - atan(vy/vx);
    if ((vx > 0) && (vy < 0))
        return  2 * M_PI - atan(vy/vx);
    if ((vx < 0) && (vy < 0))
        return  M_PI + atan(vy/vx);

    return 0;
}

/*void ball::getcentrevector(ball otherball, double &axisx, double &axisy)
{
    double xx = otherball.getx() - this->getx();
    double yy = otherball.gety() - this->gety();

    axisx = xx / sqrt((xx * xx + yy * yy));
    axisy = yy / sqrt((xx * xx + yy * yy));
}*/

/*void ball::hitbyballvector( ball* that )
{
    double axisx, axisy;
    this->getcentrevector(*that, axisx, axisy);
    double v1x = axisx * this->getspeedx();
    double v1y = axisy * this->getspeedy();
    double v2x = axisx * this->getspeedx();
    double v2y = axisy * this->getspeedy();
    double m1 = this->getmass();
    double m2 = that->getmass();

    double v1xnew = (2 * v2x * m2 - m2 * v1x + v1x * m1)/(m2 + m1);
    double v2xnew = (2 * v1x * m1 - m1 * v2x + v2x * m2)/(m2 + m1);

    this->setspeed(sqrt(v1xnew * v1xnew + v1y * v1y));
    that->setspeed(sqrt(v2xnew * v2xnew + v2y * v2y));

    double angle = this->getcentreangle(*that);

    this->setdir(atan(v1y/v1xnew) + angle);
    that->setdir(atan(v2y/v2xnew) + angle);
}*/

bool ball::areballsnearing( ball * that) const//сближаются ли шары
{
    double r1 = (sqrt(pow((that->getx() - this->getx()), 2) + pow((that->gety() - this->gety()), 2)));


    double dx1 = this->getspeed() * cos(this->getdir());
    double dy1 = this->getspeed() * sin(this->getdir());
    double dx2 = that->getspeed() * cos(that->getdir());
    double dy2 = that->getspeed() * sin(that->getdir());


    double newx1 = this->getx() + dx1;
    double newy1 = this->gety() + dy1;
    double newx2 = that->getx() + dx2;
    double newy2 = that->gety() + dy2;

    double r2 = (sqrt(pow((newx2 - newx1), 2) + pow((newy2 - newy1), 2)));


    if (r2 < r1)
    {
        return true;
    }

    return false;
}

void ball::hitbyball( ball* that )
{
    if (this->getradius() == 0.11)
        std::cout << "   ballmain" << std::endl;

    if (this->getradius() == 0.1)
        std::cout << "   ball1" << std::endl;

    double angle = this->getcentreangle(*that); std::cout << "angle = "<< angle << std::endl;
    double v1x = this->getspeed() * cos(this->getdir() - angle); std::cout << "v1x = " << v1x << std::endl;
    double v1y = this->getspeed() * sin(this->getdir() - angle); std::cout << "v1y = " << v1y << std::endl;
    double v2x = that->getspeed() * cos(that->getdir() - angle); std::cout << "v2x = " << v2x << std::endl;
    double v2y = that->getspeed() * sin(that->getdir() - angle); std::cout << "v2y = " << v2y << std::endl;
    double m1 = this->getmass();
    double m2 = that->getmass();
    if (this->areballsnearing(that) == true)
    {
        std::cout << "========="<< std::endl;
        double v1xnew = (2 * v2x * m2 - m2 * v1x + v1x * m1)/(m2 + m1);
        double v2xnew = (2 * v1x * m1 - m1 * v2x + v2x * m2)/(m2 + m1);
        std::cout << "v1xnew = " << v1xnew << "   v2xnew = " << v2xnew << std::endl;
        //angleofdir(v2xnew, v2y);
        this->setdir(angleofdir(v1xnew, v1y) + angle);
        that->setdir(angleofdir(v2xnew, v2y) + angle);
        //this->setdir(M_PI);
        //this->setdir(0);
        this->setspeed(sqrt(v1xnew * v1xnew + v1y * v1y));
        that->setspeed(sqrt(v2xnew * v2xnew + v2y * v2y));
        std::cout << "========="<< std::endl;
    }
};

void ball::draw()
{
    glBegin(GL_POLYGON);
    for (int i=0; i < 20; i++)
    {
        float degInRad = 3.14159 * 2 * i / 20;
        glVertex2f(this->getx() + cos(degInRad) * this->getradius(),this->gety() + sin(degInRad) * this->getradius());
    }
    //std::cout << "speed = "<<getspeed() << std::endl;
    glEnd();

}

ball * ball::hasitbeenhitbyball(ball * ballmain)
{
    ball * ballptr = ballmain;
    while (ballptr)
    {
        if (ballptr != this)
        {
            if (sqrt(pow((ballptr->getx() - this->getx()), 2) + pow((ballptr->gety() - this->gety()), 2)) <= (this->getradius() + ballptr->getradius()))
                return ballptr;
        }
        ballptr = ballptr->getlink();
    }
    return NULL;
}

void ball::hasitbeenhitbywall(wall * bottom_wall)
{
    wall * wallptr = bottom_wall;
    while (wallptr)
    {
        if ((wallptr->whatisit() == 'b') && (abs(this->gety() - wallptr->gettop()) <= this->getradius()))
        {
            this->setdir(- this->getdir());
        }
        if ((wallptr->whatisit() == 't') && (abs(this->gety() - wallptr->getbottom()) <= this->getradius()))
        {
            this->setdir(- this->getdir());
        }
        if ((wallptr->whatisit() == 'r') && (abs(wallptr->getleft() - this->getx())  <= this->getradius()))
        {
            this->setdir(M_PI - this->getdir());
        }
        if ((wallptr->whatisit() == 'l') && (abs(wallptr->getright() - this->getx())  <= this->getradius()))
        {
            this->setdir(M_PI - this->getdir());
        }
    wallptr = wallptr->getlink();
    }
}

void ball::update(ball * ballmain, wall * bottom_wall)
{
    double dx = this->getspeed() * cos(this->getdir());
    double dy = this->getspeed() * sin(this->getdir());

    this->setx(this->getx() + dx);
    this->sety(this->gety() + dy);

    this->hasitbeenhitbywall(bottom_wall);

    ball* pball = this->hasitbeenhitbyball(ballmain);
    if (pball != NULL)// && (this->getradius() == 0.11))
    {
        if (this->areballsnearing(pball) == true)
        {
            this->hitbyball(pball);
        }
    }



    //std::cout << this->getdir() <<std::endl;
    /*double Fx = 0;
    double Fy = 0;
    this->gravity(Fx, Fy, ballmain);
    this->setspeed (sqrt(pow(this->getspeed() * cos(this->getdir()) + Fx, 2) +
                          pow(this->getspeed() * sin(this->getdir()) + Fy, 2)));
    this->setdir(atan(pow(this->getspeed() * sin(this->getdir()) + Fy, 2) / pow(this->getspeed() * cos(this->getdir()) + Fx, 2)));*/

}

void ball::gravity(float &Fx, float &Fy, ball * ballmain)
{
    ball * ballptr = ballmain;

    while (ballptr)
    {
        if (ballptr != this)
        {
            double angle = this->getcentreangle(*ballptr);
            Fx = Fx + cos(angle) * (sqrt(pow(ballptr->getx() - this->getx(), 2) + pow(ballptr->gety() - this->gety(), 2))
             * this->getmass() * ballptr->getmass());
            Fy = Fy + sin(angle) * (sqrt(pow(ballptr->getx() - this->getx(), 2) + pow(ballptr->gety() - this->gety(), 2))
             * this->getmass() * ballptr->getmass());
        }
        ballptr = ballptr->getlink();
    }
}
