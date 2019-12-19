#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <iostream>
#include <glad/glad.h>
#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"
#include <vector>

#include "../Scene/openglwindow.h"
#include "../Objects/cube.h"
#include "../Scene/camera.h"
#include "../Scene/shader.h"
#include "../Scene/light.h"
#include "../Objects/plane.h"
#include "../Objects/capsule.h"
#include "../Objects/sphere.h"
#include "../Animation/bone.h"
#include "../Animation/animatedmodel.h"
#include "../Animation/animation.h"
#include "../Objects/drawableobject.h"
#include "../Surfaces/tensorproduct.h"

class DepthMap;
class Scene : public OpenGLWindow
{
    Q_OBJECT

public:
    //OPENGL FUNCTIONS
    explicit Scene(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent( QKeyEvent *keyEvent );
    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void wheelEvent(QWheelEvent *wheelEvent);

    //SCENE FUNCTIONS
    void createDemo();
    void clearScene();
    void createAnimationDemo();
    void initializeAnimation();
    void addObject(DrawableObject *object){objectsToDraw.push_back(object);}
    void deleteObject(int index){objectsToDraw.erase(objectsToDraw.begin() + index);}
    void playAnimation(){animation->play();}
    void stopAnimation(){animation->stop();}
    void addKeyFrame(float time);

    //UI FUNCTIONS
    void setMoveLight(bool checked){ moveLight = checked;}
    void setRotateBone(bool checked) {rotateBone = checked;}
    void setTranslateBone(bool checked) {translateBone = checked;}
    void setSelectedBone(int ind){selectedBone = an_model->getSkeleton()[ind];}

    //GETTERS
    Light& getLight() const {return *light;}
    std::vector<DrawableObject*> getObjectsToDraw() const {return objectsToDraw;}
    Animation* getAnimation() const {return animation;}
    AnimatedModel* getAnimatedModel() const {return an_model;}

protected:
    //OPENGL ATTRIBUTES
    unsigned int objectsVAO;
    Shader *objectShader = NULL;
    Camera *camera = NULL;
    Light *light = NULL;
    DepthMap *depthmap = NULL;

    //SCENE ATTRIBUTES
    std::vector<DrawableObject*> objectsToDraw;
    AnimatedModel *an_model = NULL;
    Animation *animation = NULL;
    Bone *selectedBone;
    bool drawAnimation = false;

    float lastX = size().width() / 2.0f;
    float lastY = size().height() / 2.0f;

    //UI ATTRIBUTES
    bool moveLight = false;
    bool rotateBone = false;
    bool translateBone = false;

};
#endif // OPENGLWINDOW_H
