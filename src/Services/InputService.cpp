#include "InputService.h"
#include <iostream>



#include <string>
#include <print>
namespace bleh
{
    InputService::InputService(GLFWwindow* window)
    {
        glfwSetWindowUserPointer(window, this);
        glfwSetKeyCallback(window, _PollKeys);
        glfwSetCursorPosCallback(window, _PollMouse);
        glfwSetMouseButtonCallback(window, _PollMouseEvent); //Inget stoppar mig från att sätta detta som _PollKeys tror jag för jag treatar de the same just nu lol
        //glfwSetWindowSizeCallback(window, window_size_callback);
        _InputDispatcher.SubscribeToEvent<KeyPressedEvent>([this](KeyPressedEvent& eevee){OnKeyPressed(eevee);});
        _InputDispatcher.SubscribeToEvent<KeyReleasedEvent>([this](KeyReleasedEvent& eevee) {OnKeyReleased(eevee);});

        _InputDispatcher.SubscribeToEvent<KeyReleasedEvent>([this](KeyReleasedEvent& eevee) {OnKeyReleased(eevee);});
        _InputDispatcher.SubscribeToEvent<KeyReleasedEvent>([this](KeyReleasedEvent& eevee) {OnKeyReleased(eevee);});

        _InputDispatcher.SubscribeToEvent<MouseMoveEvent>([this](MouseMoveEvent&eevee){_UpdateMousePosition(eevee);});



    }
    bool InputService::GetKeyDown(bleh::Key keyToLookUp)
    {
        return (_KeyStateMap[keyToLookUp] == KeyState::KeyDown) ? true : false; 
    }
    bool InputService::GetKeyUp(bleh::Key keyToLookUp)
    {
        return (_KeyStateMap[keyToLookUp] == KeyState::KeyUp) ? true : false; 
    }
    bool InputService::GetInputClick(bleh::Key keyToLookUp)
    {
        if (_KeyPressedStateMap[keyToLookUp] == KeyState::KeyDown)
        {
            _KeyPressedStateMap[keyToLookUp] = KeyState::KeyUp;
            return true;
        }

        return false;
    }

    void InputService::OnKeyPressed(KeyPressedEvent& eevee) 
    {
        _KeyStateMap[eevee.GetKeyCode()] = KeyState::KeyDown;
        _KeyPressedStateMap[eevee.GetKeyCode()] = KeyState::KeyDown;
    }

    void InputService::OnKeyReleased(KeyReleasedEvent& eevee)
    {
        _KeyStateMap[eevee.GetKeyCode()] = KeyState::KeyUp;
    }
    void InputService::_UpdateMousePosition(MouseMoveEvent& eevee)
    {

        _DeltaMousePosX = _MousePosX - eevee.MouseX;
        _DeltaMousePosY = _MousePosY - eevee.MouseY;
        _MousePosX = eevee.MouseX;
        _MousePosY = eevee.MouseY;
        _MouseHasUpdatedggwp = true;

    }
    //Jag Fuckar inte med det här Tbh, Jag vill hällre att det ska vara ett event som skickas typ, gillar inte direkt hur det konstant skickar 0 ifall man inte rör men fungerar :D
    MousePosition InputService::GetDeltaMousePosition()
    {
        if (_MouseHasUpdatedggwp)
        {
            _MouseHasUpdatedggwp = false;
            return MousePosition{ .MouseX = _DeltaMousePosX, .MouseY = _DeltaMousePosY };
        }
        else
        {
            return MousePosition{ .MouseX = 0, .MouseY = 0 };
        }

    }
    MousePosition InputService::GetMousePosition()
    {
        return MousePosition{ .MouseX = _MousePosX, .MouseY = _MousePosY };
    }






    //statics
    void InputService::_PollKeys(GLFWwindow *window, int key, int scanCode, int action, int modifierBits)
    {

        auto* inputSystem = static_cast<InputService*>(glfwGetWindowUserPointer(window));

        switch (action)
        {
            case GLFW_PRESS:
            {
                std::println("Button {} was Pressed", key);
                //keypress eeveent 
                KeyPressedEvent eevee((bleh::Key)key);
                inputSystem->_InputDispatcher.Dispatch(eevee);
                break;
            
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent eevee((bleh::Key)key);
                inputSystem->_InputDispatcher.Dispatch(eevee);
                break;
        
            }

            case GLFW_REPEAT:
                break; // vad vill jag göra med detta, har det mest kvar för ifall det behövs för typing
        }
    }

    void window_size_callback(GLFWwindow* window, int width, int height)
    {
    }

    void InputService::_PollMouse(GLFWwindow* window, double xpos, double ypos)
    {
        auto* inputSystem = static_cast<InputService*>(glfwGetWindowUserPointer(window));
        MouseMoveEvent eevee = { .MouseX = xpos, .MouseY = ypos };
        inputSystem->_InputDispatcher.Dispatch(eevee);

        //_LastMousePosX = xpos;
    }

    void InputService::_PollMouseEvent(GLFWwindow* window, int button, int action, int mods)
    {

        auto* inputSystem = static_cast<InputService*>(glfwGetWindowUserPointer(window));
        switch (action)
        {
            case GLFW_PRESS:
            {
                KeyPressedEvent eevee((bleh::Key)button);
                inputSystem->_InputDispatcher.Dispatch(eevee);
                break;

            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent eevee((bleh::Key)button);
                inputSystem->_InputDispatcher.Dispatch(eevee);
                break;

            }
        }
    }
}