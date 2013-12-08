#ifndef SKYBOX_H
#define SKYBOX_H

#include "common.h"

class Skybox
{
public:
    Skybox(string name);
    ~Skybox();
    
    void render(DrawContext& context);
    
private:
    Mesh* mesh_ = NULL;
};

#endif // SKYBOX_H
