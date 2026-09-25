#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <functional>
#include <unordered_map>

#include "Event.h"
#include "BlehKeys.h"
namespace bleh
{
    enum class KeyState
    {
        None = -1,
        KeyUp, 
        KeyDown,
    };



    class KeyEvent : public Event
    {
        public:
            inline bleh::Key GetKeyCode() const { return _KeyCode; }
            KeyEvent(bleh::Key keyCode)
                : _KeyCode(keyCode) {}
        protected:
            bleh::Key _KeyCode;

    };

    class KeyPressedEvent : public KeyEvent{public: KeyPressedEvent(bleh::Key keyCode) : KeyEvent(keyCode){}};
    class KeyReleasedEvent : public KeyEvent{public: KeyReleasedEvent(bleh::Key keyCode) : KeyEvent(keyCode){}};
    class KeyRepeatEvent : public KeyEvent{};
    class MousePressedEvent : public KeyEvent { public: MousePressedEvent(bleh::Key keyCode) : KeyEvent(keyCode) {} };
    class MouseReleasedEvent : public KeyEvent { public: MouseReleasedEvent(bleh::Key keyCode) : KeyEvent(keyCode) {} };
    class MousePosition
    {
    public:
        double MouseX;
        double MouseY;
    };

    class MouseMoveEvent : public Event
    {
        public:
            double MouseX;
            double MouseY;
    };



    class InputService 
    {
        public: 
            InputService(GLFWwindow *window);
            bool GetKeyDown(bleh::Key);
            bool GetKeyUp(bleh::Key);
            bool GetInputClick(bleh::Key keyToLookUp);

            void OnKeyReleased(KeyReleasedEvent& e);
            void OnKeyPressed(KeyPressedEvent& e);
            void SubscribeToKeyClick(std::function<void(void*)> _OnMouseClick);
            MousePosition GetDeltaMousePosition();
            MousePosition GetMousePosition();
    
        private:
            static void _PollKeys(GLFWwindow *window, int key, int scanCode, int action, int modifierBits); 
            static void _PollMouse(GLFWwindow* window, double xpos, double ypos);
            static void _PollMouseEvent(GLFWwindow* window, int button, int action, int mods);
            void _UpdateMousePosition(MouseMoveEvent& eevee);


            double _MousePosX = 0;
            double _MousePosY = 0;
            double _DeltaMousePosX = 0;
            double _DeltaMousePosY = 0;
            bool _MouseHasUpdatedggwp = false;
            EventDispatcher _InputDispatcher;
            std::unordered_map<bleh::Key, KeyState> _KeyStateMap;
            std::unordered_map<bleh::Key, KeyState> _KeyPressedStateMap;

    };

}
