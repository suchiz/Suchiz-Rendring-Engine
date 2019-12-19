#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <QTime>
#include <QTimer>
#include "keyframe.h"
#include "animatedmodel.h"
#include "../External/glm/glm.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"

class Animation: public QObject
{
    Q_OBJECT
public:
    //CONSTRUCTOR
    Animation(AnimatedModel *entity, float totalTime, std::vector<KeyFrame> keyFrames);

    //FUNCTION
    void play();
    void stop() {stopPressed = true;}
    void update();
    std::pair<KeyFrame, KeyFrame> updateCurrentFrames();
    void interpolate(KeyFrame previousFrame, KeyFrame nextFrame, float progression);
    float calculateProgression(KeyFrame previousFrame, KeyFrame nextFrame);
    void addKeyFrame(KeyFrame kf){keyFrames.push_back(kf); totalTime = kf.getTimeStamp();}
    void applyPoseToBone(glm::vec3 position, glm::vec3 rotation, Bone *bone);
    void deleteKeyFrame(int ind) {keyFrames.erase(keyFrames.begin()+ind);}
    void clearKeyFrames() {keyFrames.clear();}
    float getLasTime() {if (keyFrames.size()>0) return keyFrames[keyFrames.size()-1].getTimeStamp(); return 0;}

    //GETTERS
    float getTotalTime() const {return totalTime;}
    std::vector<KeyFrame> getKeyFrames() const {return keyFrames;}

public slots:
    void timeOutSlot();

private:
    //ATTRIBUTES
    QTime *animationTimer;
    AnimatedModel *entity;
    float totalTime;
    bool stopPressed = false;
    std::vector<KeyFrame> keyFrames;
};

#endif // ANIMATION_H
