#pragma once
#include "renderer/Renderer.h"
#include "Services/InputService.h"
namespace bleh
{
    class blehServices
    {
        protected: 

            Renderer* _Renderer;
            InputService* _InputService;



        public:
    
            void Initialize(Renderer& renderer, InputService& inputservice);
            void SetRenderer(Renderer& renderer);
            void SetInputSystem(InputService& inputservice);
            InputService& GetInputSystem();
            Renderer& GetRenderer();
    
            //friend class blehEngine;



    };
}