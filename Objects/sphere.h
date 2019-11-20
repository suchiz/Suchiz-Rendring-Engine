#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "drawableobject.h"

class Sphere: public DrawableObject
{
public:
    Sphere(float size = 1.0f);

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
    glm::mat4 getModel() const {return model;}
    glm::vec3 getColor() const {return color;}

protected:
    //OPENGL ATTRIBUTES
    unsigned int VBO, EBO;
    glm::vec3 color;
    glm::vec3 position;
    glm::mat4 model;

    //SPHERE ATTRIBUTES
    int sectorCount = 36;                        // longitude, # of slices
    int stackCount = 18;
    std::vector<unsigned int> indices;
    std::vector<float> interleavedVertices;

    void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);

};

#endif // SPHERE_H
