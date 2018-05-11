#include "wall.h"

wall::wall(float right, float top, float left, float bottom, char whatisit, wall * link)
{
    this->left = left;
    this->top = top;
    this->right = right;
    this->bottom = bottom;
    this->what = whatisit;
    this->link = link;
}

void wall::draw()
{
    glRectf(this->right, this->top, this->left, this->bottom);
}
