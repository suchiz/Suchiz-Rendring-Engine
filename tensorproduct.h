#ifndef TENSORPRODUCT_H
#define TENSORPRODUCT_H

#include "bspline.h"
#include <QString>
#include "drawableobject.h"

class TensorProduct: DrawableObject
{
private:
    //ATTRIBUTES
    unsigned int VBO, EBO;
    std::vector<unsigned int> indices;
    std::vector<float> interVertices;
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> normals;
    glm::vec3 color;
    glm::vec3 position;
    glm::mat4 model;

    std::vector<std::vector<glm::vec3>> generatrixVect;
    std::vector<std::vector<glm::vec3>> guidelinesVect;
    std::vector<glm::vec3> controlPointsVect;
    std::vector<float> weights;
    std::pair<int, int> size;
    KVType knotVectType;
    int order;
    QString name;

    //METHODS
    void checkParameters();
    void computePoint(float du, float dv);
    std::vector<float> getWeightatInd(int ind);

public:
    //CONSTRUCTOR
    TensorProduct(QString name, std::pair<int, int> size, std::vector<glm::vec3> controlPoints);

    //METHODS
    void draw();
    void update();
    void updatePoint(int x, int y, glm::vec3 pt);
    void buildControlPoints();
    void buildGeometry();
    void buildinterVertices();
    void buildDemo();
    void bind();
    void enableVertices(unsigned int position);
    void enableNormals(unsigned int position);
    void setPosition(glm::vec3 pos) {model = glm::translate(model, pos); position = pos;}
    void setRotation(float angle, glm::vec3 axis){model = glm::rotate(model, glm::radians(angle), axis);}
    void setColor(glm::vec3 c) {color = c;}


    //GETTERS
    int getOrder(){ return order;}
    std::pair<int,int> getSize(){ return size;}
    int getNBControlPoints(){ return controlPointsVect.size();}
    std::vector<glm::vec3> getControlPointsVect(){ return controlPointsVect;}
    std::vector<glm::vec3> getGuidelinePoints(int ind);
    std::vector<glm::vec3> getGeneratrixPoints(int ind, std::vector<std::vector<glm::vec3>> guidelinesVect);
    QString getName() const{return name;}
    glm::vec3 getPosition() const {return position;}
    glm::mat4 getModel() const {return model;}
    glm::vec3 getColor() const {return color;}
};

#endif // TENSORPRODUCT_H
