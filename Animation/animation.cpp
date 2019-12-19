#include "animation.h"

Animation::Animation(AnimatedModel *entity, float totalTime, std::vector<KeyFrame> keyFrames)
{
    this->entity = entity;
    this->totalTime = totalTime;
    this->keyFrames = keyFrames;
}

void Animation::play()
{
    if (keyFrames.size() > 0){
        animationTimer = new QTime;
        animationTimer->start();
        stopPressed = false;

        QTimer *t = new QTimer(this);
        float frame_t = 1000/60;
        QObject::connect(t, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t->start(frame_t);
    }
}

void Animation::update()
{
    if (!stopPressed){
        std::pair<KeyFrame, KeyFrame> currentFrames = updateCurrentFrames();
        float progression = calculateProgression(currentFrames.first, currentFrames.second);
        interpolate(currentFrames.first, currentFrames.second, progression);
//        entity->updateModelVerticeLBS();
        if((animationTimer->elapsed()/1000) > totalTime)
            animationTimer->restart();
     }
}

void Animation::applyPoseToBone(glm::vec3 position, glm::vec3 rotation, Bone *bone)
{
    for (Bone *b : bone->getChildren())
        applyPoseToBone(position, rotation, b);

    glm::mat4 interpolatedModel = glm::mat4(1.0f);
    interpolatedModel = glm::translate(interpolatedModel, position);
    interpolatedModel = glm::rotate(interpolatedModel, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    interpolatedModel = glm::rotate(interpolatedModel, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    interpolatedModel = glm::rotate(interpolatedModel, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    bone->setAnimatedTransform(interpolatedModel);
}

std::pair<KeyFrame, KeyFrame> Animation::updateCurrentFrames()
{
    KeyFrame previousFrame = keyFrames[0];
    KeyFrame nextFrame = keyFrames[0];
    for (unsigned int i = 1; i < keyFrames.size(); ++i) {
        nextFrame = keyFrames[i];
        if (nextFrame.getTimeStamp()*1000 > animationTimer->elapsed())
            break;
        previousFrame = keyFrames[i];
    }
    return std::pair<KeyFrame, KeyFrame> {previousFrame, nextFrame};
}

float Animation::calculateProgression(KeyFrame previousFrame, KeyFrame nextFrame)
{
        float time = nextFrame.getTimeStamp() - previousFrame.getTimeStamp();
        float currentTime = animationTimer->elapsed() - previousFrame.getTimeStamp()*1000;
        return currentTime / (time * 1000);
}

void Animation::timeOutSlot()
{
    update();
}

void Animation::interpolate(KeyFrame previousFrame, KeyFrame nextFrame, float progression)
{
    std::vector<QString> bonesName;
    for (std::pair<QString, BoneTransform*> pose : previousFrame.getPoses())
        bonesName.push_back(pose.first);
    for (QString currentBone : bonesName){
        BoneTransform* previousTransform = previousFrame.getPoses()[currentBone];
        BoneTransform* nextTransform = nextFrame.getPoses()[currentBone];

        glm::vec3 rotation = glm::mix(previousTransform->getRotation(), nextTransform->getRotation(), progression);
        glm::vec3 position = glm::mix(previousTransform->getPosition(), nextTransform->getPosition(), progression);
        applyPoseToBone(position, rotation, entity->getBone(currentBone));
    }
}
