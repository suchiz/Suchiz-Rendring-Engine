#ifndef CAPSULE_H
#define CAPSULE_H

#include "drawableobject.h"
#include "vector"

class Capsule : public DrawableObject
{
public:
    //CONSTRUCTORS
    Capsule(QString name);

    //OPENGL FUNCTIONS
    void enableVertices(unsigned int position);
    void enableNormals(unsigned int position);
    void draw();
    void drawAnim();
    void bind();
    void enableWeights(unsigned int position);

    //FUNCTIONS
    void clearArrays();
    void buildVerticesSmooth();
    void buildUnitCircleVertices();
    void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);
    void buildInterleavedWeights(std::vector<float> weights);
    std::vector<float> getSideNormals();

private:
    unsigned int EBO;
    const int sectorCount = 36;
    const int stackCount = 18;
    const float baseRadius = 0.5f;
    const float topRadius = 0.5f;
    const float height = 6;
    unsigned int baseIndex;                 // starting index of base
    unsigned int topIndex;
    std::vector<float> unitCircleVertices;
    std::vector<unsigned int> indices;
    std::vector<float> interleavedVertices;


};

#endif // CAPSULE_H
