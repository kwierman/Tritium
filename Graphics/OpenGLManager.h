#ifndef Tritium_OpenGLManager_h_
#define Tritium_OpenGLManager_h_

namespace Tritium{
	namespace Graphics{

		class OpenGLManagerImpl{

		public:
			void Initialize() throw(GraphicsException)
			{
					// Initialise GLFW
				if( !glfwInit() )
					throw GraphicsException("Failed to Initialize GLFW", true);

				glfwWindowHint(GLFW_SAMPLES, 4);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			}
			void Terminate(){
				glfwTerminate();
			}

			void InitGLEW() throw(GraphicsException){
				if(glewInit() != GLEW_OK)
					throw GraphicsException("Failed to Initialize GLEW", true);
			}

			void SetInput(GLFWWindow* window){
				glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
			}

		};
	}
}

#endif //File Guardian