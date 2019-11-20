#include "bspline.h"

BSpline::BSpline(std::vector<glm::vec3> controlPointsVect, KVType knotVectType, int order){
    this->controlPointsVect = controlPointsVect;
    this->knotVectType = knotVectType;
    this->order = order;
    checkParameters();
    computeKnotVect(knotVectType, order);
}

void BSpline::checkParameters(){
    assert(getNBControlPoints()>=order);
    assert(order > 1);
}

std::vector<glm::vec3> BSpline::computePoint(float du, std::vector<float> w){
    std::vector<glm::vec3> calculatedPoints;
    float start, end;
    if (this->knotVectType == KVType::UNIFORM){
        start = this->order-1;
        end = getNBControlPoints();
    } else if (this->knotVectType == KVType::OPEN_UNIFORM){
        start = this->order-1 - getDegree();
        end = getNBControlPoints() - getDegree();
    }
    for (float u = start; u < end; u+=du){
        int offset = getIndexInterestPoint(u);
        std::vector<glm::vec3> interestPointsVect;
        for (int i = 0; i < this->order; ++i)
            interestPointsVect.push_back(controlPointsVect[i+offset]);

        int k = this->order;
        for (int j = 0; j < this->order-1; ++j){
            for (int i = 0; i < k-1; ++i){
                float denom = knotVect[offset+k+i] - knotVect[offset+1+i];
                interestPointsVect[i] = interestPointsVect[i] * ((knotVect[offset+k+i] - u) / denom) +
                                interestPointsVect[i+1] * ((u - knotVect[offset+1+i]) / denom);
            }
            --k;
            ++offset;
        }
        calculatedPoints.push_back(interestPointsVect[0]);
    }
    return calculatedPoints;
}

void BSpline::draw(float du){
    //std::vector<glm::vec3> curvePoints = computePoint(du);
}

void BSpline::printControlPointsVect(){
    for (int i = 0; i < this->controlPointsVect.size(); ++i)
        std::cout << "[" << this->controlPointsVect[i].x << "," <<
                this->controlPointsVect[i].y << "," <<
                this->controlPointsVect[i].z << "]" << std::endl;
}

void BSpline::printKnotVect(){
    for (int i = 0; i < this->knotVect.size(); ++i)
        std::cout << this->knotVect[i];
    std::cout<<std::endl;
}


int BSpline::getIndexInterestPoint(float u){
    int offset = 0;
    for (int i = this->order; knotVect[i] < u; ++i)
        ++offset;
    return offset;
}

void BSpline::computeKnotVect(KVType knotVectType, int order){
    if (knotVectType == KVType::UNIFORM){
        for (int i = 0; i < getNBControlPoints()+order; ++i)
            this->knotVect.push_back(i);
    } else if (knotVectType == KVType::OPEN_UNIFORM){
        int val = 1;
        for (int i = 0; i < getNBControlPoints()+order; ++i)
            if (i < order){
                this->knotVect.push_back(0);
            } else if (i < getNBControlPoints()) {
                this->knotVect.push_back(val);
                ++val;
            } else {
                this->knotVect.push_back(val);
            }

    } else {
        std::cout << "Not available yet" << std::endl;
    }
}
