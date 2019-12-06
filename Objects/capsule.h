#ifndef CAPSULE_H
#define CAPSULE_H

#include "drawableobject.h"
#include "vector"

class Capsule : public DrawableObject
{
public:
    //CONSTRUCTORS
    Capsule(QString name);

    //OPENGL FUNCTIONS
    void enableVertices(unsigned int position);
    void enableNormals(unsigned int position);
    void draw();
    void bind();

private:
    unsigned int VBO, EBO;
};

#endif // CAPSULE_H
