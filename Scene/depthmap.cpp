#include "depthmap.h"

DepthMap::DepthMap(Scene *scene): scene(scene)
{
    glad_glGenFramebuffers(1, &FBO);
    glad_glGenTextures(1, &depthTexture);

    glad_glBindTexture(GL_TEXTURE_2D, depthTexture);
    glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glad_glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glad_glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glad_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glad_glDrawBuffer(GL_NONE);
    glad_glReadBuffer(GL_NONE);
    glad_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    depthShader = new Shader(DEPTH);
}

void DepthMap::generateDepthMap()
{
    glm::vec3 lightPos = scene->getLight().getPosition();
    glm::mat4 lightProjection, lightView;
    std::vector<DrawableObject*> objectsToDraw = scene->getObjectsToDraw();

    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;

    depthShader->use();
    depthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

    glad_glViewport(0, 0, width, height);
    glad_glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glad_glClear(GL_DEPTH_BUFFER_BIT);
        for(unsigned int i(0); i < objectsToDraw.size(); ++i){
            depthShader->setMat4("model", objectsToDraw[i]->getModel());
            objectsToDraw[i]->draw();
        }
    glad_glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DepthMap::bindTexture()
{
    glad_glActiveTexture(GL_TEXTURE0);
    glad_glBindTexture(GL_TEXTURE_2D, depthTexture);
}

