#ifndef DRAWABLEOBJECT
#define DRAWABLEOBJECT
#include <glad/glad.h>
#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"
#include <vector>
#include <QString>

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
    void updateModel(){model = glm::mat4(1.0f);
                       model = glm::translate(model, position);
                       model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
                       model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
                       model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
                       model = glm::scale(model, scale);}

    //GETTERS
    glm::vec3 getPosition() const {return position;}
    glm::vec3 getRotation() const {return rotation;}
    glm::vec3 getSize() const {return scale;}
    glm::mat4 getModel() const {return model;}
    glm::vec3 getColor() const {return color;}
    std::vector<float> getVertices() const {return vertices;}
    ObjectType getType() const {return objectType;}
    QString getName() const {return name;}
    bool getWire() const {return wire;}
    unsigned int getVBO() const {return VBO;}

    //SETTERS
    void setColor(glm::vec3 c) {color = c;}
    void setVertices(std::vector<float> vertices) {this->vertices = vertices;}
    void setPosition(glm::vec3 pos) {position = pos; updateModel();}
    void setRotation(glm::vec3 rot) {rotation = rot; updateModel();}
    void setSize(glm::vec3 size) {scale = size; updateModel();}
    void setWire(bool b) {wire = b;}
    void setName(QString n) {name = n;}

protected:
    //ATTRIBUTES
    unsigned int VBO;
    bool wire = false;
    QString name;
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 color = glm::vec3(1.0f);
    glm::vec3 position = glm::vec3(0.f);
    glm::vec3 rotation = glm::vec3(0.f);
    glm::mat4 model = glm::mat4(1.0f);
    ObjectType objectType;

    std::vector<float> vertices;
};

#endif // DRAWABLEOBJECT

