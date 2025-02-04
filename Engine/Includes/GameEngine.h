#pragma once

#include "GameObject.h"
#include "MeshRenderer.h"
#include "Light.h"
#include "ShaderData.h"
#include "Camera.h"
#include "PostProcess.h"
#include "OBJLoader.h"
#include "Canvas.h"
#include "Skybox.h"

/*
	Keywords :
	- private / public
	- static
	- singleton
	- operator overloading
	- callback
*/

class GameEngine
{
public:
	~GameEngine();

	//Singleton
	static void initializeEngine(const char* window_name, int width, int height, ShaderData shader_list[], int shader_array_size);
	static GameEngine* getInstance();
	GameEngine(GameEngine& other) = delete;
	void operator=(const GameEngine&) = delete;

	static GameObject* createGameObject(const char* name, glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
	static GameObject* createUiElement(const char* name, glm::vec2 position = glm::vec2(0.0f), float rotation = 0.0f, glm::vec2 size = glm::vec2(1.0f));
	static void destroyObject(GameObject* object);


	//Engine
	void update();
	bool shouldClose();
	void exit();

	bool isKeyPressed(int key);
	bool isMouseButtonPressed(int key);
	void setCursorState(bool enable);

	void setSkyboxTexture(Texture* texture);
	void setBloomSize(int size);
	void setBloomThreshold(float threshold);

	static float getTime();
	static float getDeltaTime();
	static glm::vec2 getCursorPosition();
	static glm::vec2 getCursorDeltaPosition();

private:
	GameEngine(const char* window_name, int width, int height, ShaderData shader_list[], int shader_array_size);

	void addGameObject(GameObject* game_object);
	void addUiObject(GameObject* game_object);
	void destroyGameObject(GameObject* object);

	//Initialization
	void intializeGlew();
	void framebufferResizeCallback(GLFWwindow* window, int framebuffer_width, int framebuffer_height);
	void createWindow(const char* window_name, int width, int height);
	void enableOpenGlOptions();
	void createShaders(ShaderData shader_list[], int shader_array_size);

	//Engine
	void updateTime();
	void updateCursorPosition();
	void updateInput();
	void updateComponents();
	void draw();

private:
	//Window
	GLFWwindow* m_window;
	int m_window_width;
	int m_window_height;

	//Engine
	std::list<GameObject*> m_game_objects;
	std::list<Shader*> m_shader_list;
	PostProcess* m_post_process;

	//Time
	static float m_time;
	static float m_delta_time;
	float m_draw_timer;
	float m_draw_time;

	//Cursor
	static glm::vec2 m_cursor_position;
	static glm::vec2 m_cursor_delta_position;

	//Canvas
	Canvas* m_canvas;

	//Skybox
	Skybox* m_skybox;

	//Singleton
	static GameEngine* m_instance;
};