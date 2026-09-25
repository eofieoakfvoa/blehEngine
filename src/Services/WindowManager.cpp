#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowManager.h"
#include <print>
namespace bleh
{
	WindowManager::WindowManager()
	{

	}
	std::vector<Window>& WindowManager::GetAllWindows()
	{
		return WindowStorer;
	}
	Window& WindowManager::GetWindowByHandle(uint8_t Handle)
	{
		return WindowStorer[Handle];
	}
	void WindowManager::SetActiveWindow(uint8_t Handle)
	{
		glfwMakeContextCurrent(GetWindowByHandle(Handle).GetWindow());
	}

	void WindowManager::CreateWindow(WindowSpecifications windowspec, uint8_t& windowhandle, GLFWwindow* SharedContextWindow)
	{
		WindowStorer.emplace_back(windowspec, SharedContextWindow);

		glfwMakeContextCurrent(WindowStorer.back().GetWindow());
		
		_CheckIfFirstWindowExists();

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.117f, 0.109f, 0.137f, 1.0f);

		windowhandle = WindowStorer.size() - 1; //problem när man tar bort sen lägger till eftersom den kommer ha samma size() - 1 som den som la tills innan den
	}	
	void WindowManager::CreateWindow(WindowSpecifications windowspec, uint8_t& windowhandle, uint8_t SharedContextHandle)
	{
		CreateWindow(windowspec, windowhandle, GetWindowByHandle(SharedContextHandle).GetWindow() );
	}

	void WindowManager::_CheckIfFirstWindowExists()
	{
		if (!_FirstWindowExists)
		{
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::println("Failed to initialize GLAD");
				glfwTerminate();
				return;
			}
			_FirstWindowExists = true;
		}
	}




}