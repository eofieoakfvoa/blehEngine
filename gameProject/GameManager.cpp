#include "GameManager.h"
#include "Camera.h"
#include "blehEngine.h"
#include <print>
#include <memory>
#include <filesystem>
#include "renderer\Texture.h"
#include "Random.h"
#include "Services/Assets/handle.h"

using namespace bleh;
int main()
{
    blehEngine bleh;
    bleh.SetGame(std::make_unique<GameManager>());
    bleh.Initialize();
    //overflowing with joy and sadness, unable to commit to one side.
    //afraid to live, afraid to die.
}

void GameManager::OnUpdate()
{
    blehMath::vector3 cameraposition = _PlayerCamera->GetPosition();
    //camera movement
    _blehservices->GetRenderer().assetmanager = _AssetManager;
    if (_blehservices->GetInputSystem().GetKeyDown(bleh::Key::W))
    {
        cameraposition = blehMath::vector3(cameraposition.x, cameraposition.y, cameraposition.z - _cameraSpeed); //fps dependent på hastigheten
        //_PlayerCamera->SetPosition(cameraposition);
        _PlayerCamera->Move(CameraDirection::CameraFront, _cameraSpeed);
    }
    if (_blehservices->GetInputSystem().GetKeyDown(bleh::Key::A))
    {
        cameraposition = blehMath::vector3(cameraposition.x - _cameraSpeed, cameraposition.y, cameraposition.z); 
        _PlayerCamera->Move(CameraDirection::CameraLeft, _cameraSpeed);
    }
    if (_blehservices->GetInputSystem().GetKeyDown(bleh::Key::S))
    {
        cameraposition = blehMath::vector3(cameraposition.x, cameraposition.y, cameraposition.z + _cameraSpeed); 
        _PlayerCamera->Move(CameraDirection::CameraBack, _cameraSpeed);
    }
    if (_blehservices->GetInputSystem().GetKeyDown(bleh::Key::D))
    {
        cameraposition = blehMath::vector3(cameraposition.x + _cameraSpeed, cameraposition.y, cameraposition.z); 
        _PlayerCamera->Move(CameraDirection::CameraRight, _cameraSpeed);
    }

    //Up and Down 
    if (_blehservices->GetInputSystem().GetKeyDown(bleh::Key::Space))
    {
        cameraposition = blehMath::vector3(cameraposition.x, cameraposition.y + _cameraSpeed, cameraposition.z);
        _PlayerCamera->Move(CameraDirection::CameraUp, _cameraSpeed);
    }
    if (_blehservices->GetInputSystem().GetKeyDown(bleh::Key::LEFT_SHIFT))
    {
        cameraposition = blehMath::vector3(cameraposition.x, cameraposition.y - _cameraSpeed, cameraposition.z);
        _PlayerCamera->Move(CameraDirection::CameraDown, _cameraSpeed);
    }

    //Change Movement speed
    if (_blehservices->GetInputSystem().GetKeyDown(bleh::Key::UP))
    {
        _cameraSpeed += 0.000001f;
    }
    if (_blehservices->GetInputSystem().GetKeyDown(bleh::Key::DOWN))
    {
        _cameraSpeed -= 0.000001f;
    }


    //camera rotation temp
    float cameraSensitivity = 0.3 * 0.1; 
    MousePosition DeltaPosition = _blehservices->GetInputSystem().GetDeltaMousePosition();
    if (DeltaPosition.MouseX || DeltaPosition.MouseY)
    {
        _PlayerCamera->Rotate(DeltaPosition.MouseX, DeltaPosition.MouseY, cameraSensitivity);
        
    }

    //debug
    if (_blehservices->GetInputSystem().GetInputClick(bleh::Key::L))
    {
        uint64_t randomnumber = bleh::Random::RandomInt64();
        std::println("random number: {}", randomnumber);
    }
    //_PlayerCamera->LookAt(_PlayerCamera->GetPosition() + _PlayerCamera->CameraFront); 


}


//like its to a point where its needles eye
void GameManager::Initialize()
{ 
    
   
    //fixa så AssetManager kan loadar textures + kan ta string overload eller något?
    _AssetManager->setBlehServices(*_blehservices);

    blehHandle Texture1 = _AssetManager->LoadImage(ResourcePath "Textures/cc12.jpg");
    blehHandle Texture2 = _AssetManager->LoadImage(ResourcePath "Textures/container.jpg");
    _AssetManager->SetTextureActive(Texture1.UUID, 0);
    _AssetManager->SetTextureActive(Texture2.UUID, 1);

	

    blehHandle meshhandle2 = _AssetManager->LoadMesh(ResourcePath "temp/newcube.gltf"); 
    _AssetManager->AddToRenderQueue(meshhandle2.UUID);

    _PlayerCamera = std::make_unique<Camera>(blehMath::vector3(0.0f,0.0f,0.0f), Camera::EulerToQuaternion(blehMath::vector3(0.0f,0.0f,0.0f)));
    _blehservices->GetRenderer().SetCurrentCamera(_PlayerCamera.get());
    
    
    
    //highkey att denna är inte en override, men istället automatiskt som enginen callar, då tar den filepath till GameResources läser in cpp filer med BlehCode för OnUpdate() och liknande? där den senare kan använda    
  
}

void GameManager::Update()
{

}
