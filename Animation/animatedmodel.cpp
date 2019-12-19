#include "animatedmodel.h"

AnimatedModel::AnimatedModel(DrawableObject *model, Bone* rootBone, std::vector<Bone*> skeleton)
{
    this->model = model;
    this->nbBones = skeleton.size();
    this->rootBone = rootBone;
    this->skeleton = skeleton;
    this->originalVertices = model->getVertices();
    rootBone->calcInverseRestTransform(glm::mat4(1.0f));
    for (Bone *b : skeleton)
        U_inv.push_back(b->getInverseRestTransform());

}

void AnimatedModel::computeWeights(float smooth)
{
    Bone* child = rootBone->getChildren()[0];
    std::vector<float> weightRoot;
    std::vector<float> weightChild;
    for (unsigned int i = 0; i < originalVertices.size(); i+=6){
        float dist = glm::smoothstep(child->getPosition()[2]-smooth, rootBone->getPosition()[2]+smooth,  originalVertices[i+2]);
        weightRoot.push_back(dist);
        weightChild.push_back(1-dist);
        weightsForGPU.push_back(dist);
        weightsForGPU.push_back(1-dist);
    }
    weights.insert(std::pair<Bone*, std::vector<float>>{rootBone, weightRoot});
    weights.insert(std::pair<Bone*, std::vector<float>>{child, weightChild});
}

void AnimatedModel::updateModelVerticeLBS()
{
    std::vector<float> oldvertices = originalVertices;
    std::vector<float> newvertices;

    for (unsigned int i = 0, j = 0; i < oldvertices.size(); ++j, i+=6){
        glm::vec3 pos = glm::vec3(oldvertices[i], oldvertices[i+1], oldvertices[i+2]);
        glm::vec4 currentVertex = glm::vec4(pos, 1.0f);
        glm::vec4 newVertex= glm::vec4(0.f);

        for (std::pair<Bone*, std::vector<float>> it : weights)
            newVertex += it.second[j]*it.first->getAnimatedTransform()*it.first->getInverseRestTransform()* currentVertex;

        newvertices.push_back(newVertex.x);
        newvertices.push_back(newVertex.y);
        newvertices.push_back(newVertex.z);
        newvertices.push_back(oldvertices[i+3]);
        newvertices.push_back(oldvertices[i+4]);
        newvertices.push_back(oldvertices[i+5]);
    }
    model->setVertices(newvertices);
}



