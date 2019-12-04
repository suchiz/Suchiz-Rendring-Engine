#ifndef DEPTHMAP_H
#define DEPTHMAP_H

#include <iostream>
#include <glad/glad.h>
#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"

#include <vector>

#include "../Scene/shader.h"
#include "../Objects/drawableobject.h"
#include "../Scene/scene.h"

class DepthMap
{
public:
    //CONSTRUTORS
    DepthMap(Scene *scene);

    //OPENGL FUNCTIONS
    void generateDepthMap();
    void bindTexture();

    //GETTERS
    glm::mat4 getLightSpaceMatrix() const {return lightSpaceMatrix;}
    unsigned int getDepthTexture() const {return depthTexture;}

private:
    Scene *scene;
    unsigned int FBO, depthTexture;
    glm::mat4 lightSpaceMatrix;
    Shader *depthShader;
    int width = 2048;
    int height = 2048;
    float borderColor[4] = { 1.0, 1.0, 1.0, 1.0 };
    float near_plane = 1.0f, far_plane = 7.5f;
};

#endif // DEPTHMAP_H
