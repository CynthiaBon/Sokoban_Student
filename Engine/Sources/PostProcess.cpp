#include "../Includes/PostProcess.h"
#include "../Includes/Texture.h"

float rectangle_vertices[] =
{
	-1.0f, 1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 0.0f,
	1.0f, -1.0f, 1.0f, 0.0f,

	-1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 1.0f
};

PostProcess::PostProcess(int window_width, int window_height) :
	m_window_width(window_width), m_window_height(window_height)
{
	try
	{
		initializeBuffers();
		initializeShader();
	}
	catch (const std::exception& exception)
	{
		std::cerr << "POST PROCESS ERROR: " << exception.what() << "\n";
	}
}

PostProcess::~PostProcess()
{

}

void PostProcess::setWindowSize(int window_width, int window_height)
{
	m_window_width = window_width;
	m_window_height = window_height;

	glBindTexture(GL_TEXTURE_2D, fbo_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_window_width, m_window_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_window_width, m_window_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	m_post_process_material->setVector2("screen_size", glm::vec2(m_window_width, m_window_height));
}

void PostProcess::initializeBuffers()
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &fbo_texture);
	glBindTexture(GL_TEXTURE_2D, fbo_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_window_width, m_window_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_window_width, m_window_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	GLenum fbo_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fbo_status != GL_FRAMEBUFFER_COMPLETE)
		throw std::exception(("Framebuffer incomplete: " + std::to_string(fbo_status)).c_str());

	glCreateVertexArrays(1, &rect_vao);
	glBindVertexArray(rect_vao);

	glGenBuffers(1, &rect_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, rect_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle_vertices), &rectangle_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void PostProcess::initializeShader()
{
	Shader::createPostProcess("PostProcess", "Engine/GLSL/post_process_vertex.glsl", "Engine/GLSL/post_process_fragment.glsl");
	m_post_process_shader = Shader::Find("PostProcess");
	m_post_process_material = new Material(m_post_process_shader);

	m_post_process_material->setVector2("screen_size", glm::vec2(m_window_width, m_window_height));
	m_post_process_material->setInt("bloom_size", 50);
	m_post_process_material->setFloat("bloom_threshold", 3.0f);
}

void PostProcess::enableFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void PostProcess::draw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_post_process_shader->use();
	glBindVertexArray(rect_vao);
	glDisable(GL_DEPTH_TEST);

	m_post_process_material->sendToShader();
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(m_post_process_shader->getId(), "screen_texture"), 0);
	glBindTexture(GL_TEXTURE_2D, fbo_texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	m_post_process_material->unbindTextures();
	m_post_process_shader->unuse();
}

void PostProcess::setBloomSize(int size)
{
	m_post_process_material->setInt("bloom_size", size);
}

void PostProcess::setBloomThreshold(float threshold)
{
	m_post_process_material->setFloat("bloom_threshold", threshold);
}
