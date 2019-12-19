#include "keyframe.h"

KeyFrame::KeyFrame(float timeStamp, std::map<QString, BoneTransform*> poses)
{
    this->timeStamp = timeStamp;
    this->poses = poses;
}
