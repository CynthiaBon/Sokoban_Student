#pragma once

#include "libs.h"
#include "ShaderProperty.h";
#include <sstream>

/*
	Keywords :
	- static
	- model, view and projection matrices
	- std::map
	- parsing text
*/

class Shader
{
public:
	static void createShader(const char* shader_name, const char* vertex_file, const char* fragment_file, const char* geometry_file = "");
	static void createPostProcess(const char* shader_name, const char* vertex_file, const char* fragment_file, const char* geometry_file = "");
	static void createUiShader(const char* shader_name, const char* vertex_file, const char* fragment_file, const char* geometry_file = "");
	static void updateAllViewMatrix(glm::vec3 camera_position, glm::vec3 forward);
	static void updateAllProjectionMatrix(int window_width, int window_height);
	static void updateAllLightColor(glm::vec3 color, bool is_ambient);
	static void updateLightDirection(glm::vec3 direction);
	static Shader* Find(const char* name);
	~Shader();

	const char* getName();
	bool isValid();
	void use();
	void unuse();
	void setInt(const char* name, GLint value);
	void setFloat(const char* name, GLfloat value);
	void setVector2(const char* name, glm::vec2 vector);
	void setVector3(const char* name, glm::vec3 vector);
	void setVector4(const char* name, glm::vec4 vector);
	void setMatrix(const char* name, glm::mat4 matrix);
	GLuint getId();
	bool isPostProcess();
	bool isUi();
	std::vector<ShaderProperty*> getShaderProperties();

private:
	Shader(const char* shader_name, const char* vertex_file, const char* fragment_file, const char* geometry_file, bool is_post_process = false, bool is_ui = false);
	std::string loadShaderSource(const char* filename);
	void saveExposedProperty(std::string line);
	ShaderProperty* createShaderProperty(std::string name, std::string type, std::stringstream& ss, bool default_value);
	GLuint loadShader(const char* filename, GLenum type, const char* helper_filename);
	void linkProgram(GLuint vertex_shader, GLuint fragment_shader, GLuint geometry_shader);

private:
	const char* m_name;
	GLuint m_id;
	bool m_is_post_process;
	bool m_is_ui;

	std::vector<ShaderProperty*> m_exposed_properties;

	static std::map<const char*, Shader*> m_shaders;
	static GLuint m_current_shader_used;
};