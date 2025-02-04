#include "../Includes/Shader.h"

std::map<const char*, Shader*> Shader::m_shaders = std::map<const char*, Shader*>();
GLuint Shader::m_current_shader_used = 0;


Shader::Shader(const char* shader_name, const char* vertex_file, const char* fragment_file, const char* geometry_file, bool is_post_process, bool is_ui)
{
	m_name = shader_name;
	try
	{
		bool is_object = !(is_post_process || is_ui);

		GLuint vertex_shader = loadShader(vertex_file, GL_VERTEX_SHADER, is_object ? "Engine/GLSL/vertex_helper.glsl" : nullptr);
		GLuint fragment_shader = loadShader(fragment_file, GL_FRAGMENT_SHADER, is_object ? "Engine/GLSL/fragment_helper.glsl" : nullptr);
		GLuint geometry_shader = 0;
		if (geometry_file != nullptr && geometry_file != "")
			geometry_shader = loadShader(geometry_file, GL_GEOMETRY_SHADER, nullptr);

		linkProgram(vertex_shader, fragment_shader, geometry_shader);

		m_is_post_process = is_post_process;
		m_is_ui = is_ui;
	}
	catch (const std::exception& exception)
	{
		std::cerr << "SHADER ERROR: " << m_name << ":\n" << exception.what() << "\n";
		m_id = 0;
	}
}

Shader::~Shader()
{
	glDeleteProgram(m_id);
}

void Shader::createShader(const char* shader_name, const char* vertex_file, const char* fragment_file, const char* geometry_file)
{
	Shader* shader = new Shader(shader_name, vertex_file, fragment_file, geometry_file);
	m_shaders[shader_name] = shader;
}

void Shader::createPostProcess(const char* shader_name, const char* vertex_file, const char* fragment_file, const char* geometry_file)
{
	Shader* shader = new Shader(shader_name, vertex_file, fragment_file, geometry_file, true);
	m_shaders[shader_name] = shader;
}

void Shader::createUiShader(const char* shader_name, const char* vertex_file, const char* fragment_file, const char* geometry_file)
{
	Shader* shader = new Shader(shader_name, vertex_file, fragment_file, geometry_file, false, true);
	m_shaders[shader_name] = shader;
}

void Shader::updateAllViewMatrix(glm::vec3 camera_position, glm::vec3 forward)
{
	glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view_matrix = glm::mat4(1.0f);
	view_matrix = glm::lookAt(camera_position, camera_position + forward, world_up);

	for (auto const& shader : m_shaders)
	{
		if (shader.second->isPostProcess() || shader.second->isUi())
			continue;

		shader.second->use();
		shader.second->setMatrix("matrices.view_matrix", view_matrix);
		shader.second->setVector3("main_camera.position", camera_position);
		shader.second->unuse();
	}
}

void Shader::updateAllProjectionMatrix(int window_width, int window_height)
{
	float fov = 90.0f;
	float aspectRatio = static_cast<float>(window_width) / window_height;
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;
	glm::mat4 projection_matrix = glm::mat4(1.0f);
	projection_matrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

	for (auto const& shader : m_shaders)
	{
		if (shader.second->isPostProcess() || shader.second->isUi())
			continue;

		shader.second->use();
		shader.second->setMatrix("matrices.projection_matrix", projection_matrix);
		shader.second->unuse();
	}
}

void Shader::updateAllLightColor(glm::vec3 color, bool is_ambient)
{
	const char* color_name = is_ambient ? "main_light.ambient_color" : "main_light.color";

	for (auto const& shader : m_shaders)
	{
		if (shader.second->isPostProcess() || shader.second->isUi())
			continue;

		shader.second->use();
		shader.second->setVector3(color_name, color);
		shader.second->unuse();
	}
}

void Shader::updateLightDirection(glm::vec3 direction)
{
	for (auto const& shader : m_shaders)
	{
		if (shader.second->isPostProcess() || shader.second->isUi())
			continue;

		shader.second->use();
		shader.second->setVector3("main_light.direction", direction);
		shader.second->unuse();
	}
}

Shader* Shader::Find(const char* name)
{
	return m_shaders[name];
}

bool Shader::isValid()
{
	return m_id != 0;
}

void Shader::use()
{
	m_current_shader_used = m_id;
	glUseProgram(m_id);
}

void Shader::unuse()
{
	m_current_shader_used = 0;
	glUseProgram(0);
}

void Shader::setInt(const char* name, GLint value)
{
	if (m_current_shader_used == m_id)
		glUniform1i(glGetUniformLocation(m_id, name), value);
}

void Shader::setFloat(const char* name, GLfloat value)
{
	if (m_current_shader_used == m_id)
		glUniform1f(glGetUniformLocation(m_id, name), value);
}

void Shader::setVector2(const char* name, glm::vec2 vector)
{
	if (m_current_shader_used == m_id)
		glUniform2fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(vector));
}

void Shader::setVector3(const char* name, glm::vec3 vector)
{
	if (m_current_shader_used == m_id)
		glUniform3fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(vector));
}

void Shader::setVector4(const char* name, glm::vec4 vector)
{
	if (m_current_shader_used == m_id)
		glUniform4fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(vector));
}

void Shader::setMatrix(const char* name, glm::mat4 matrix)
{
	if (m_current_shader_used == m_id)
		glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint Shader::getId()
{
	return m_id;
}

bool Shader::isPostProcess()
{
	return m_is_post_process;
}

bool Shader::isUi()
{
	return m_is_ui;
}

std::vector<ShaderProperty*> Shader::getShaderProperties()
{
	std::vector<ShaderProperty*> copy = std::vector<ShaderProperty*>();
	for (ShaderProperty* exposed_property : m_exposed_properties)
	{
		ShaderProperty* property_copy = new ShaderProperty{ exposed_property->name, exposed_property->type, exposed_property->value };
		copy.push_back(property_copy);

	}
	return copy;
}

const char* Shader::getName()
{
	return m_name;
}

std::string Shader::loadShaderSource(const char* filename)
{
	std::string line = "";
	std::string src = "";
	bool fill_exposed_properties = false;

	std::ifstream in_file;

	in_file.open(filename);
	if (in_file.is_open())
	{
		while (std::getline(in_file, line))
		{
			if (line != "#exposed" && line != "#end_exposed")
				src += line + "\n";
			else
				fill_exposed_properties = !fill_exposed_properties;

			if (fill_exposed_properties && line != "#exposed")
				saveExposedProperty(line);
		}
	}
	else
	{
		throw std::exception((filename + std::string(" did not load")).c_str());
	}
	in_file.close();

	return src;
}

void Shader::saveExposedProperty(std::string line)
{
	std::stringstream ss;
	ss.str(line);
	std::string tmp;
	ss >> tmp;

	std::string property_type;
	ss >> property_type;

	std::string property_name;
	ss >> property_name;

	bool default_value = false;
	if (property_name[property_name.size() - 1] == ';')
	{
		property_name = property_name.substr(0, property_name.size() - 1);
		default_value = true;
	}

	ShaderProperty* shader_property = createShaderProperty(property_name, property_type, ss, default_value);

	m_exposed_properties.push_back(shader_property);
}

ShaderProperty* Shader::createShaderProperty(std::string name, std::string type, std::stringstream& ss, bool default_value)
{
	ShaderProperty* shader_property = new ShaderProperty{ name, type, nullptr };
	std::string tmp = "";
	if (!default_value)
		ss >> tmp;

	if (type == "int")
	{
		int* value = new int(0);
		if (!default_value)
			ss >> *value;
		shader_property->value = value;
	}
	else if (type == "float")
	{
		float* value = new float(0.0f);
		if (!default_value)
			ss >> *value;
		shader_property->value = value;
	}
	else if (type == "vec2")
	{
		glm::vec2* value = new glm::vec2(0.0f);
		if (!default_value)
		{
			if (ss.peek() == ' ')
				ss.ignore(1);
			ss.ignore(5);
			ss >> value->x;
			ss.ignore(1);
			ss >> value->y;
		}
		shader_property->value = value;
	}
	else if (type == "vec3")
	{
		glm::vec3* value = new glm::vec3(0.0f);
		if (!default_value)
		{
			if (ss.peek() == ' ')
				ss.ignore(1);
			ss.ignore(5);
			ss >> value->x;
			ss.ignore(1);
			ss >> value->y;
			ss.ignore(1);
			ss >> value->z;
		}
		shader_property->value = value;
	}
	else if (type == "vec4")
	{
		glm::vec4* value = new glm::vec4(0.0f);
		if (!default_value)
		{
			if (ss.peek() == ' ')
				ss.ignore(1);
			ss.ignore(5);
			ss >> value->x;
			ss.ignore(1);
			ss >> value->y;
			ss.ignore(1);
			ss >> value->z;
			ss.ignore(1);
			ss >> value->w;
		}
		shader_property->value = value;
	}

	return shader_property;
}

GLuint Shader::loadShader(const char* filename, GLenum type, const char* helper_filename)
{
	m_exposed_properties = std::vector<ShaderProperty*>();
	std::string src_str = loadShaderSource(filename);
	if (helper_filename != nullptr)
	{
		std::string helper_str = loadShaderSource(helper_filename);
		src_str = helper_str + "\n" + src_str;
	}
	const GLchar* src = src_str.c_str();

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	char info_log[512];
	GLint success;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info_log);
		throw std::exception((filename + std::string(" did not compile:\n") + info_log).c_str());
	}

	return shader;
}

void Shader::linkProgram(GLuint vertex_shader, GLuint fragment_shader, GLuint geometry_shader)
{
	m_id = glCreateProgram();
	glAttachShader(m_id, vertex_shader);
	glAttachShader(m_id, fragment_shader);
	if (geometry_shader != 0)
		glAttachShader(m_id, geometry_shader);

	glLinkProgram(m_id);

	char info_log[512];
	GLint success;

	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_id, 512, NULL, info_log);
		throw std::exception((std::string("Link failed:\n") + info_log).c_str());
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	if (geometry_shader != 0)
		glDeleteShader(geometry_shader);

	glUseProgram(0);
}
