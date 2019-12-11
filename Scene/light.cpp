#include "light.h"

Light::Light(): Cube("Light")
{
    lightShader = new Shader(LIGHT);
    setPosition(glm::vec3(distance*cos(angle), height, distance*sin(angle)));
    setSize(glm::vec3(0.1f));
}

void Light::updatePosition()
{
    this->setPosition(glm::vec3(distance*cos(angle), height, distance*sin(angle)));
    angle += 0.01;
    if (angle > 20)
        angle = 0;
}

void Light::draw(Camera *camera)
{
    lightShader->use();
    lightShader->setMat4("projection", camera->getProjectionMatrix());
    lightShader->setMat4("view", camera->GetViewMatrix());
    lightShader->setMat4("model", model);
    lightShader->setVec3("color", glm::vec3(1.0f));
    bind();
    enableVertices(0);
    glad_glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glad_glDrawArrays(GL_TRIANGLES, 0, 36);
}

