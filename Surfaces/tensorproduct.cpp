#include "tensorproduct.h"

TensorProduct::TensorProduct(QString name, std::pair<int, int> size, KVType knotVectType, int order){
    this->name = name;
    this->order = order;
    this->size = size;
    this->knotVectType = knotVectType;
    this->objectType = SURFACE;
    glad_glGenBuffers(1, &VBO);
    glad_glGenBuffers(1, &EBO);

    for (int i(0); i < size.first*size.second; ++i)
        weights.push_back(1.0);

    buildControlPoints();
    checkParameters();
    computePoint(0.1, 0.1);
    buildGeometry();
    buildinterVertices();
}

void TensorProduct::computePoint(float du, float dv){
    for (int i = 0; i < this->size.first; ++i){
        BSpline guideSpline = BSpline(getGuidelinePoints(i), this->knotVectType, this->order);
        guidelinesVect.push_back(guideSpline.computePoint(du, getWeightatInd(i)));
    }

    for (unsigned int i = 0; i < guidelinesVect[0].size(); ++i){
        BSpline generatrixSpline = BSpline(getGeneratrixPoints(i, guidelinesVect), this->knotVectType, this->order);
        std::vector<glm::vec3> tmp = generatrixSpline.computePoint(dv, getWeightatInd(i));
        generatrixVect.push_back(tmp);
        for (unsigned int j(0); j < tmp.size(); ++j)
            points.push_back(tmp[j]);
    }
}

std::vector<float> TensorProduct::getWeightatInd(int ind){
    std::vector<float> weightsInterestedPoint;
    for (int i = 0; i < this->size.second; ++i)
        weightsInterestedPoint.push_back(this->weights[ind*this->size.second+i]);
    return weightsInterestedPoint;
}

std::vector<glm::vec3> TensorProduct::getGuidelinePoints(int ind){
    std::vector<glm::vec3> controlPointGuideline;
    for (int i = 0; i < this->size.second; ++i)
        controlPointGuideline.push_back(this->controlPointsVect[ind*this->size.second+i]);
    return controlPointGuideline;
}

std::vector<glm::vec3> TensorProduct::getGeneratrixPoints(int ind, std::vector<std::vector<glm::vec3>> guidelinesVect){
    std::vector<glm::vec3> controlPointsGeneratrix;
    for (int i = 0; i < this->size.first; ++i)
        controlPointsGeneratrix.push_back(guidelinesVect[i][ind]);
    return controlPointsGeneratrix;
}

void TensorProduct::checkParameters(){
    assert(getNBControlPoints() == size.first*size.second);
}

void TensorProduct::update()
{
    vertices.clear();
    normals.clear();
    points.clear();
    indices.clear();
    generatrixVect.clear();
    guidelinesVect.clear();
    checkParameters();
    computePoint(0.1, 0.1);
    buildGeometry();
    buildinterVertices();
}

void TensorProduct::updatePoint(int i, glm::vec3 pt)
{
    controlPointsVect[i] = pt;
    update();
}

void TensorProduct::buildControlPoints()
{
    for (int i(0); i < size.first; ++i)
        for (int j(0); j < size.second; ++j)
            controlPointsVect.push_back(glm::vec3(j+position.x, position.y, i+position.z));

}


void TensorProduct::buildGeometry()
{
    normals = std::vector<glm::vec3>(points.size());
    int gen_size = generatrixVect[0].size();

    for (unsigned int i = 0; i < normals.size(); ++i)
        normals[i] = glm::vec3(0, 0, 0);

    for (unsigned int i = 0; i < guidelinesVect[0].size() - 1; ++i){
        for (int j = 0; j < gen_size - 1; ++j){

            int cur = i*gen_size + j;

            indices.push_back(cur); indices.push_back(cur+1); indices.push_back(cur+gen_size+1);
            glm::vec3 edge1 = points[cur + 1] - points[cur];
            glm::vec3 edge2 = points[cur + gen_size + 1] - points[cur + 1];
            glm::vec3 normal = cross(edge1, edge2);
            normals[cur] += normal;
            normals[cur + 1] += normal;
            normals[cur + gen_size + 1] += normal;

            indices.push_back(cur); indices.push_back(cur+gen_size+1); indices.push_back(cur+gen_size);
            edge1 = points[cur + gen_size + 1] - points[cur];
            edge2 = points[cur + gen_size] - points[cur + gen_size + 1];
            normal = cross(edge1, edge2);
            normals[cur] += normal;
            normals[cur + gen_size] += normal;
            normals[cur + gen_size + 1] += normal;
        }
    }

    for (unsigned int i = 0; i < normals.size(); ++i)
        normals[i] = normalize(normals[i]);
}

void TensorProduct::buildinterVertices()
{
        for (unsigned int i = 0; i < normals.size(); i++){
            vertices.push_back(points[i].x);
            vertices.push_back(points[i].y);
            vertices.push_back(points[i].z);

            vertices.push_back(normals[i].x);
            vertices.push_back(normals[i].y);
            vertices.push_back(normals[i].z);
        }
}

void TensorProduct::bind()
{
    glad_glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glad_glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof (unsigned int), indices.data(), GL_STATIC_DRAW);
}

void TensorProduct::enableVertices(unsigned int position)
{
    glad_glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glad_glEnableVertexAttribArray(position);
}
void TensorProduct::enableNormals(unsigned int position)
{
    glad_glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glad_glEnableVertexAttribArray(position);
}

void TensorProduct::draw(){
    bind();
    enableVertices(0);
    enableNormals(1);
    if (wire)
        glad_glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
    else
        glad_glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
    glad_glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, 0);
}
