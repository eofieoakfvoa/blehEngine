#include "InputService.h"
#include <iostream>



#include <string>
InputService::InputService(GLFWwindow* window)
{
    
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, PollKeys);
    _InputDispatcher.SubscribeToEvent<KeyPressedEvent>([this](KeyPressedEvent& e){OnKeyPressed(e);});
    _InputDispatcher.SubscribeToEvent<KeyReleasedEvent>([this](KeyReleasedEvent& e){OnKeyReleased(e);}); //läs om lambdas
}

void InputService::OnKeyPressed(KeyPressedEvent& e) 
{
    _KeyStateMap[e.GetKeyCode()] = KeyState::KeyDown;
}
void InputService::OnKeyReleased(KeyReleasedEvent &e)
{
    _KeyStateMap[e.GetKeyCode()] = KeyState::KeyUp;
}


void InputService::PollKeys(GLFWwindow *window, int key, int scanCode, int action, int modifierBits)
{

    auto* inputSystem = static_cast<InputService*>(glfwGetWindowUserPointer(window));

    switch (action)
    {
        case GLFW_PRESS:
        {
            std::cout << "Key " << key << " pressed!\n";
            //keypress eeveent 
            KeyPressedEvent eevee((Bleh::Key)key);
            inputSystem->_InputDispatcher.Dispatch(eevee);
            break;
            
        }
        case GLFW_RELEASE:
        {
            std::cout << "Key " << key << " released!\n";
            KeyReleasedEvent eevee((Bleh::Key)key);
            inputSystem->_InputDispatcher.Dispatch(eevee);
            break;
        
        }

        case GLFW_REPEAT:
            std::cout << "Key " << key << " held!\n";
            break;
    }
}


bool InputService::GetKeyDown(Bleh::Key keyToLookUp)
{
    return (_KeyStateMap[keyToLookUp] == KeyState::KeyDown) ? true : false; //ifall den är none så false automatiskt oavsätt vad keyn är eftersom den inte blivit uppdaterad 
}

