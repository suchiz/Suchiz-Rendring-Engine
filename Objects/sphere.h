#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"

#include "../Objects/drawableobject.h"

class Sphere: public DrawableObject
{
public:
    Sphere(QString name);

    //OPENGL FUNCTIONS
    void enableVertices(unsigned int position);
    void enableNormals(unsigned int position);
    void draw();
    void bind();

    //SPHERE FUNCTION

private:
    //OPENGL ATTRIBUTES
    unsigned int VBO, EBO;
    std::vector<unsigned int> indices;

    //SPHERE ATTRIBUTES
    int sectorCount = 36;
    int stackCount = 18;

    //METHODS
    void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);

};

#endif // SPHERE_H
