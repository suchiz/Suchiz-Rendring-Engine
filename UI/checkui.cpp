#include "checkui.h"

glm::vec3 CheckUI::checkColor(QString p1, QString p2, QString p3)
{
    float r = checkInt(p1);
    float g = checkInt(p2);
    float b = checkInt(p3);

    r = clampBot(r, 0, 0);
    g = clampBot(g, 0, 0);
    b = clampBot(b, 0, 0);
    r = clampTop(r, 255, 255);
    g = clampTop(g, 255, 255);
    b = clampTop(b, 255, 255);
    if (r == 0 && g == 0 && b == 0)
        return glm::vec3(1.0f);
    return glm::vec3(r/255.0f,g/255.0f,b/255.0f);
}

glm::vec3 CheckUI::checkSize(QString p1, QString p2, QString p3)
{
    float x = checkFloat(p1);
    float y = checkFloat(p2);
    float z = checkFloat(p3);

    return glm::vec3(clampBot(x, 0, 1),
                     clampBot(y, 0, 1),
                     clampBot(z, 0, 1));
}

glm::vec3 CheckUI::checkRotation(QString p1, QString p2, QString p3)
{
    float r = checkFloat(p1);
    float p = checkFloat(p2);
    float y = checkFloat(p3);
    return glm::vec3(r,p,y);
}

glm::vec3 CheckUI::checkPostion(QString p1, QString p2, QString p3)
{
    float x = checkFloat(p1);
    float y = checkFloat(p2);
    float z = checkFloat(p3);
    return glm::vec3(x,y,z);
}

float CheckUI::clampBot(float x, float thresh, float clampVal)
{
    if (x <= thresh)
        return clampVal;
    return x;
}

float CheckUI::clampTop(float x, float thresh, float clampVal)
{
    if (x >= thresh)
        return clampVal;
    return x;
}

float CheckUI::checkFloat(QString ref)
{
    if (std::regex_match(ref.toStdString(), std::regex{"^[-+]?[0-9]*.?[0-9]+$"}))
        return ref.toFloat();
    return 0;
}
int CheckUI::checkInt(QString ref)
{
    if (std::regex_match(ref.toStdString(), std::regex{"^[0-9]+$"}))
        return ref.toInt();
    return 0;
}
