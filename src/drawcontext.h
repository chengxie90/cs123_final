#ifndef DRAWCONTEXT_H
#define DRAWCONTEXT_H

#include <geometry.h>

class DrawContext
{
public:
    mat4 view;
    mat4 projection;
    mat4 viewProjection;
};

#endif // DRAWCONTEXT_H
