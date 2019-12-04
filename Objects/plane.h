#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <glad/glad.h>
#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"

#include "../Objects/drawableobject.h"

class Plane: public DrawableObject
{
public:
    //CONSTRUCTORS
    Plane(float size = 1.0f);

    //OPENGL FUNCTIONS
    void enableVertices(unsigned int position);
    void enableNormals(unsigned int position);
    void draw();
    void bind();

private:
    unsigned int VBO;

};

#endif // PLANE_H
