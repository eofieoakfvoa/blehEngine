#define GLM_ENABLE_EXPERIMENTAL
#pragma once
#include "blehMath/blehMath.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
enum CameraMode
{
    NoClip = 1, // fly like kamera
    LookAt, // kameran är fast en relativ distance från ett object
    Static // ska bara kunna röra sig en plane, t.ex XY som terraria, och ZX, som core keeper. används t.ex för maps ksk?
};
class Camera
{
private:
    unsigned int FieldOfView;
    blehMath::vector3 Position;
    blehMath::quaternion Rotation; //Quaternion
    blehMath::vector3 const WorldUp = blehMath::vector3(0.0f, 1.0f, 0.0f);
    CameraMode CameraType = CameraMode::NoClip;
public:
    blehMath::vector3 CameraFront = blehMath::vector3(0.0f, 0.0f, -1.0f);
    Camera(blehMath::vector3 StartPosition, blehMath::quaternion StartRotation);
    ~Camera();
    const blehMath::vector3& GetPosition();
    void Move(blehMath::vector3 addedPosition);
    void SetPosition(blehMath::vector3 newPosition);
    glm::mat4 LookAt(blehMath::vector3 PositionToLookAt);
    void Rotate(glm::vec4 AddedQuaternion); //vet faktiskt inte ifall jag borde ha en vec4 här, skulle kanske kunna ha function overloading med vec4, quat, vec3(euler)
    void SetRotation(blehMath::quaternion NewQuaternion);
    static blehMath::quaternion EulerToQuaternion(blehMath::vector3 Euler);
    void Update();
};