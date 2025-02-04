#pragma once

#include "Material.h";

class PostProcess
{
public:
	PostProcess(int window_width, int window_height);
	~PostProcess();

	void setWindowSize(int window_width, int window_height);

	void enableFramebuffer();
	void draw();

	void setBloomSize(int size);
	void setBloomThreshold(float threshold);

private:
	void initializeBuffers();
	void initializeShader();

private:
	int m_window_width;
	int m_window_height;

	GLuint fbo;
	GLuint rbo;
	GLuint fbo_texture;

	GLuint rect_vao;
	GLuint rect_vbo;

	GLuint attribute_v_coord_postproc;
	GLuint uniform_fbo_texture;

	Shader* m_post_process_shader;
	Material* m_post_process_material;
};