#include "animatedmodel.h"

AnimatedModel::AnimatedModel(DrawableObject *model, std::vector<Bone*> skeleton)
{
    this->model = model;
    this->nbBones = skeleton.size();
    this->skeleton = skeleton;
    this->originalVertices = model->getVertices();
}


void AnimatedModel::computeWeights(float smooth)
{
    weights.clear();
    std::vector<float> vertices = model->getVertices();
    for (unsigned int i = 0; i < vertices.size(); i+=6){
        std::vector<float> weightAti;
        float dist = glm::smoothstep(skeleton[0]->getPosition()[2]+smooth, skeleton[1]->getPosition()[2]-smooth, -vertices[i+2]);
        weightAti.push_back(dist);
        weightAti.push_back(1-dist);
        weights.push_back(weightAti);
    }
}

void AnimatedModel::updateModelVertice()
{
    std::vector<float> oldvertices = originalVertices;
    std::vector<float> newvertices;

    for (unsigned int i = 0, j = 0; i < oldvertices.size(); ++j, i+=6){
        glm::vec3 pos = glm::vec3(oldvertices[i], oldvertices[i+1], oldvertices[i+2]);
        glm::vec4 currentVertex = glm::vec4(pos, 1.0f);
        glm::vec4 newVertex= glm::vec4(0.f);

        for (int k = 0; k < nbBones; ++k)
            newVertex += weights[j][k]*skeleton[k]->getAnimatedTransform()*skeleton[k]->getInverseRestTransform()* currentVertex;

        newvertices.push_back(newVertex.x);
        newvertices.push_back(newVertex.y);
        newvertices.push_back(newVertex.z);
        newvertices.push_back(oldvertices[i+3]);
        newvertices.push_back(oldvertices[i+4]);
        newvertices.push_back(oldvertices[i+5]);
    }
    model->setVertices(newvertices);
}
