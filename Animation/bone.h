#ifndef BONE_H
#define BONE_H

#include <glad/glad.h>
#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"
#include <QString>
#include <vector>
#include "../Objects/cube.h"

class Bone
{
public:
    //CONSTRUCTOR
    Bone(int ID, QString name, glm::mat4 bindLocalTransform);

    //FUNCTIONS
    void calcInverseRestTransform(glm::mat4 parentBindTransform);
    void addChildren(Bone *bone) {children.push_back(bone);}
    void roll(float val);
    void pitch(float val);
    void yaw(float val);
    void translate_x(float val);
    void translate_y(float val);
    void translate_z(float val);

    //SETTERS
    void setPosition(glm::vec3 pos){position = pos;}
    void setAnimatedTransform(glm::mat4 animationTransform) {this->animatedTransform = animationTransform;}
    void updateModel();

    //GETTERS
    glm::mat4 getAnimatedTransform() const {return animatedTransform;}
    glm::mat4 getInverseRestTransform() const {return inverseRestTransform;}
    std::vector<Bone*> getChildren() const {return children;}
    int getID() const {return ID;}
    glm::vec3 getPosition() const {return position;}
    glm::vec3 getRotation() const {return rotation;}
    QString getName() const {return name;}
    Cube* getCube() const {return cube;}

private:
    //ATTRIBUTES
    int ID;
    QString name;
    Cube *cube;
    std::vector<Bone*> children;
    glm::mat4 animatedTransform = glm::mat4(1.0f);
    glm::mat4 inverseRestTransform = glm::mat4(1.0f);
    glm::mat4 restTransform;
    glm::vec3 position = glm::vec3(0.f);
    glm::vec3 rotation = glm::vec3(0.f);
};

#endif // BONE_H
