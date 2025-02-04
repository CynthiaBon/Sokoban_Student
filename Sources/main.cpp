#include "../Engine/Includes/GameEngine.h"
#include "../Includes/GameManager.h"

/*
	Keywords :
	- include
	- function / method
	- public / private
	- guard
	- throw / exception
	- try / catch
	- pointer
	- SOLID principles
*/

void initializeEngine()
{
	const char* window_name = "Open GL Window";
	int window_width = 1280;
	int window_height = 720;

	ShaderData shader_list[] = {
		"Base Shader", "Engine/GLSL/vertex_core.glsl", "Engine/GLSL/fragment_core.glsl", nullptr, false,
		"UI Shader", "Engine/GLSL/vertex_ui.glsl", "Engine/GLSL/fragment_ui.glsl", nullptr, true,
		"Text Shader", "Engine/GLSL/vertex_ui.glsl", "Engine/GLSL/fragment_text.glsl", nullptr, true
	};
	int shader_array_size = sizeof(shader_list) / sizeof(ShaderData);

	GameEngine::initializeEngine(window_name, window_width, window_height, shader_list, shader_array_size);
}

void runGame()
{
	GameObject* game_manager_object = GameEngine::createGameObject("GameObject");

	while (!GameEngine::getInstance()->shouldClose())
	{
		try
		{
			GameEngine::getInstance()->update();
		}
		catch (const std::exception& e)
		{
			std::cerr << "ERROR: " << e.what() << "\n";
		}
	}

	GameEngine::getInstance()->exit();
}

void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght, const GLchar* message, const void* user_param)
{
	std::cout << message << "\n";
}

void enableDebugMode()
{
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(debugCallback, 0);
}

int main()
{
	initializeEngine();

	runGame();

	return 0;
}