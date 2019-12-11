#ifndef CHECKUI_H
#define CHECKUI_H

#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"
#include <QString>
#include <regex>

class CheckUI
{
public:

protected:
    glm::vec3 checkColor(QString p1, QString p2, QString p3);
    glm::vec3 checkSize(QString p1, QString p2, QString p3);
    glm::vec3 checkRotation(QString p1, QString p2, QString p3);
    glm::vec3 checkPostion(QString p1, QString p2, QString p3);
    int checkOrder(QString p1);
    int checkWidth(QString p1);
    int checkHeight(QString p1);

    float clampBot(float x, float thresh, float clampVal);
    float clampTop(float x, float thresh, float clampVal);
    float checkFloat(QString ref);
    int checkInt(QString ref);
};

#endif // CHECKUI_H
