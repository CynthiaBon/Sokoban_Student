#include "../Includes/GameEngine.h"

GameEngine* GameEngine::m_instance = nullptr;
float GameEngine::m_time = 0.0f;
float GameEngine::m_delta_time = 0.0f;
glm::vec2 GameEngine::m_cursor_position = glm::vec2(0.0f);
glm::vec2 GameEngine::m_cursor_delta_position = glm::vec2(0.0f);

void GameEngine::initializeEngine(const char* window_name, int width, int height, ShaderData shader_list[], int shader_array_size)
{
	if (m_instance == nullptr)
		new GameEngine(window_name, width, height, shader_list, shader_array_size);
}

GameEngine::GameEngine(const char* window_name, int width, int height, ShaderData shader_list[], int shader_array_size)
{
	m_instance = this;

	glfwInit();
	createWindow(window_name, width, height);
	intializeGlew();
	enableOpenGlOptions();

	createShaders(shader_list, shader_array_size);
	m_post_process = new PostProcess(width, height);

	m_game_objects = std::list<GameObject*>();

	GameObject* camera = createGameObject("Main Camera");
	Camera* camera_component = new Camera(camera);

	GameObject* light = createGameObject("Main Light", glm::vec3(0.0f), glm::vec3(90.0f, 90.0f, 0.0f), glm::vec3(100.0f));
	Light* light_component = new Light(light, glm::vec3(1.0f, 1.0f, 0.8f), 2.0f, glm::vec3(0.2f, 0.2f, 0.2f));

	updateCursorPosition();
	m_cursor_delta_position = glm::vec2(0.0f);

	m_canvas = new Canvas();
	m_skybox = new Skybox();

	m_draw_time = 1.0f / 60.0f;
	m_draw_timer = 0.0f;
}

void GameEngine::addGameObject(GameObject* game_object)
{
	m_game_objects.push_back(game_object);
}

void GameEngine::addUiObject(GameObject* ui_object)
{
	m_canvas->addElement(ui_object);
}

void GameEngine::destroyGameObject(GameObject* object)
{
	m_game_objects.remove(object);

	std::list<MonoBehaviour*> components = object->getAllComponents();
	for (auto component : components)
	{
		delete component;
	}

	delete object;
}

GameEngine::~GameEngine()
{
}

GameEngine* GameEngine::getInstance()
{
	return m_instance;
}

void GameEngine::intializeGlew()
{
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		throw std::exception("Error in GLEW init");
	}
}

void GameEngine::framebufferResizeCallback(GLFWwindow* window, int framebuffer_width, int framebuffer_height)
{
	Shader::updateAllProjectionMatrix(framebuffer_width, framebuffer_height);
	glViewport(0, 0, framebuffer_width, framebuffer_height);
	m_window_width = framebuffer_width;
	m_window_height = framebuffer_height;
	TextRenderer::WindowAspect = glm::vec2(1.0f / m_window_width, 1.0f / m_window_height);

	m_post_process->setWindowSize(framebuffer_width, framebuffer_height);
}

void GameEngine::createWindow(const char* window_name, int width, int height)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	m_window = glfwCreateWindow(width, height, window_name, NULL, NULL);

	glfwSetWindowUserPointer(m_window, this);
	auto resizeCallback = [](GLFWwindow* window, int width, int height)
		{
			static_cast<GameEngine*>(glfwGetWindowUserPointer(window))->framebufferResizeCallback(window, width, height);
		};

	glfwSetFramebufferSizeCallback(m_window, resizeCallback);
	glfwMakeContextCurrent(m_window);

	m_window_width = width;
	m_window_height = height;
	TextRenderer::WindowAspect = glm::vec2(1.0f / m_window_width, 1.0f / m_window_height);
}

void GameEngine::enableOpenGlOptions()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDepthMask(GL_TRUE);
}

void GameEngine::createShaders(ShaderData shader_list[], int shader_array_size)
{
	m_shader_list = std::list<Shader*>();
	for (int i = 0; i < shader_array_size; i++)
	{
		if (shader_list[i].is_ui)
			Shader::createUiShader(shader_list[i].name, shader_list[i].vertex_filename, shader_list[i].fragment_filename, shader_list[i].geometry_filename);
		else
			Shader::createShader(shader_list[i].name, shader_list[i].vertex_filename, shader_list[i].fragment_filename, shader_list[i].geometry_filename);
		m_shader_list.push_back(Shader::Find(shader_list[i].name));
	}
	Shader::updateAllProjectionMatrix(m_window_width, m_window_height);
}

void GameEngine::update()
{
	updateTime();
	updateCursorPosition();
	updateInput();
	updateComponents();
	draw();
}

void GameEngine::updateTime()
{
	float time = static_cast<float>(glfwGetTime());
	m_delta_time = time - m_time;
	m_time = time;
}

void GameEngine::updateCursorPosition()
{
	double x = 0.0f;
	double y = 0.0f;
	glfwGetCursorPos(m_window, &x, &y);
	y = -y;

	glm::vec2 cursor_position = glm::vec2(x, y);
	m_cursor_delta_position = cursor_position - m_cursor_position;
	m_cursor_position = cursor_position;
}

void GameEngine::updateInput()
{
	glfwPollEvents();

	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

void GameEngine::updateComponents()
{
	for (GameObject* object : m_game_objects)
	{
		std::list<MonoBehaviour*> components = object->getAllComponents();
		for (MonoBehaviour* compenent : components)
		{
			compenent->update();
		}
	}
}

void GameEngine::draw()
{
	if (m_time - m_draw_timer < m_draw_time)
		return;
	m_draw_timer = m_time;

	m_post_process->enableFramebuffer();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	m_skybox->render(Camera::getMain()->getGameObject()->getTransform()->getPosition());
	glClear(GL_DEPTH_BUFFER_BIT);

	for (Shader* shader : m_shader_list)
	{
		if (shader->isPostProcess() || shader->isUi())
			continue;

		shader->use();

		for (GameObject* object : m_game_objects)
		{
			MeshRenderer* renderer = object->getComponent<MeshRenderer>();

			if (renderer != nullptr && renderer->isActive()
				&& renderer->getMaterial()->getShader()->getName() == shader->getName())
			{
				shader->setMatrix("matrices.model_matrix", object->getTransform()->getModelMatrix());
				renderer->render();
			}
		}

		shader->unuse();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	m_post_process->draw();
	m_canvas->draw(m_shader_list);

	glfwSwapBuffers(m_window);
}

bool GameEngine::isKeyPressed(int key)
{
	return glfwGetKey(m_window, key) == GLFW_PRESS;
}

bool GameEngine::isMouseButtonPressed(int key)
{
	return glfwGetMouseButton(m_window, key) == GLFW_PRESS;
}

glm::vec2 GameEngine::getCursorPosition()
{
	return m_cursor_position;
}

glm::vec2 GameEngine::getCursorDeltaPosition()
{
	return m_cursor_delta_position;
}

void GameEngine::setCursorState(bool enable)
{
	if (enable)
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void GameEngine::setSkyboxTexture(Texture* texture)
{
	m_skybox->setTexture(texture);
}

void GameEngine::setBloomSize(int size)
{
	m_post_process->setBloomSize(size);
}

void GameEngine::setBloomThreshold(float threshold)
{
	m_post_process->setBloomThreshold(threshold);
}

float GameEngine::getTime()
{
	return m_time;
}

float GameEngine::getDeltaTime()
{
	return m_delta_time;
}

bool GameEngine::shouldClose()
{
	return m_window == nullptr || glfwWindowShouldClose(m_window);
}

void GameEngine::exit()
{
	glfwSetWindowShouldClose(m_window, GLFW_TRUE);
	glfwDestroyWindow(m_window);
	m_window = nullptr;
	glfwTerminate();
}

GameObject* GameEngine::createGameObject(const char* name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	GameObject* object = new GameObject(name);
	object->getTransform()->setPosition(position);
	object->getTransform()->setRotation(rotation);
	object->getTransform()->setScale(scale);
	getInstance()->addGameObject(object);
	return object;
}

GameObject* GameEngine::createUiElement(const char* name, glm::vec2 position, float rotation, glm::vec2 size)
{
	GameObject* object = new GameObject(name, true);
	RectTransform* transform = RectTransform::castToRect(object->getTransform());
	transform->setPosition(position);
	transform->setRotation(rotation);
	transform->setSize(size);
	getInstance()->addUiObject(object);
	return object;
}

void GameEngine::destroyObject(GameObject* object)
{
	m_instance->destroyGameObject(object);
}
