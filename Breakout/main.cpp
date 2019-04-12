#include "stdafx.h"


#include "Game.h"


#ifdef _DEBUG
void APIENTRY debugCallback(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar *message, const void *userParam) {
	std::cerr << "0x" << std::hex << id << std::dec << ": ";

	switch(severity) {
	case GL_DEBUG_SEVERITY_HIGH: std::cerr << "High"; break;
	case GL_DEBUG_SEVERITY_MEDIUM: std::cerr << "Medium";  break;
	case GL_DEBUG_SEVERITY_LOW: std::cerr << "Low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cerr << "Notification"; break;
	default: std::cerr << "Unknown Severity (0x" << std::hex << severity << std::dec << ")"; break;
	}
	std::cerr << " ";

	switch(src) {
	case GL_DEBUG_SOURCE_API: std::cerr << "API";  break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: std::cerr << "Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cerr << "Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY: std::cerr << "Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION: std::cerr << "Application"; break;
	case GL_DEBUG_SOURCE_OTHER: std::cerr << "Other"; break;
	default: std::cerr << "Unknown Source (0x" << std::hex << severity << std::dec << ")"; break;
	}
	std::cerr << " ";

	switch(type) {
	case GL_DEBUG_TYPE_ERROR: std::cerr << "Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cerr << "Deprecated Behavior"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: std::cerr << "Undefined Behavior"; break;
	case GL_DEBUG_TYPE_PORTABILITY: std::cerr << "Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE: std::cerr << "Performance"; break;
	case GL_DEBUG_TYPE_MARKER: std::cerr << "Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP: std::cerr << "Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP: std::cerr << "Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER: std::cerr << "Other"; break;
	default: std::cerr << "Unknown Type (0x" << std::hex << severity << std::dec << ")"; break;
	}
	std::cerr << " ";

	std::cerr << "Message: " << message << std::endl;
}
#endif

int main() {
	glfwInit();
#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
#else
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
#endif
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Breakout", nullptr, nullptr);
	if(window == nullptr) {
		glfwTerminate();
		std::cerr << "Failed to create GLFW window" << std::endl;
		throw std::runtime_error("");
	}
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		throw std::runtime_error("");
	}
#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(debugCallback, nullptr);
	GLuint uselessIDs = {0x20071};
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 1, &uselessIDs, GL_FALSE);
#endif

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	});

	Game game(window);

	while(!glfwWindowShouldClose(window)) {
		game.tick();
		game.render();

		// Display
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}
