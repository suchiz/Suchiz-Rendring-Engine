#ifndef ANIMATEDMODEL_H
#define ANIMATEDMODEL_H

#include <glad/glad.h>
#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"
#include <QString>
#include <vector>
#include "../Objects/drawableobject.h"
#include "bone.h"
#include <iostream>
#include <map>

class AnimatedModel
{
public:
    //CONSTRUCTOR
    AnimatedModel(DrawableObject *model, Bone* rootBone, std::vector<Bone*> skeleton);

    //FUNCTIONS
    void computeWeights(float smooth);

    //GETTERS
    DrawableObject* getModel() const {return model;}
    Bone* getRootBone() const {return rootBone;}
    Bone* getBone(QString name){for (Bone *b :skeleton) if (b->getName() == name) return b; return NULL;}
    std::vector<Bone*> getSkeleton() const {return skeleton;}
    std::vector<glm::mat4> getU_inv() const {return U_inv;}
    int getNbBones() const {return nbBones;}
    std::vector<float> getWeights() const {return weights;}

private:
    //ATTRIBUTES
    DrawableObject *model;
    Bone* rootBone;
    int nbBones;
    std::vector<float> weights;
    std::vector<Bone*> skeleton;
    std::vector<glm::mat4> U_inv;
};

#endif // ANIMATEDMODEL_H
