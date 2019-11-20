#ifndef DRAWABLEOBJECT
#define DRAWABLEOBJECT
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum ObjectType {SPHERE, CUBE, PLANE};

class DrawableObject {
public:
    void draw();
    void bind();
    void enableVertices(unsigned int position);
    void enableNormals(unsigned int position);
    void copyData(DrawableObject obj);

    glm::vec3 getPosition() const {return position;}
    glm::vec3 getRotation() const {return rotation;}
    glm::mat4 getModel() const {return model;}
    glm::vec3 getColor() const {return color;}
    ObjectType getType() const {return objectType;}
    float getSize() const {return size;}
    void setPosition(glm::vec3 pos) {model = glm::translate(model, pos); position = pos;}
    void setRotation(float angle, glm::vec3 axis){model = glm::rotate(model, glm::radians(angle), axis);}
    void setColor(glm::vec3 c) {color = c;}

protected:
    float size;
    glm::vec3 color;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::mat4 model;
    ObjectType objectType;

};

#endif // DRAWABLEOBJECT

