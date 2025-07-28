#include <glm/glm.hpp>
#include "blehMath/blehMath.h"
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
    glm::vec4 Rotation; //Quaternion
    blehMath::vector3 WorldUp = blehMath::vector3(0.0f,1.0f,0.0f);
    CameraMode CameraType = CameraMode::NoClip;

public:
    Camera(glm::vec3 StartPosition, glm::vec4 StartRotation);
    ~Camera();
    void Move(glm::vec3 addedPosition);
    void SetPosition(glm::vec3 newPosition);
    void LookAt(glm::vec3 PositionToLookAt);
    void Rotate(glm::vec4 AddedQuaternion);
    void SetRotation(glm::vec4 NewQuaternion);
    void EulerToQuaternion(glm::vec3 Euler);
    void Update();
};