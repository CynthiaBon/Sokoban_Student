#pragma once

#include "libs.h"
#include "Mesh.h"
#include <sstream>

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();

	static Mesh* loadObj(const char* filename, bool valid_triangle = false);

private:
	static void loadFile(const char* filename, std::ifstream& in_file);
	static void initializeArrays();
	static void parseFile(std::ifstream& in_file);
	static void fillPositionsArray(std::stringstream& ss);
	static void fillTexcoordsArray(std::stringstream& ss);
	static void fillNormalsArray(std::stringstream& ss);
	static void fillIndicesArray(std::stringstream& ss);
	static Mesh* constructMesh(bool valid_triangle);

private:
	static std::vector<glm::vec3> vertex_positions;
	static std::vector<glm::vec2> vertex_texcoords;
	static std::vector<glm::vec3> vertex_normals;

	static std::vector<GLuint> vertex_position_indicies;
	static std::vector<GLuint> vertex_texcoord_indicies;
	static std::vector<GLuint> vertex_normal_indicies;
};