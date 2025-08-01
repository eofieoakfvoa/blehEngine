#include "Camera.h"

Camera::Camera(glm::vec3 StartPosition, glm::quat StartRotation)
    : Position(StartPosition), Rotation(StartRotation)
{
}
Camera::~Camera()
{
}
const glm::vec3& Camera::GetPosition()
{
    return Position;
}
void Camera::SetPosition(glm::vec3 newPosition)
{
    Position = newPosition;
}
glm::mat4 Camera::LookAt(glm::vec3 PositionToLookAt)
{
    return glm::lookAt(Position, PositionToLookAt, WorldUp);
}
void Camera::SetRotation(glm::quat NewQuaternion)
{
    Rotation = NewQuaternion;
}
glm::quat Camera::EulerToQuaternion(glm::vec3 Euler)
{
    return glm::quat(glm::vec3(Euler));
}
