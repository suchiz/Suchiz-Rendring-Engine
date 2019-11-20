#include "plane.h"

Plane::Plane(float size)
{
    float init[] = {
        // positions            // normals
         1.0f*size, -0.5f,  1.0f*size,  0.0f, 1.0f, 0.0f,
        -1.0f*size, -0.5f,  1.0f*size,  0.0f, 1.0f, 0.0f,
        -1.0f*size, -0.5f, -1.0f*size,  0.0f, 1.0f, 0.0f,

         1.0f*size, -0.5f,  1.0f*size,  0.0f, 1.0f, 0.0f,
        -1.0f*size, -0.5f, -1.0f*size,  0.0f, 1.0f, 0.0f,
         1.0f*size, -0.5f, -1.0f*size,  0.0f, 1.0f, 0.0f,
    };

    for (int i(0); i < 36; ++i)
        vertices[i] = init[i];
    glad_glGenBuffers(1, &VBO);
    model = glm::mat4(1.0f);
    objectType = PLANE;
    setColor(glm::vec3(1,1,1));
    setPosition(glm::vec3(0,0,0));
}

void Plane::bind()
{
    glad_glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Plane::enableVertices(unsigned int position)
{
    glad_glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glad_glEnableVertexAttribArray(position);
}
void Plane::enableNormals(unsigned int position)
{
    glad_glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glad_glEnableVertexAttribArray(position);
}

void Plane::draw()
{
    bind();
    enableVertices(0);
    enableNormals(1);
    glad_glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glad_glDrawArrays(GL_TRIANGLES, 0, 36);
}
