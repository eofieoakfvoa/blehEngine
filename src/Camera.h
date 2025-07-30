#define GLM_ENABLE_EXPERIMENTAL
#pragma once
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
    glm::vec3 Position;
    glm::quat Rotation; //Quaternion
    glm::vec3 const WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    CameraMode CameraType = CameraMode::NoClip;
public:
    glm::vec3 CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    Camera(glm::vec3 StartPosition, glm::quat StartRotation);
    ~Camera();
    glm::vec3 GetPosition();
    void Move(glm::vec3 addedPosition);
    void SetPosition(glm::vec3 newPosition);
    glm::mat4 LookAt(glm::vec3 PositionToLookAt);
    void Rotate(glm::vec4 AddedQuaternion);
    void SetRotation(glm::quat NewQuaternion);
    static glm::quat EulerToQuaternion(glm::vec3 Euler);
    void Update();
};