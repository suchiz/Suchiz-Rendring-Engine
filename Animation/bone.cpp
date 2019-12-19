#include "bone.h"

Bone::Bone(int ID, QString name, glm::mat4 bindLocalTransform)
{
    this->ID = ID;
    this->name = name;
    this->restTransform = bindLocalTransform;
    cube = new Cube(name);
    cube->setColor(glm::vec3(1,0,0));
    cube->setSize(glm::vec3(0.1f));
}

void Bone::calcInverseRestTransform(glm::mat4 parentBindTransform)
{
    glm::mat4 bindTransform = parentBindTransform * restTransform;
    inverseRestTransform = glm::inverse(bindTransform);
    for (unsigned int i(0); i < children.size(); ++i)
        children[i]->calcInverseRestTransform(bindTransform);
}

void Bone::roll(float val)
{
    rotation.x += val;
    for (Bone *b : children)
        b->roll(val);
    updateModel();
}

void Bone::pitch(float val)
{
    rotation.y += val;
    for (Bone *b : children)
        b->pitch(val);
    updateModel();
}

void Bone::yaw(float val)
{
    rotation.z += val;
    for (Bone *b : children)
        b->yaw(val);
    updateModel();
}

void Bone::translate_x(float val)
{
    position.x += val;
    for (Bone *b : children)
        b->translate_x(val);
    updateModel();
}
void Bone::translate_y(float val)
{
    position.y += val;
    for (Bone *b : children)
         b->translate_y(val);
    updateModel();
}
void Bone::translate_z(float val)
{
    position.z += val;
    for (Bone *b : children)
         b->translate_z(val);
    updateModel();
}

void Bone::updateModel()
{
    animatedTransform = glm::mat4(1.0f);
    animatedTransform = glm::translate(animatedTransform, position);
    animatedTransform = glm::rotate(animatedTransform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    animatedTransform = glm::rotate(animatedTransform, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    animatedTransform = glm::rotate(animatedTransform, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    cube->setPosition(position);
    cube->setRotation(rotation);
}
