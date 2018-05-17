#ifndef WALL_H
#define WALL_H

#include <QGLWidget>

class wall
{
public:
    wall(float left, float right, float top, float bottom, char whatisit, wall * link);
    wall * getlink() {return this->link;}
    float getleft() {return this->left;}
    float getright() {return this->right;}
    float gettop() {return this->top;}
    float getbottom() {return this->bottom;}
    char whatisit(){return this->what;}//l=left, r=right, t=top, b=bottom
    void draw();
protected:
    float left;
    float right;
    float top;
    float bottom;
    wall * link;
    char what;
};

#endif // WALL_H
