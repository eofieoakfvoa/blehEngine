#include "blehServices.h"

#include <print>
namespace bleh
{
    void blehServices::Initialize(Renderer& renderer, InputService& inputservice)
    {
        SetRenderer(renderer);
        SetInputSystem(inputservice);
    }



    //lowkey gjorde inte inline på dessa för att då skulle .cpp filen bara vara initialize 
    void blehServices::SetRenderer(Renderer& renderer)
    {
        _Renderer = &renderer;
    }

    void blehServices::SetInputSystem(InputService& inputservice)
    {
        _InputService = &inputservice;
    }


    InputService& blehServices::GetInputSystem()
    {

        return *_InputService;
    }

    Renderer& blehServices::GetRenderer()
    {
        return *_Renderer;
    }

}