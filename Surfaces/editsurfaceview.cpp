#include "editsurfaceview.h"

EditSurfaceView::EditSurfaceView(QWidget *parent): Scene(parent)
{

}

void EditSurfaceView::initializeGL()
{
    glad_glEnable(GL_DEPTH_TEST);
    camera = new Camera();
    camera->setProjectionMatrix(size().width(), size().height());
    objectShader = new Shader(LIGHT);
    glad_glGenVertexArrays(1, &objectsVAO);
}

void EditSurfaceView::paintGL()
{
    glad_glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glad_glBindVertexArray(objectsVAO);
    objectShader->use();
    objectShader->setMat4("projection", camera->getProjectionMatrix());
    objectShader->setMat4("view", camera->GetViewMatrix());

    for(unsigned int i(0); i < objectsToDraw.size(); ++i){
        objectShader->setMat4("model", objectsToDraw[i]->getModel());
        objectShader->setVec3("color", objectsToDraw[i]->getColor());
        objectsToDraw[i]->draw();
    }
}

void EditSurfaceView::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
    case Qt::Key_Z:
        if (cubeSelected){
            for(unsigned int i(0); i < selectedCubes.size(); ++i){
                glm::vec3 oldpos = selectedCubes[i]->getPosition();
                glm::vec3 newpos =glm::vec3(oldpos.x + 0.1, oldpos.y, oldpos.z);
                selectedCubes[i]->setPosition(newpos);
                currentTp->updatePoint(indices[i], newpos);
            }
            currentTp->update();
        }else
            camera->ProcessKeyboard(FORWARD);
        updateGL();
        break;
    case Qt::Key_S:
        if (cubeSelected){
            for(unsigned int i(0); i < selectedCubes.size(); ++i){
                glm::vec3 oldpos = selectedCubes[i]->getPosition();
                glm::vec3 newpos =glm::vec3(oldpos.x - 0.1, oldpos.y, oldpos.z);
                selectedCubes[i]->setPosition(newpos);
                currentTp->updatePoint(indices[i], newpos);
            }
            currentTp->update();
        }else
            camera->ProcessKeyboard(BACKWARD);
        updateGL();
        break;
    case Qt::Key_Q:
        if (cubeSelected){
            for(unsigned int i(0); i < selectedCubes.size(); ++i){
                glm::vec3 oldpos = selectedCubes[i]->getPosition();
                glm::vec3 newpos =glm::vec3(oldpos.x, oldpos.y, oldpos.z+0.1);
                selectedCubes[i]->setPosition(newpos);
                currentTp->updatePoint(indices[i], newpos);
            }
            currentTp->update();
        }else
            camera->ProcessKeyboard(LEFT);
        updateGL();
        break;
    case Qt::Key_D:
        if (cubeSelected){
            for(unsigned int i(0); i < selectedCubes.size(); ++i){
                glm::vec3 oldpos = selectedCubes[i]->getPosition();
                glm::vec3 newpos =glm::vec3(oldpos.x, oldpos.y, oldpos.z-0.1);
                selectedCubes[i]->setPosition(newpos);
                currentTp->updatePoint(indices[i], newpos);
            }
            currentTp->update();
        }else
            camera->ProcessKeyboard(RIGHT);
        updateGL();
        break;
    case Qt::Key_T:
        if (cubeSelected){
            for(unsigned int i(0); i < selectedCubes.size(); ++i){
                glm::vec3 oldpos = selectedCubes[i]->getPosition();
                glm::vec3 newpos =glm::vec3(oldpos.x, oldpos.y+0.1, oldpos.z);
                selectedCubes[i]->setPosition(newpos);
                currentTp->updatePoint(indices[i], newpos);
            }
            currentTp->update();
        }
        break;
    case Qt::Key_B:
        if (cubeSelected){
            for(unsigned int i(0); i < selectedCubes.size(); ++i){
                glm::vec3 oldpos = selectedCubes[i]->getPosition();
                glm::vec3 newpos =glm::vec3(oldpos.x, oldpos.y-0.1, oldpos.z);
                selectedCubes[i]->setPosition(newpos);
                currentTp->updatePoint(indices[i], newpos);
            }
            currentTp->update();
        }
        break;
    }
}
