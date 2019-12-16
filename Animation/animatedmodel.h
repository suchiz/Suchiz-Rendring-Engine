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

class AnimatedModel
{
public:
    //CONSTRUCTOR
    AnimatedModel(DrawableObject *model, std::vector<Bone*> skeleton);

    //FUNCTIONS
    void computeWeights(float smooth);
    void updateModelVertice();

    //GETTERS
    DrawableObject* getModel() const {return model;}
    std::vector<Bone*> getSkeleton() const {return skeleton;}

private:
    //ATTRIBUTES
    DrawableObject *model;
    std::vector<Bone*> skeleton;
    int nbBones;
    std::vector<std::vector<float> > weights;
    std::vector<float> originalVertices;
};

#endif // ANIMATEDMODEL_H
