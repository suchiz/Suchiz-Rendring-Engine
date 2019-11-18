#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "openglwindow.h"
#include "cube.h"
#include "camera.h"
#include "shader.h"
#include "light.h"
#include "plane.h"
#include "sphere.h"
#include "drawableobject.h"
#include "tensorproduct.h"

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
    void createDemo();
    void clearScene();

    void addCube(Cube cube){cubeToDraw.push_back(cube);}
    void addPlane(Plane plane){planeToDraw.push_back(plane);}
    void addSphere(Sphere sphere){sphereToDraw.push_back(sphere);}
    void addSurface(TensorProduct tp){surfaceToDraw.push_back(tp);}
    void delSurface(int i){surfaceToDraw.erase(surfaceToDraw.begin()+i);}

    //UI FUNCTIONS
    void setMoveLight(bool checked){ moveLight = checked;}
    void setMoveSurfacePoint(bool checked) {moveSurfacePoint = checked;}

    //GETTERS
    Light& getLight() {return *light;}
    std::vector<Cube> getCubeToDraw() {return cubeToDraw;}
    std::vector<Sphere> getSphereToDraw() {return sphereToDraw;}
    std::vector<Plane> getPlaneToDraw() {return planeToDraw;}
    std::vector<TensorProduct> getSurfaceToDraw() {return surfaceToDraw;}

private:
    //OPENGL ATTRIBUTES
    unsigned int objectsVAO;
    unsigned lightsVAO;
    Shader *objectShader;
    Shader *lightShader;
    Camera *camera;
    Light *light;
    DepthMap *depthmap;
    std::vector<Cube> cubeToDraw;
    std::vector<Plane> planeToDraw;
    std::vector<Sphere> sphereToDraw;
    std::vector<TensorProduct> surfaceToDraw;

    float lastX = size().width() / 2.0f;
    float lastY = size().height() / 2.0f;

    //UI ATTRIBUTES
    bool moveLight = false;
    bool moveSurfacePoint = false;

};
#endif // OPENGLWINDOW_H
