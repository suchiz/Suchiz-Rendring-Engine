#include "cube.h"

Cube::Cube(float size)
{
    float init[] = {
        -0.5f*size, -0.5f*size, -0.5f*size,  0.0f,  0.0f, -1.0f,
         0.5f*size, -0.5f*size, -0.5f*size,  0.0f,  0.0f, -1.0f,
         0.5f*size,  0.5f*size, -0.5f*size,  0.0f,  0.0f, -1.0f,
         0.5f*size,  0.5f*size, -0.5f*size,  0.0f,  0.0f, -1.0f,
        -0.5f*size,  0.5f*size, -0.5f*size,  0.0f,  0.0f, -1.0f,
        -0.5f*size, -0.5f*size, -0.5f*size,  0.0f,  0.0f, -1.0f,

        -0.5f*size, -0.5f*size,  0.5f*size,  0.0f,  0.0f,  1.0f,
         0.5f*size, -0.5f*size,  0.5f*size,  0.0f,  0.0f,  1.0f,
         0.5f*size,  0.5f*size,  0.5f*size,  0.0f,  0.0f,  1.0f,
         0.5f*size,  0.5f*size,  0.5f*size,  0.0f,  0.0f,  1.0f,
        -0.5f*size,  0.5f*size,  0.5f*size,  0.0f,  0.0f,  1.0f,
        -0.5f*size, -0.5f*size,  0.5f*size,  0.0f,  0.0f,  1.0f,

        -0.5f*size,  0.5f*size,  0.5f*size, -1.0f,  0.0f,  0.0f,
        -0.5f*size,  0.5f*size, -0.5f*size, -1.0f,  0.0f,  0.0f,
        -0.5f*size, -0.5f*size, -0.5f*size, -1.0f,  0.0f,  0.0f,
        -0.5f*size, -0.5f*size, -0.5f*size, -1.0f,  0.0f,  0.0f,
        -0.5f*size, -0.5f*size,  0.5f*size, -1.0f,  0.0f,  0.0f,
        -0.5f*size,  0.5f*size,  0.5f*size, -1.0f,  0.0f,  0.0f,

         0.5f*size,  0.5f*size,  0.5f*size,  1.0f,  0.0f,  0.0f,
         0.5f*size,  0.5f*size, -0.5f*size,  1.0f,  0.0f,  0.0f,
         0.5f*size, -0.5f*size, -0.5f*size,  1.0f,  0.0f,  0.0f,
         0.5f*size, -0.5f*size, -0.5f*size,  1.0f,  0.0f,  0.0f,
         0.5f*size, -0.5f*size,  0.5f*size,  1.0f,  0.0f,  0.0f,
         0.5f*size,  0.5f*size,  0.5f*size,  1.0f,  0.0f,  0.0f,

        -0.5f*size, -0.5f*size, -0.5f*size,  0.0f, -1.0f,  0.0f,
         0.5f*size, -0.5f*size, -0.5f*size,  0.0f, -1.0f,  0.0f,
         0.5f*size, -0.5f*size,  0.5f*size,  0.0f, -1.0f,  0.0f,
         0.5f*size, -0.5f*size,  0.5f*size,  0.0f, -1.0f,  0.0f,
        -0.5f*size, -0.5f*size,  0.5f*size,  0.0f, -1.0f,  0.0f,
        -0.5f*size, -0.5f*size, -0.5f*size,  0.0f, -1.0f,  0.0f,

        -0.5f*size,  0.5f*size, -0.5f*size,  0.0f,  1.0f,  0.0f,
         0.5f*size,  0.5f*size, -0.5f*size,  0.0f,  1.0f,  0.0f,
         0.5f*size,  0.5f*size,  0.5f*size,  0.0f,  1.0f,  0.0f,
         0.5f*size,  0.5f*size,  0.5f*size,  0.0f,  1.0f,  0.0f,
        -0.5f*size,  0.5f*size,  0.5f*size,  0.0f,  1.0f,  0.0f,
        -0.5f*size,  0.5f*size, -0.5f*size,  0.0f,  1.0f,  0.0f
    };

    for (int i(0); i < 216; ++i)
        vertices.push_back(init[i]);
    glad_glGenBuffers(1, &VBO);
    objectType = CUBE;
}

void Cube::bind()
{
    glad_glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glad_glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

void Cube::enableVertices(unsigned int position)
{
    glad_glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glad_glEnableVertexAttribArray(position);
}

void Cube::enableNormals(unsigned int position)
{
    glad_glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glad_glEnableVertexAttribArray(position);
}

void Cube::draw()
{
    bind();
    enableVertices(0);
    enableNormals(1);
    glad_glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glad_glDrawArrays(GL_TRIANGLES, 0, 36);
}
