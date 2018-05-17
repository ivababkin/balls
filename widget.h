#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include <QGLWidget>
#include "ball.h"
#include "wall.h"

class Widget : public QGLWidget
{
public:
    Widget(QGLWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
public slots:
    virtual void updateGL();
private:
    float xRotation,yRotation,zRotation,scale;
    QPoint mousePos;
    void drawAxis();
    ball * ballmain;
    ball * ball1;
    ball * ball2;
    ball * ball3;

    wall* left_wall;
    wall* right_wall;
    wall* top_wall;
    wall* bottom_wall;
};

#endif // WIDGET_H
