#ifndef BSPLINE_H
#define BSPLINE_H

#include <vector>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <glad/glad.h>
#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"

enum class KVType {UNIFORM, OPEN_UNIFORM, NON_UNIFORM};

class BSpline{
private:
    //ATTRIBUTES
    std::vector<glm::vec3> controlPointsVect;
    std::vector<float> knotVect;
    KVType knotVectType;
    int order = 0;

    //METHODS
    void checkParameters();
    int getIndexInterestPoint(float u);
    void computeKnotVect(KVType knotVectType, int order);

public:
    //CONSTRUCTOR
    BSpline(std::vector<glm::vec3> controlPointsVect, KVType knotVectType, int order);

    //METHODS
    std::vector<glm::vec3> computePoint(float du, std::vector<float> w);

    //DEBUG
    void printKnotVect();
    void printControlPointsVect();

    //GETTERS
    int getOrder(){ return order;}
    int getDegree(){ return order-1;}
    int getNBControlPoints(){ return controlPointsVect.size();}
    std::vector<glm::vec3> getControlPointsVect(){ return controlPointsVect;}
    std::vector<float> getKnotVect(){ return knotVect;}
};

#endif


