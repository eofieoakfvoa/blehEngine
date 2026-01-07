#include "Camera.h"

Camera::Camera(glm::vec3 StartPosition, glm::quat StartRotation)
    : _CameraPosition(StartPosition), _CameraRotation(StartRotation), _ProjectionMatrix(glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f)), _CameraMatrix(1.0)
{
}
Camera::~Camera()
{
}

void Camera::SetPosition(glm::vec3 newPosition)
{
    _CameraPosition = newPosition;
}
void Camera::LookAt(glm::vec3 PositionToLookAt)
{
    _CameraMatrix = glm::lookAt(_CameraPosition, PositionToLookAt, WorldUp);
}
void Camera::SetRotation(glm::quat NewQuaternion)
{
    _CameraRotation = NewQuaternion;
}
glm::quat Camera::EulerToQuaternion(glm::vec3 Euler)
{
    return glm::quat(glm::vec3(Euler));
}
