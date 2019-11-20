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
        vertices[i] = init[i];
    glad_glGenBuffers(1, &VBO);
    model = glm::mat4(1.0f);
    objectType = CUBE;
    setColor(glm::vec3(1,1,1));
    setPosition(glm::vec3(0,0,0));
}

void Cube::copyData(DrawableObject obj){
    setPosition(obj.getPosition());
    setColor(obj.getColor());
    model = obj.getModel();
}

void Cube::bind()
{
    glad_glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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
