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
    objectShader->setMat4("projection", camera->getProjectionMatrix()); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    objectShader->setMat4("view", camera->GetViewMatrix());
    objectShader->setMat4("lightSpaceMatrix", depthmap->getLightSpaceMatrix());
    depthmap->bindTexture();

    for(unsigned int i(0); i < cubeToDraw.size(); ++i){
        objectShader->setMat4("model", cubeToDraw[i].getModel());
        objectShader->setVec3("color", cubeToDraw[i].getColor());
        cubeToDraw[i].draw();
    }
    for(unsigned int i(0); i < planeToDraw.size(); ++i){
        objectShader->setMat4("model", planeToDraw[i].getModel());
        objectShader->setVec3("color", planeToDraw[i].getColor());
        planeToDraw[i].draw();
    }
    for(unsigned int i(0); i < sphereToDraw.size(); ++i){
        objectShader->setMat4("model", sphereToDraw[i].getModel());
        objectShader->setVec3("color", sphereToDraw[i].getColor());
        sphereToDraw[i].draw();
    }
    for(unsigned int i(0); i < surfaceToDraw.size(); ++i){
        objectShader->setMat4("model", surfaceToDraw[i].getModel());
        objectShader->setVec3("color", surfaceToDraw[i].getColor());
        surfaceToDraw[i].draw();
    }

    if(moveLight)
        light->updatePosition();
    light->draw(camera);

}

void Scene::createDemo(){
    Sphere sphere(1.0);
    sphere.setColor(glm::vec3(0.90f, 0.31f, 0.3f));
    sphere.setPosition(glm::vec3(1.0f,2.0f,0.0f));
    Plane plane(5.0);
    plane.setColor(glm::vec3(0.5f, 0.7f, 0.5f));
    plane.setPosition(glm::vec3(1.0f,1.0f,0.0f));
    Cube cube(1.0);
    cube.setColor(glm::vec3(0.63f, 0.31f, 0.71f));
    cube.setPosition(glm::vec3(1.0f,3.0f,2.0f));
    std::vector<glm::vec3> pts{
        glm::vec3(-0.35,0,0.3), glm::vec3(-0.15,0.1,0.35), glm::vec3(0,-0.2,0.25),
        glm::vec3(0.3,0.05,0.3), glm::vec3(0.45,0,0.25),
        glm::vec3(-0.4,-0.05,0.1), glm::vec3(-0.3,0,0.1), glm::vec3(-0.1,-0.15,0.15),
        glm::vec3(0.2,-0.05,0.05), glm::vec3(0.4,-0.1,0.1),
        glm::vec3(-0.5,0,0), glm::vec3(-0.25,0,0), glm::vec3(0,0,0),
        glm::vec3(0.25,0,0), glm::vec3(0.5,0,0)
    };
    TensorProduct tp = TensorProduct("Demo", std::pair<int,int>{3,5}, pts);
    tp.setColor(glm::vec3(0.35f, 0.46f, 0.72f));
    tp.setPosition(glm::vec3(3.0f,2.0f,2.0f));

    cubeToDraw.push_back(cube);
    planeToDraw.push_back(plane);
    sphereToDraw.push_back(sphere);
    surfaceToDraw.push_back(tp);
}

void Scene::clearScene()
{
    cubeToDraw.clear();
    sphereToDraw.clear();
    planeToDraw.clear();
    surfaceToDraw.clear();
}

void Scene::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
    case Qt::Key_Z:
        if (moveLight)
            light->increaseHeight();
        else
            camera->ProcessKeyboard(FORWARD);
        updateGL();
        break;
    case Qt::Key_S:
        if (moveLight)
            light->decreaseHeight();
        else
            camera->ProcessKeyboard(BACKWARD);
        updateGL();
        break;
    case Qt::Key_Q:
        if (moveLight)
            light->increaseDistance();
        else
        camera->ProcessKeyboard(LEFT);
        updateGL();
        break;
    case Qt::Key_D:
        if (moveLight)
            light->decreaseDistance();
        else
        camera->ProcessKeyboard(RIGHT);
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


