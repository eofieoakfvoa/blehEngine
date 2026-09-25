#include "Services/blehGame.h"
#include "Services/blehServices.h"
#include "Camera.h"
#include <memory>

class GameManager : public bleh::blehGame
{
    private:
        void OnUpdate() override;
        void Initialize() override;
        std::unique_ptr<bleh::Camera> _PlayerCamera;
        float _cameraSpeed = 0.0005f;


    public:
        void Update();
            


};