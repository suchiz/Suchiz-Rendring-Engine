#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "drawableobject.h"

class Cube: public DrawableObject
{
public:
    //CONSTRUCTORS
    Cube(float size = 1.0f);

    //OPENGL FUNCTIONS
    void enableVertices(unsigned int position);
    void enableNormals(unsigned int position);
    void draw();
    void bind();
    void copyData(DrawableObject obj);

    //SETTERS
    void setPosition(glm::vec3 pos) {model = glm::translate(model, pos); position = pos;}
    void setRotation(float angle, glm::vec3 axis){model = glm::rotate(model, glm::radians(angle), axis);}
    void setColor(glm::vec3 c) {color = c;}

    //GETTERS
    glm::vec3 getPosition() const {return position;}
    glm::mat4 getModel() const {return model;}
    glm::vec3 getColor() const {return color;}

protected:
    unsigned int VBO;
    float vertices[216];
    glm::vec3 color;
    glm::vec3 position;
    glm::mat4 model;
};

#endif // CUBE_H
