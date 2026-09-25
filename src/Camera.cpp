#include "Camera.h"
#include "renderer/Renderer.h"
#include "blehEngine.h"
#include <print>
namespace bleh
{
    Camera::Camera(glm::vec3 StartPosition, glm::quat StartRotation)
        : _CameraPosition(StartPosition), _CameraRotation(StartRotation), _ProjectionMatrix(glm::perspective(glm::radians(_FieldOfView), (float)800 / (float)600, _NearClippingPlane, _FarClippingPlane)), _CameraMatrix(1.0)
    {
        _CameraDirections[(int)CameraDirection::CameraFront] = &_CameraFront;
        _CameraDirections[(int)CameraDirection::CameraRight] = &_CameraRight;
        _CameraDirections[(int)CameraDirection::CameraBack] = &_CameraBack;
        _CameraDirections[(int)CameraDirection::CameraLeft] = &_CameraLeft;
        _CameraDirections[(int)CameraDirection::CameraDown] = &_CameraDown;
        _CameraDirections[(int)CameraDirection::CameraUp] = &_CameraUp;
    }
    Camera::~Camera()
    {
    }

    blehMath::mat4 Camera::GetCameraMatrix() const
    {

        glm::mat4 rotation = glm::mat4_cast(_CameraRotation);
        glm::mat4 invRotation = glm::transpose(rotation);
        return (invRotation * glm::translate(glm::mat4(1.0f), -_CameraPosition));
        //return _CameraMatrix;
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

    void Camera::SetActive()
    {
        //GetRenderer()->SetCurrentCamera(&camera);
    }

    void Camera::Move(CameraDirection direction, float Offset)
    {
        blehMath::vector3 movementdirection = *_CameraDirections[(int)direction];
        //std::println("movementdirection: directionx = {}, directiony = {}, directionz = {}", movementdirection.x, movementdirection.y, movementdirection.z);
        //std::println("CAMERA UP:         directionx = {}, directiony = {}, directionz = {}", _CameraUp.x, _CameraUp.y, _CameraUp.z);
        _CameraPosition += movementdirection * Offset;
    }

    void Camera::AddRotate(float degree, glm::vec3 AddedVec3)
    {
        glm::quat addedRotation = glm::angleAxis(glm::radians(degree), glm::normalize(AddedVec3));
        _CameraRotation = addedRotation * _CameraRotation;
    }

    void Camera::Rotate(float deltax, float deltay,float sensitivity)
    {
        _Yaw += deltax * sensitivity;
        _Pitch += deltay * sensitivity;
        _Pitch = glm::clamp(_Pitch, -89.0f, 89.0f);

        glm::quat yaw = glm::angleAxis(glm::radians(_Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::quat pitch = glm::angleAxis(glm::radians(_Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
        _CameraRotation = yaw * pitch;
        _CameraFront = _CameraRotation * glm::vec3(0, 0, -1);
        _CameraRight = _CameraRotation * glm::vec3(1, 0, 0);
        _CameraUp = _CameraRotation * glm::vec3(0, 1, 0);
        _CameraDown = -_CameraUp;
        _CameraLeft = -_CameraRight;
        _CameraBack = -_CameraFront;
        //std::println("CAMERA UP; directionx = {}, directiony = {}, directionz = {},", _CameraUp.x, _CameraUp.y, _CameraUp.z);
        //std::println("CAMERA RIGHT; directionx = {}, directiony = {}, directionz = {},", _CameraRight.x, _CameraRight.y, _CameraRight.z);
        //std::println("CAMERA FRONT; directionx = {}, directiony = {}, directionz = {},", _CameraFront.x, _CameraFront.y, _CameraFront.z);

    }

}
