#include "capsule.h"
#include <iostream>
Capsule::Capsule(QString name)
{
    this->name = name;
    glad_glGenBuffers(1, &VBO);
    glad_glGenBuffers(1, &EBO);
    objectType = CAPSULE;
    buildUnitCircleVertices();
    buildVerticesSmooth();
}

void Capsule::clearArrays()
{
    std::vector<float>().swap(vertices);
    std::vector<unsigned int>().swap(indices);
}

void Capsule::buildVerticesSmooth()
{
    clearArrays();

    float x, y, z;                                  // vertex position
    float radius;                                   // radius for each stack

    std::vector<float> sideNormals = getSideNormals();

    for(int i = 0; i <= stackCount; ++i)
    {
        z = -(height * 0.5f) + (float)i / stackCount * height;      // vertex position z
        radius = baseRadius + (float)i / stackCount * (topRadius - baseRadius);     // lerp

        for(int j = 0, k = 0; j <= sectorCount; ++j, k += 3)
        {
            x = unitCircleVertices[k];
            y = unitCircleVertices[k+1];
            vertices.push_back(x*radius);
            vertices.push_back(y*radius);
            vertices.push_back(z);
            vertices.push_back(sideNormals[k]);
            vertices.push_back(sideNormals[k+1]);
            vertices.push_back(sideNormals[k+2]);
        }
    }

    // remember where the base.top vertices start
    unsigned int baseVertexIndex = (unsigned int)vertices.size() / 6;

    // put vertices of base of cylinder
    z = -height * 0.5f;
    vertices.push_back(0);
    vertices.push_back(0);
    vertices.push_back(z);
    vertices.push_back(0);
    vertices.push_back(0);
    vertices.push_back(-1);

    for(int i = 0, j = 0; i < sectorCount; ++i, j += 3){
        x = unitCircleVertices[j];
        y = unitCircleVertices[j+1];
        vertices.push_back(x * baseRadius);
        vertices.push_back(y * baseRadius);
        vertices.push_back(z);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(-1);
    }

    // remember where the base vertices start
    unsigned int topVertexIndex = (unsigned int)vertices.size() / 6;

    // put vertices of top of cylinder
    z = height * 0.5f;
    vertices.push_back(0);
    vertices.push_back(0);
    vertices.push_back(z);
    vertices.push_back(0);
    vertices.push_back(0);
    vertices.push_back(1);

    for(int i = 0, j = 0; i < sectorCount; ++i, j += 3)
    {
        x = unitCircleVertices[j];
        y = unitCircleVertices[j+1];
        vertices.push_back(x * topRadius);
        vertices.push_back(y * topRadius);
        vertices.push_back(z);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(1);
    }

    // put indices for sides
    unsigned int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // bebinning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 trianles per sector
            addIndices(k1, k1 + 1, k2);
            addIndices(k2, k1 + 1, k2 + 1);
        }
    }

    // remember where the base indices start
    baseIndex = (unsigned int)indices.size();

    // put indices for base
    for(int i = 0, k = baseVertexIndex + 1; i < sectorCount; ++i, ++k)
    {
        if(i < (sectorCount - 1))
            addIndices(baseVertexIndex, k + 1, k);
        else    // last triangle
            addIndices(baseVertexIndex, baseVertexIndex + 1, k);
    }

    // remember where the base indices start
    topIndex = (unsigned int)indices.size();

    for(int i = 0, k = topVertexIndex + 1; i < sectorCount; ++i, ++k)
    {
        if(i < (sectorCount - 1))
            addIndices(topVertexIndex, k, k + 1);
        else
            addIndices(topVertexIndex, k, topVertexIndex + 1);
    }
}

void Capsule::buildUnitCircleVertices()
{
    const float PI = 3.1415926f;
    float sectorStep = 2 * PI / sectorCount;
    float sectorAngle;  // radian

    for(int i = 0; i <= sectorCount; ++i)
    {
        sectorAngle = i * sectorStep;
        unitCircleVertices.push_back(cos(sectorAngle)); // x
        unitCircleVertices.push_back(sin(sectorAngle)); // y
        unitCircleVertices.push_back(0);                // z
    }
}

void Capsule::addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
{
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
}

std::vector<float> Capsule::getSideNormals()
{
    const float PI = 3.1415926f;
    float sectorStep = 2 * PI / sectorCount;
    float sectorAngle;  // radian

    float zAngle = atan2(baseRadius - topRadius, height);
    float x0 = cos(zAngle);     // nx
    float y0 = 0;               // ny
    float z0 = sin(zAngle);     // nz

    // rotate (x0,y0,z0) per sector angle
    std::vector<float> normals;
    for(int i = 0; i <= sectorCount; ++i)
    {
        sectorAngle = i * sectorStep;
        normals.push_back(cos(sectorAngle)*x0 - sin(sectorAngle)*y0);   // nx
        normals.push_back(sin(sectorAngle)*x0 + cos(sectorAngle)*y0);   // ny
        normals.push_back(z0);  // nz
    }

    return normals;
}

void Capsule::bind()
{
    glad_glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glad_glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Capsule::enableVertices(unsigned int position)
{
    glad_glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glad_glEnableVertexAttribArray(position);
}
void Capsule::enableNormals(unsigned int position)
{
    glad_glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glad_glEnableVertexAttribArray(position);
}

void Capsule::draw()
{
    bind();
    enableVertices(0);
    enableNormals(1);
    if (wire)
        glad_glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    else
        glad_glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glad_glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT,0);
}

