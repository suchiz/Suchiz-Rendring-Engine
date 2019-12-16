#include "bone.h"

Bone::Bone(int ID, QString name, glm::mat4 bindLocalTransform)
{
    this->ID = ID;
    this->name = name;
    this->restTransform = bindLocalTransform;
}

void Bone::calcInverseRestTransform(glm::mat4 parentBindTransform)
{
    glm::mat4 bindTransform = parentBindTransform * restTransform;
    inverseRestTransform = glm::inverse(bindTransform);
    for (unsigned int i(0); i < children.size(); ++i)
        children[i]->calcInverseRestTransform(bindTransform);
}
