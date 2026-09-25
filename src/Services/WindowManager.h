#include <vector>
#include <Services/Window.h>
#include <cstdint>
namespace bleh
{
	class WindowManager
	{

		public:
		
			WindowManager();
			void GetActiveWindow();
			std::vector<Window>& GetAllWindows();
			void GetWindowByName();
			Window& GetWindowByHandle(uint8_t handle);
			void SetActiveWindow(uint8_t handle);

			void CreateWindow(WindowSpecifications WindowSpecs, uint8_t& WindowHandle, GLFWwindow* SharedContextWindow = nullptr);
			void CreateWindow(WindowSpecifications WindowSpecs, uint8_t& WindowHandle, uint8_t ContextHandle);
			void RemoveWindow();

		private:

			//eversince i remininisced i keep on asking why?
			//sat myself down found it to generous to cry
			void _CheckIfFirstWindowExists();

			bool _FirstWindowExists = false;
			std::vector<Window> WindowStorer;

			//main Window är alltid [0] när den stängs stängs alla andra
			
	};
}