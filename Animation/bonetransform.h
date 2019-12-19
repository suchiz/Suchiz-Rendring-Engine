#ifndef BONETRANSFORM_H
#define BONETRANSFORM_H

#include "../External/glm/glm.hpp"
#include "../External/glm/gtx/quaternion.hpp"
#include "../External/glm/gtc/matrix_transform.hpp"
#include "../External/glm/gtc/type_ptr.hpp"
#include <QString>

class BoneTransform
{
public:
    //CONSTRUCTOR
    BoneTransform(glm::vec3 position, glm::vec3 rotation);

    //GETTERS
    glm::vec3 getPosition()const {return position;}
    glm::vec3 getRotation() const {return rotation;}

private:
    //ATTRIBUTES
    glm::vec3 position;
    glm::vec3 rotation;
};

#endif // BONETRANSFORM_H
