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
        initializeAnimation();

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
        objectShader->setBool("drawAnimation", drawAnimation);
        if (drawAnimation){
            std::vector<glm::mat4> D;
            for(Bone *b : an_model->getSkeleton())
                D.push_back(b->getAnimatedTransform());
            objectShader->setMat4Array("D", D, an_model->getNbBones());
            objectShader->setMat4Array("U_inv", an_model->getU_inv(), an_model->getNbBones());
            Capsule *caps = (Capsule*) objectsToDraw[i];
            caps->drawAnim();
        } else {
            objectsToDraw[i]->draw();
        }

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
    drawAnimation = false;
}

void Scene::createAnimationDemo()
{
    drawAnimation = true;
    addObject(an_model->getModel());
}

void Scene::initializeAnimation()
{
    Capsule *cap = new Capsule("Cylinder");

    Bone *bone1 = new Bone(0, "Arm", glm::mat4(1.0f));
    Bone *bone2 = new Bone(1, "Hand", glm::mat4(1.0f));
    //Bone *bone3 = new Bone(2, "Fingers", glm::mat4(1.0f));
    bone1->setPosition(glm::vec3(0.f));
    bone2->setPosition(glm::vec3(0.f));
    bone1->addChildren(bone2);
    //bone2->addChildren(bone3);
    //bone3->setPosition(glm::vec3(-1.f));

    std::vector<Bone*> skeleton;
    skeleton.push_back(bone1);
    skeleton.push_back(bone2);
    //skeleton.push_back(bone3);

    an_model = new AnimatedModel(cap, bone1, skeleton);
    an_model->computeWeights(0.9f);
    cap->buildInterleavedWeights(an_model->getWeightsForGPU());
    std::vector<KeyFrame> kf;
    animation = new Animation(an_model,0, kf);
}

void Scene::addKeyFrame(float time)
{
    if (time == -1){
        std::map<QString, BoneTransform*> datas;
        for (Bone* b: an_model->getSkeleton()){
            BoneTransform *bt = new BoneTransform(glm::vec3(0.f), glm::vec3(0.f));
            datas.insert(std::pair<QString, BoneTransform*> {b->getName(), bt});
        }
        KeyFrame kf(0, datas);
        animation->addKeyFrame(kf);
    }
    std::map<QString, BoneTransform*> datas;
    for (Bone* b: an_model->getSkeleton()){
        BoneTransform *bt = new BoneTransform(b->getPosition(), b->getRotation());
        datas.insert(std::pair<QString, BoneTransform*> {b->getName(), bt});
    }
    KeyFrame kf(time, datas);
    animation->addKeyFrame(kf);
}

void Scene::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
    case Qt::Key_Z:
        if (moveLight){
            light->increaseHeight();
        }else if (rotateBone){
            selectedBone->roll(5);;
//            an_model->updateModelVerticeLBS();
        }else if (translateBone){
            selectedBone->translate_x(0.1);
//            an_model->updateModelVerticeLBS();
        }else{
            camera->ProcessKeyboard(FORWARD);
        }
        updateGL();
        break;
    case Qt::Key_S:
        if (moveLight){
             light->decreaseHeight();
        }else if (rotateBone){
            selectedBone->roll(-5);;
//            an_model->updateModelVerticeLBS();
        }else if (translateBone){
            selectedBone->translate_x(-0.1);
//            an_model->updateModelVerticeLBS();
        }else{
            camera->ProcessKeyboard(BACKWARD);
            }
        updateGL();
        break;
    case Qt::Key_Q:
        if (moveLight){
            light->increaseDistance();
        }else if (rotateBone){
            selectedBone->yaw(5);
//            an_model->updateModelVerticeLBS();
        }else if (translateBone){
            selectedBone->translate_z(0.1);
//            an_model->updateModelVerticeLBS();
        }else{
            camera->ProcessKeyboard(LEFT);
            }
        updateGL();
        break;
    case Qt::Key_D:
        if (moveLight){
            light->decreaseDistance();
        }else if (rotateBone){
            selectedBone->yaw(-5);;
//            an_model->updateModelVerticeLBS();
        }else if (translateBone){
            selectedBone->translate_z(-0.1);
//            an_model->updateModelVerticeLBS();
        }else{
            camera->ProcessKeyboard(RIGHT);
            }
        updateGL();
        break;
    case Qt::Key_T:
        if (rotateBone){
            selectedBone->pitch(5);
//            an_model->updateModelVerticeLBS();
        }else if (translateBone){
            selectedBone->translate_y(0.1);
//            an_model->updateModelVerticeLBS();
        }
        updateGL();
        break;
    case Qt::Key_B:
        if (rotateBone){
            selectedBone->pitch(-5);;
//            an_model->updateModelVerticeLBS();
        } else if (translateBone){
            selectedBone->translate_y(-0.1);
//            an_model->updateModelVerticeLBS();
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


