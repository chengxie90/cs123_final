#ifndef LIGHT_H
#define LIGHT_H

#include "common.h"

class Light
{
public:
    virtual void apply(DrawContext& drawContext) = 0;
};

#endif // LIGHT_H
