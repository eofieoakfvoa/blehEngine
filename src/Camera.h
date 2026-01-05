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
    public:
        Camera(blehMath::vector3 StartPosition, blehMath::quaternion StartRotation);
        ~Camera();

        blehMath::vector3 CameraFront = blehMath::vector3(0.0f, 0.0f, -1.0f);
        blehMath::vector3 const WorldUp = blehMath::vector3(0.0f, 1.0f, 0.0f);
        //fixa copies
        inline blehMath::mat4 GetCameraMatrix() const { return _CameraMatrix; } 
        inline blehMath::mat4 GetProjectionMatrix() const {return _ProjectionMatrix; }

        inline blehMath::vector3 GetPosition() const { return _CameraPosition; }
        inline float GetFieldOfView() const { return _FieldOfView; }
        inline float GetNearClippingPlane() const { return _NearClippingPlane; }
        inline float GetFarClippingPlane() const { return _FarClippingPlane; }

        void SetPosition(blehMath::vector3 newPosition);
        void SetRotation(blehMath::quaternion NewQuaternion);
        

        void Move(blehMath::vector3 addedPosition);
        void LookAt(blehMath::vector3 PositionToLookAt);
        void Rotate(glm::vec4 AddedQuaternion); //vet faktiskt inte ifall jag borde ha en vec4 här, skulle kanske kunna ha function overloading med vec4, quat, vec3(euler)
        static blehMath::quaternion EulerToQuaternion(blehMath::vector3 Euler);
    
        private:
        float _FieldOfView;
        float _NearClippingPlane;
        float _FarClippingPlane;

        blehMath::mat4 _CameraMatrix;
        blehMath::mat4 _ProjectionMatrix; //fixa så det här inte är hard coded, och resizar med skärmen
        blehMath::vector3 _CameraPosition;
        blehMath::quaternion _CameraRotation; //Quaternion
        CameraMode CameraType = CameraMode::NoClip;
};