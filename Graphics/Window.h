#ifndef Tritium_Graphics_Window_h_
#define Tritium_Graphics_Window_h_

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>

namespace Tritium{
	namespace Graphics{

		class Window{
			glm::GLFWwindow* fWindow;

		public:
			Window() throw(GraphicsException): fWindow(NULL) {
				OpenGLManager::GetInstance().Init();

				fWindow = glm::glfwCreateWindow(1024, 768, "Tritium", NULL, NULL);

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