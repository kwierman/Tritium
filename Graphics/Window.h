#ifndef Tritium_Graphics_Window_h_
#define Tritium_Graphics_Window_h_

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw3.h>

// Include GLM
#include <glm/glm.hpp>

namespace Tritium{
	namespace Graphics{

		class Window{
			glm::GLFWwindow* fWindow;

		public:
			Window(const std::string& name="Tritium", const unsigned& width=1024, const unsigned& height = 768 ) throw(GraphicsException): fWindow(NULL) {
				OpenGLManager::GetInstance().Init();

				fWindow = glm::glfwCreateWindow(width, hight, name, NULL, NULL);

				if(!fWindow){
					throw GraphicsException("Failed to open GLFW window");
					OpenGLManager::GetInstance().Terminate();
				}

				OpenGLManager::GetInstance().SetContextCurrent(fWindow);
			}

		};

	}
}


#endif //File Guardian