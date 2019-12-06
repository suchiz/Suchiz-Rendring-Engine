#include "sphere.h"

Sphere::Sphere(QString name)
{

    const float PI = 3.1415926f;
    float size = 1.0f;
    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / size;    // normal

    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stackCount; ++i){
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = size * cosf(stackAngle);             // r * cos(u)
        z = size * sinf(stackAngle);              // r * sin(u)
        for(int j = 0; j <= sectorCount; ++j){
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);
        }
    }

    unsigned int k1, k2;
    for(int i = 0; i < stackCount; ++i){
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2){
            if(i != 0)
                addIndices(k1, k2, k1+1);   // k1---k2---k1+1
            if(i != (stackCount-1))
                addIndices(k1+1, k2, k2+1); // k1+1---k2---k2+1
        }
    }

    glad_glGenBuffers(1, &VBO);
    glad_glGenBuffers(1, &EBO);
    objectType = SPHERE;
    this->name = name;
}

void Sphere::addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
{
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
}

void Sphere::bind()
{
    glad_glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glad_glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Sphere::buildTriangulation()
{
    for (unsigned int i(0); i < indices.size(); i += 3){
        triangledVertices.push_back(indices[i]);
        triangledVertices.push_back(indices[i+1]);
        triangledVertices.push_back(indices[i+2]);
    }

}

void Sphere::enableVertices(unsigned int position)
{
    glad_glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glad_glEnableVertexAttribArray(position);
}
void Sphere::enableNormals(unsigned int position)
{
    glad_glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glad_glEnableVertexAttribArray(position);
}

void Sphere::draw()
{
    bind();
    enableVertices(0);
    enableNormals(1);
    glad_glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glad_glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT,0);
}
