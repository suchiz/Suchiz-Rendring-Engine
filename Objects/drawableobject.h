#ifndef DRAWABLEOBJECT
#define DRAWABLEOBJECT
#include <glad/glad.h>
#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"
#include <vector>

enum ObjectType {SPHERE, CUBE, PLANE, SURFACE, CAPSULE};

class DrawableObject {
public:
    //OPENGL FUNCTIONS
    virtual void draw() = 0;
    virtual void bind() = 0;
    virtual void enableVertices(unsigned int position) = 0;
    virtual void enableNormals(unsigned int position) = 0;

    //OBJECTS FUNCTIONS
    bool is(ObjectType otherType) {return otherType == objectType;}

    //GETTERS
    glm::vec3 getPosition() const {return position;}
    glm::vec3 getRotation() const {return rotation;}
    glm::mat4 getModel() const {return model;}
    glm::vec3 getColor() const {return color;}
    ObjectType getType() const {return objectType;}

    //SETTERS
    void setColor(glm::vec3 c) {color = c;}
    void setPosition(glm::vec3 pos) {model = glm::translate(glm::mat4(1.0f), pos); position = pos;}
    void setRotation(float angle, glm::vec3 axis){model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
                                                 this->angle = angle, rotation = axis;}

protected:
    //ATTRIBUTES
    float angle = 0;
    glm::vec3 color = glm::vec3(1,1,1);
    glm::vec3 position = glm::vec3(0,0,0);
    glm::vec3 rotation = glm::vec3(0,0,0);
    glm::mat4 model = glm::mat4(1.0f);
    ObjectType objectType;

    std::vector<float> vertices;
};

#endif // DRAWABLEOBJECT

