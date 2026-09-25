#define GLM_ENABLE_EXPERIMENTAL
#pragma once
#include "blehMath/blehMath.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <Unordered_map>
namespace bleh
{
    enum CameraMode
    {
        NoClip = 1, // fly like kamera
        LookAt, // kameran är fast en relativ distance från ett object
        Static // ska bara kunna röra sig en plane, t.ex XY som terraria, och ZX, som core keeper. används t.ex för maps ksk?
    };
    enum class CameraDirection
    {
        None = 0,
        CameraFront,
        CameraRight,
        CameraBack,
        CameraLeft,
        CameraDown,
        CameraUp,

    };

    class Camera
    {
    public:
        Camera(blehMath::vector3 StartPosition, blehMath::quaternion StartRotation);
        ~Camera();

        blehMath::vector3 const WorldUp = blehMath::vector3(0.0f, 1.0f, 0.0f);

        blehMath::mat4 GetCameraMatrix() const;
        inline blehMath::mat4 GetProjectionMatrix() const { return _ProjectionMatrix; }

        inline blehMath::vector3 GetPosition() const { return _CameraPosition; }
        inline float GetFieldOfView() const { return _FieldOfView; }
        inline float GetNearClippingPlane() const { return _NearClippingPlane; }
        inline float GetFarClippingPlane() const { return _FarClippingPlane; }

        void SetPosition(blehMath::vector3 newPosition);
        void SetRotation(blehMath::quaternion NewQuaternion);
        void SetActive();

        void Move(CameraDirection direction, float Offset);
        void LookAt(blehMath::vector3 PositionToLookAt);
        void AddRotate(float degree, glm::vec3 AddedVec3);
        void Rotate(float deltax, float deltay, float sensitivity);
        static blehMath::quaternion EulerToQuaternion(blehMath::vector3 Euler); //xd vet inte varför jag la den här borde bara vara blehmath som glm gör HAHAHAH 

    private:
        void UpdateCameraMatrix();
        float _FieldOfView = 45.0f;
        float _NearClippingPlane = 0.1f;
        float _FarClippingPlane = 10000.0f;
        float _Yaw = 0;
        float _Pitch = 0;
        float _Roll = 0;
        blehMath::vector3 _CameraRight = blehMath::vector3(1.0f, 0.0f, 0.0f);
        blehMath::vector3 _CameraUp = blehMath::vector3(0.0f, 1.0f, 0.0f);
        blehMath::vector3 _CameraBack = blehMath::vector3(0.0f, 0.0f, 1.0f);
        blehMath::vector3 _CameraFront = blehMath::vector3(0.0f, 0.0f, -1.0f);
        blehMath::vector3 _CameraDown = blehMath::vector3(0.0f, -1.0f, 0.0f);
        blehMath::vector3 _CameraLeft = blehMath::vector3(-1.0f, 0.0f, 0.0f);

        blehMath::mat4 _CameraMatrix;
        blehMath::mat4 _ProjectionMatrix;
        blehMath::vector3 _CameraPosition;
        blehMath::quaternion _CameraRotation;
        CameraMode CameraType = CameraMode::NoClip;
        blehMath::vector3* _CameraDirections[7]; //idk bro kanske borde vara unique pointer så det försvinner, eller switch case ifall det är snabbare man idk 
    };
}