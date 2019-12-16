#ifndef KEYFRAME_H
#define KEYFRAME_H

#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"
#include <QString>
#include <vector>

class KeyFrame
{
public:
    //CONSTRUCTOR
    KeyFrame(int ID, float timeStamp);

    //FUNCTIONS
    void addPose(glm::mat4 pose){poses.push_back(pose);}

    //GETTERS
    int getID() const {return ID;}
    float getTimeStamp() const {return timeStamp;}
    std::vector<glm::mat4> getPoses() const {return poses;}

private:
    //ATTRIBUTES
    float timeStamp = 0.f;
    int ID;
    std::vector<glm::mat4> poses;
};

#endif // KEYFRAME_H
