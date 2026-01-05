#include "InputService.h"
#include <iostream>



#include <string>
#include <print>
InputService::InputService(GLFWwindow* window)
{
    
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, PollKeys);
    _InputDispatcher.SubscribeToEvent<KeyPressedEvent>([this](KeyPressedEvent& eevee){OnKeyPressed(eevee);});
    _InputDispatcher.SubscribeToEvent<KeyReleasedEvent>([this](KeyReleasedEvent& eevee){OnKeyReleased(eevee);}); 
}

void InputService::OnKeyPressed(KeyPressedEvent& eevee) 
{
    _KeyStateMap[eevee.GetKeyCode()] = KeyState::KeyDown;
}
void InputService::OnKeyReleased(KeyReleasedEvent &eevee)
{
    _KeyStateMap[eevee.GetKeyCode()] = KeyState::KeyUp;
}
bool InputService::GetKeyDown(Bleh::Key keyToLookUp)
{
    return (_KeyStateMap[keyToLookUp] == KeyState::KeyDown) ? true : false; //ifall den är none så false automatiskt oavsätt vad keyn är eftersom den inte blivit uppdaterad 
}
bool InputService::GetKeyUp(Bleh::Key keyToLookUp)
{
    return (_KeyStateMap[keyToLookUp] == KeyState::KeyUp) ? true : false; 
}


void InputService::PollKeys(GLFWwindow *window, int key, int scanCode, int action, int modifierBits)
{

    auto* inputSystem = static_cast<InputService*>(glfwGetWindowUserPointer(window));

    switch (action)
    {
        case GLFW_PRESS:
        {
            std::println("Button {} was Pressed", key);
            //keypress eeveent 
            KeyPressedEvent eevee((Bleh::Key)key);
            inputSystem->_InputDispatcher.Dispatch(eevee);
            break;
            
        }
        case GLFW_RELEASE:
        {
            KeyReleasedEvent eevee((Bleh::Key)key);
            inputSystem->_InputDispatcher.Dispatch(eevee);
            break;
        
        }

        case GLFW_REPEAT:
            break; // vad vill jag göra med detta, har det mest kvar för ifall det behövs för typing
    }
}



