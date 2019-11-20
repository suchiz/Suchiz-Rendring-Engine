#ifndef LIGHT_H
#define LIGHT_H

#include "../Objects/cube.h"
#include "../Scene/shader.h"
#include "../Scene/camera.h"

class Light : public Cube
{
public:
    Light();
    void updatePosition();
    void draw(Camera *camera);

    void increaseDistance() {distance += 0.1f;}
    void decreaseDistance() {distance -= 0.1;}
    void increaseHeight() {height += 0.1f;}
    void decreaseHeight() {height -= 0.1;}
    float getHeight() const {return height;}
    float getDistance() const {return distance;}
    float getAngle() const {return angle;}

private:
    unsigned int VAO;
    Shader *lightShader;
    float height = 5.0f;
    float distance = 3.0f;
    float angle = 0;

};

#endif // LIGHT_H
