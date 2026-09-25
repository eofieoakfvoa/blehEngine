#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <memory>
#include "renderer\Renderer.h"
#include "services/InputService.h"
#include "services/blehGame.h"
#include "services/blehServices.h"
#include "services/WindowManager.h"
//never knew a thing but i knew when i was ready to learn
//had to walk the golden curve and to be where we deserve 
//to be far away from hurt,
//place the 9 above the world

namespace bleh
{
    class blehEngine
    {
        public:
            void Initialize();

            inline void SetGame(std::unique_ptr<blehGame> game) {  _BlehGame = std::move(game); }
            inline Renderer& GetRenderer() { return *_Renderer; }
        
        private:


            GLFWwindow* _Window;

            //[[-- idk asså Jag vet inte ifall dfet borde vara shared pointers, då att Services har en shared eller weak ptr och gameproject har en weak ptr, istället för de har raw pointers, men här är det clear att det är enginen--]]
            std::unique_ptr<blehGame> _BlehGame;
            std::unique_ptr<Renderer> _Renderer;
            std::unique_ptr<InputService> _inputService;
            std::unique_ptr<WindowManager> _WindowManager;
            std::unique_ptr<blehServices> _BlehServices;

            void _GameLoop();


    };
}