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
    Plane(float size= 1.0f);

    //OPENGL FUNCTIONS
    void enableVertices(unsigned int position);
    void enableNormals(unsigned int position);
    void draw();
    void bind();

    //SETTERS
    void setPosition(glm::vec3 pos) {model = glm::translate(model, pos); position = pos;}
    void setRotation(float angle, glm::vec3 axis){model = glm::rotate(model, glm::radians(angle), axis);}
    void setColor(glm::vec3 c) {color = c;}

    //GETTERS
    glm::vec3 getPosition() const {return position;}
    const float* getVertices() const {return vertices;}
    unsigned int getVBO() const {return VBO;}
    glm::mat4 getModel() const {return model;}
    glm::vec3 getColor() const {return color;}

protected:
    unsigned int VBO;
    float vertices[36];
    glm::vec3 color;
    glm::vec3 position;
    glm::mat4 model;
};

#endif // PLANE_H
