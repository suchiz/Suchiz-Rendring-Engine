#ifndef TENSORPRODUCT_H
#define TENSORPRODUCT_H

#include "../Surfaces/bspline.h"
#include "../Objects/drawableobject.h"
#include <QString>

class TensorProduct: public DrawableObject
{
private:
    //ATTRIBUTES
    unsigned int VBO, EBO;
    std::vector<unsigned int> indices;
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> normals;

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

    //OPENGL FUNCTIONS
    void draw();
    void bind();
    void enableVertices(unsigned int position);
    void enableNormals(unsigned int position);

    //METHODS
    void update();
    void updatePoint(int x, int y, glm::vec3 pt);
    void buildControlPoints();
    void buildGeometry();
    void buildinterVertices();
    void buildDemo();


    //GETTERS
    int getOrder(){ return order;}
    std::pair<int,int> getSize(){ return size;}
    int getNBControlPoints(){ return controlPointsVect.size();}
    std::vector<glm::vec3> getControlPointsVect(){ return controlPointsVect;}
    std::vector<glm::vec3> getGuidelinePoints(int ind);
    std::vector<glm::vec3> getGeneratrixPoints(int ind, std::vector<std::vector<glm::vec3>> guidelinesVect);
    QString getName() const{return name;}
};

#endif // TENSORPRODUCT_H
