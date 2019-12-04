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
#include "../Objects/sphere.h"
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
    void addObject(DrawableObject *object){objectsToDraw.push_back(object);}

    //UI FUNCTIONS
    void setMoveLight(bool checked){ moveLight = checked;}
    void setMoveSurfacePoint(bool checked) {moveSurfacePoint = checked;}

    //GETTERS
    Light& getLight() {return *light;}
    std::vector<DrawableObject*> getObjectsToDraw() {return objectsToDraw;}


private:
    //OPENGL ATTRIBUTES
    unsigned int objectsVAO;
    Shader *objectShader;
    Shader *lightShader;
    Camera *camera;
    Light *light;
    DepthMap *depthmap;

    //SCENE ATTRIBUTES
    std::vector<DrawableObject*> objectsToDraw;

    float lastX = size().width() / 2.0f;
    float lastY = size().height() / 2.0f;

    //UI ATTRIBUTES
    bool moveLight = false;
    bool moveSurfacePoint = false;

};
#endif // OPENGLWINDOW_H
