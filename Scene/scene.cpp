#include "scene.h"
#include "depthmap.h"
Scene::Scene(QWidget *parent)
    : OpenGLWindow(60, parent, "Suchiz' Rendering Engine")
{

}

void Scene::initializeGL()
{

    if (gladLoadGL()) {
        glad_glEnable(GL_DEPTH_TEST);
        objectShader = new Shader(BLINNPHONG);
        camera = new Camera();
        camera->setProjectionMatrix(size().width(), size().height());
        depthmap = new DepthMap(this);
        glad_glGenVertexArrays(1, &objectsVAO);
        light = new Light();

    } else {
        std::cout << "Error init glad" << std::endl;
    }

}

void Scene::resizeGL(int width, int height)
{
    camera->setProjectionMatrix(width, height);
}

void Scene::paintGL()
{
    glad_glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    depthmap->generateDepthMap();

    glad_glViewport(0, 0, size().width(), size().height());
    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glad_glBindVertexArray(objectsVAO);
    objectShader->use();
    objectShader->setVec3("lightPos", light->getPosition());
    objectShader->setVec3("viewPos", camera->Position);
    objectShader->setMat4("projection", camera->getProjectionMatrix());
    objectShader->setMat4("view", camera->GetViewMatrix());
    objectShader->setMat4("lightSpaceMatrix", depthmap->getLightSpaceMatrix());
    depthmap->bindTexture();

    for(unsigned int i(0); i < objectsToDraw.size(); ++i){
        objectShader->setMat4("model", objectsToDraw[i]->getModel());
        objectShader->setVec3("color", objectsToDraw[i]->getColor());
        objectsToDraw[i]->draw();
    }

    if(moveLight)
        light->updatePosition();
    light->draw(camera);

}

void Scene::createDemo(){
    Sphere *sphere = new Sphere("Sphere Demo");
    sphere->setColor(glm::vec3(0.90f, 0.31f, 0.3f));
    sphere->setPosition(glm::vec3(1.0f,2.0f,0.0f));
    Plane *plane = new Plane("Plane Demo");
    plane->setSize(glm::vec3(7.0f));
    plane->setColor(glm::vec3(0.5f, 0.7f, 0.5f));
    plane->setPosition(glm::vec3(1.0f,1.0f,0.0f));
    Cube *cube = new Cube("Cube Demo");
    cube->setColor(glm::vec3(0.63f, 0.31f, 0.71f));
    cube->setPosition(glm::vec3(1.0f,3.0f,2.0f));

    addObject(plane);
    addObject(cube);
    addObject(sphere);
}

void Scene::clearScene()
{
    objectsToDraw.clear();
}

void Scene::createAnimationDemo()
{
    Capsule *cap = new Capsule("Caps");

    Cube *cube1 = new Cube("Control 1");
    cube1->setPosition(glm::vec3(0,0,2.5f));

    cube1->setSize(glm::vec3(0.1f));
    cube1->setColor(glm::vec3(1.0,0,0));

    Cube *cube2 = new Cube("Control 2");
    cube2->setPosition(glm::vec3(0.f));
    cube2->setSize(glm::vec3(0.1f));
    cube2->setColor(glm::vec3(1.0,0,0));

    Bone *bone1 = new Bone(0, "arm", glm::mat4(1.0f));
    Bone *bone2 = new Bone(1, "hand", glm::mat4(1.0f));
    bone1->setPosition(glm::vec3(0.f));
    bone2->setPosition(glm::vec3(0.f));
    bone1->addChildren(bone2);
    bone1->calcInverseRestTransform(glm::mat4(1.0f));

    std::vector<Bone*> skeleton;
    skeleton.push_back(bone1);
    skeleton.push_back(bone2);

    an_model = new AnimatedModel(cap, skeleton);
    an_model->computeWeights(0.9f);

    addObject(cap);
    addObject(cube1);
    addObject(cube2);
}

void Scene::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
    case Qt::Key_Z:
        if (moveLight){
            light->increaseHeight();
        }else if (moveBone){
            an_model->getSkeleton()[1]->roll(5);
            an_model->updateModelVertice();
        }else{
            camera->ProcessKeyboard(FORWARD);
        }
        updateGL();
        break;
    case Qt::Key_S:
        if (moveLight){
             light->decreaseHeight();
        }else if (moveBone){
            an_model->getSkeleton()[1]->roll(-5);
            an_model->updateModelVertice();
        }else{
            camera->ProcessKeyboard(BACKWARD);
            }
        updateGL();
        break;
    case Qt::Key_Q:
        if (moveLight){
            light->increaseDistance();
        }else if (moveBone){
            an_model->getSkeleton()[1]->yaw(5);
            an_model->updateModelVertice();
        }else{
            camera->ProcessKeyboard(LEFT);
            }
        updateGL();
        break;
    case Qt::Key_D:
        if (moveLight){
            light->decreaseDistance();
        }else if (moveBone){
            an_model->getSkeleton()[1]->yaw(-5);
            an_model->updateModelVertice();
        }else{
            camera->ProcessKeyboard(RIGHT);
            }
        updateGL();
        break;
    case Qt::Key_T:
        if (moveBone){
            an_model->getSkeleton()[1]->pitch(+5);
            an_model->updateModelVertice();
        }
        updateGL();
        break;
    case Qt::Key_B:
        if (moveBone){
            an_model->getSkeleton()[1]->pitch(-5);
            an_model->updateModelVertice();
        }
        updateGL();
        break;
    }
}

void Scene::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    float xoffset = mouseEvent->x() - lastX;
    float yoffset = lastY - mouseEvent->y(); // reversed since y-coordinates go from bottom to top
    lastX = mouseEvent->x();
    lastY = mouseEvent->y();
    if (xoffset< 20 && xoffset > -20 && yoffset < 20 && yoffset>-20 )
        camera->ProcessMouseMovement(xoffset, yoffset);
    updateGL();
}

void Scene::wheelEvent(QWheelEvent *wheelEvent)
{
    int sign = wheelEvent->delta()/120;
    camera->ProcessMouseScroll(sign);
    updateGL();
}


