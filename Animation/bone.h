#ifndef BONE_H
#define BONE_H

#include <glad/glad.h>
#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"
#include <QString>
#include <vector>

class Bone
{
public:
    //CONSTRUCTOR
    Bone(int ID, QString name, glm::mat4 bindLocalTransform);

    //FUNCTIONS
    void calcInverseRestTransform(glm::mat4 parentBindTransform);
    void addChildren(Bone *bone) {children.push_back(bone);}
    void roll(float val){rotation.x += val; updateModel();}
    void pitch(float val){rotation.y += val; updateModel();}
    void yaw(float val){rotation.z += val; updateModel();}

    //SETTERS
    void setPosition(glm::vec3 pos){position = pos;}
    void setAnimatedTransform(glm::mat4 animationTransform) {this->animatedTransform = animationTransform;}
    void updateModel() {animatedTransform = glm::mat4(1.0f);
                                     animatedTransform = glm::rotate(animatedTransform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
                                     animatedTransform = glm::rotate(animatedTransform, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
                                     animatedTransform = glm::rotate(animatedTransform, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));}

    //GETTERS
    glm::mat4 getAnimatedTransform() const {return animatedTransform;}
    glm::mat4 getInverseRestTransform() const {return inverseRestTransform;}
    std::vector<Bone*> getChildren() const {return children;}
    int getID() const {return ID;}
    glm::vec3 getPosition() const {return position;}
    QString getName() const {return name;}

private:
    //ATTRIBUTES
    int ID;
    QString name;
    std::vector<Bone*> children;
    glm::mat4 animatedTransform = glm::mat4(1.0f);
    glm::mat4 inverseRestTransform = glm::mat4(1.0f);
    glm::mat4 restTransform;
    glm::vec3 position = glm::vec3(0.f);
    glm::vec3 rotation = glm::vec3(0.f);
};

#endif // BONE_H
