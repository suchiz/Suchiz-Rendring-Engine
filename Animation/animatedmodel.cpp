#include "animatedmodel.h"

AnimatedModel::AnimatedModel(DrawableObject *model, Bone* rootBone, std::vector<Bone*> skeleton)
{
    this->model = model;
    this->nbBones = skeleton.size();
    this->rootBone = rootBone;
    this->skeleton = skeleton;
    rootBone->calcInverseRestTransform(glm::mat4(1.0f));
    for (Bone *b : skeleton)
        U_inv.push_back(b->getInverseRestTransform());

}

void AnimatedModel::computeWeights(float smooth)
{
    std::vector<float> vertices = model->getVertices();
    for (unsigned int i = 0; i < vertices.size(); i+=6){
        float w_bone1 = glm::smoothstep(1-smooth, 2+smooth,  vertices[i+2]);
        float w21 = 1 - glm::smoothstep(1-smooth, 2+smooth,  vertices[i+2]);
        float w22 = glm::smoothstep(-2-smooth, -1+smooth,  vertices[i+2]);
        float w_bone2 = w21 * w22;
        float w_bone3 = 1 - glm::smoothstep(-1-smooth, 0+smooth,  vertices[i+2]);

        float sum = w_bone1 + w_bone2 + w_bone3;

        weights.push_back(w_bone1/sum);
        weights.push_back(w_bone2/sum);
        weights.push_back(w_bone3/sum);
    }
}



