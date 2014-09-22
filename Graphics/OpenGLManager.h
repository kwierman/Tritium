#ifndef Tritium_OpenGLManager_h_
#define Tritium_OpenGLManager_h_

#include "Protium/Singleton/Singleton.h"
#include "Protium/Threads/ThreadingPolicy.h"
#include "Protium/Threads/Mutex.h"

namespace Tritium{
	namespace Graphics{

		class OpenGLManagerImpl{
		private:
			OpenGLManagerImpl(const OpenGLManagerImpl&);
			OpenGLManagerImpl& operator=(const OpenGLManagerImpl&);

		public:
			OpenGLManagerImpl(){}
			virtual ~OpenGLManagerImpl(){}


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


		class OpenGLManager : public OpenGLManagerImpl{
			typedef Protium::Singleton::Singleton<	OpenGLManagerImpl, 
													Protium::Singleton::CreateStatic, 
													Protium::Singleton::DeleteFirst, 
													Protium::Threads::StaticLocked> OpenGLManagerSingleton;
			public:
				inline static OpenGLManager& Instance(){
					return OpenGLManagerSingleton::Instance();
				}
				inline OpenGLManager() : OpenGLManagerImpl() {}
				inline ~OpenGLManager(){}
		};
	}
}

#endif //File Guardian