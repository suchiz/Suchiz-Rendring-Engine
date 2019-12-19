#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <map>
#include <QString>
#include "bonetransform.h"
#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"

class KeyFrame
{
public:
    //CONSTRUCTOR
    KeyFrame(float timeStamp, std::map<QString, BoneTransform*> poses);

    //GETTERS
    float getTimeStamp() const {return timeStamp;}
    std::map<QString, BoneTransform*> getPoses() {return poses;}

private:
    //ATTRIBUTES
    float timeStamp;
    std::map<QString, BoneTransform*> poses;
};

#endif // KEYFRAME_H
