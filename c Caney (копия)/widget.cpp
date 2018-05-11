#include "widget.h"
#include <iostream>

Widget::Widget(QGLWidget *parent)
    : QGLWidget(parent)
{
    resize(500,500);
    //ball(double x, double y, double newspeed, double direction, ball* pnextball, double radius, int newmass);
    //ball3 = new ball(0, 0, 0.01, 3, NULL, 0.1, 1);
    //ball2 = new ball(-0.5, 0, 0.01, 2, ball3, 0.1, 1);
    ball1 = new ball(0.5, 0, 0.01, -M_PI, NULL, 0.1, 1);
    ballmain = new ball(-0.5, 0, 0.01, 1, ball1, 0.1, 1);

    left_wall = new wall(-0.8, 0.9, -0.9, -0.9, 'l', NULL);
    right_wall = new wall(0.9, 0.9, 0.8, -0.9, 'r', left_wall);
    top_wall = new wall(0.9, 0.9, -0.9, 0.8, 't', right_wall);
    bottom_wall = new wall(0.9, -0.8, -0.9, -0.9, 'b', top_wall);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(1);
}

void Widget::initializeGL()
{
   qglClearColor(Qt::white);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);
   glEnable(GL_CULL_FACE);
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void Widget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nHeight, nHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void Widget::paintGL()
{
   //std::cout << "paint" << std::endl;
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера изображения и глубины

   //glMatrixMode(GL_MODELVIEW); // устанавливает положение и ориентацию матрице моделирования
   //glLoadIdentity();           // загружает единичную матрицу моделирования

   //glScalef(scale, scale, scale);        // масштабирование
   /*
   glRotatef(xRotation, 1.0f, 0.0f, 0.0f); // поворот по X
   glRotatef(yRotation, 0.0f, 1.0f, 0.0f); // поворот по Y
   glRotatef(zRotation, 0.0f, 0.0f, 1.0f); // поворот по Z
    */
   glColor3f(1 , 0, 0);
   ball * ballptr = ballmain;
   while (ballptr)
   {
        ballptr->draw();
        ballptr = ballptr->getlink();
   }
   //ballmain->draw();
   glColor3f(0.5 ,0, 0.5);
   wall * wallptr = bottom_wall;
   while (wallptr)
   {
        wallptr->draw();
        wallptr = wallptr->getlink();
   }

}

void Widget::drawAxis()
{
    glLineWidth(3.0f); // устанавливаем ширину линии

    glColor4f(1.00f, 0.00f, 0.00f, 1.0f); // устанавливается цвет последующих линий
    // ось x
    glBegin(GL_LINES); // построение линии
        glVertex3f( 1.0f,  0.0f,  0.0f); // первая точка
        glVertex3f(-1.0f,  0.0f,  0.0f); // вторая точка
    glEnd();

    QColor halfGreen(0, 128, 0, 255);
    qglColor(halfGreen);
    glBegin(GL_LINES);
        // ось y
        glVertex3f( 0.0f,  1.0f,  0.0f);
        glVertex3f( 0.0f, -1.0f,  0.0f);

        glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
        // ось z
        glVertex3f( 0.0f,  0.0f,  1.0f);
        glVertex3f( 0.0f,  0.0f, -1.0f);
    glEnd();
}

void Widget::updateGL()
{
    ball * ballptr = ballmain;
    while (ballptr)
    {
        ballptr->update(ballmain, bottom_wall);
        ballptr = ballptr->getlink();
    }
    glDraw();

}
