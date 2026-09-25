#pragma once
//#include "blehEngine.h"
#include "Services/blehServices.h"
#include "Services/Assets/AssetManager.h"
namespace bleh
{
    class blehGame
    {
        public:
            virtual void OnUpdate() = 0; //ska vara blehScript som alla scripts inheritar
            virtual void Initialize() = 0;
            void setBlehServices(blehServices&);
            //friend class blehEngine;

        protected:
            std::shared_ptr<AssetManager> _AssetManager;
            blehServices* _blehservices;
            blehGame();

        private:


    };
}