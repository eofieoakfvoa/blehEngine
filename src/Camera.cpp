#include "Camera.h"

Camera::Camera(glm::vec3 StartPosition, glm::vec4 StartRotation)
    : Position(StartPosition), Rotation(StartRotation)
{
}

void Camera::EulerToQuaternion(glm::vec3 Euler)
{
    float roll = Euler.x;
    float pitch = Euler.y;
    float yaw= Euler.z;
    
}
