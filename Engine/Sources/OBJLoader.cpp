#include "../Includes/OBJLoader.h"

std::vector<glm::vec3> OBJLoader::vertex_positions;
std::vector<glm::vec2> OBJLoader::vertex_texcoords;
std::vector<glm::vec3> OBJLoader::vertex_normals;

std::vector<GLuint> OBJLoader::vertex_position_indicies;
std::vector<GLuint> OBJLoader::vertex_texcoord_indicies;
std::vector<GLuint> OBJLoader::vertex_normal_indicies;

OBJLoader::OBJLoader()
{
}

OBJLoader::~OBJLoader()
{
}

Mesh* OBJLoader::loadObj(const char* filename, bool valid_triangle)
{
	Mesh* mesh = nullptr;

	try
	{
		initializeArrays();
		std::ifstream in_file;
		loadFile(filename, in_file);
		parseFile(in_file);
		mesh = constructMesh(valid_triangle);
	}
	catch (const std::exception& exception)
	{
		std::cerr << "OBJ LOADER ERROR:\n" << exception.what() << "\n";
	}

	return mesh;
}

void OBJLoader::loadFile(const char* filename, std::ifstream& in_file)
{
	in_file.open(filename);
	if (!in_file.is_open())
		throw std::exception((filename + std::string(" did not load")).c_str());
}

void OBJLoader::initializeArrays()
{
	vertex_positions = std::vector<glm::vec3>();
	vertex_texcoords = std::vector<glm::vec2>();
	vertex_normals = std::vector<glm::vec3>();

	vertex_position_indicies = std::vector<GLuint>();
	vertex_texcoord_indicies = std::vector<GLuint>();;
	vertex_normal_indicies = std::vector<GLuint>();;
}

void OBJLoader::parseFile(std::ifstream& in_file)
{
	std::stringstream ss;
	std::string line = "";
	std::string prefix = "";

	while (std::getline(in_file, line))
	{
		ss.clear();
		ss.str(line);

		prefix = "";
		ss >> prefix;

		if (prefix == "v")
			fillPositionsArray(ss);
		else if (prefix == "vt")
			fillTexcoordsArray(ss);
		else if (prefix == "vn")
			fillNormalsArray(ss);
		else if (prefix == "f")
			fillIndicesArray(ss);
	}
}

void OBJLoader::fillPositionsArray(std::stringstream& ss)
{
	glm::vec3 temp_vec;
	ss >> temp_vec.x >> temp_vec.y >> temp_vec.z;
	vertex_positions.push_back(temp_vec);
}

void OBJLoader::fillTexcoordsArray(std::stringstream& ss)
{
	glm::vec2 temp_vec;
	ss >> temp_vec.x >> temp_vec.y;
	vertex_texcoords.push_back(temp_vec);
}

void OBJLoader::fillNormalsArray(std::stringstream& ss)
{
	glm::vec3 temp_vec;
	ss >> temp_vec.x >> temp_vec.y >> temp_vec.z;
	vertex_normals.push_back(temp_vec);
}

void OBJLoader::fillIndicesArray(std::stringstream& ss)
{
	GLint temp_glint = 0;
	int counter = 0;

	while (ss >> temp_glint)
	{
		temp_glint -= 1;
		if (counter == 0)
			vertex_position_indicies.push_back(temp_glint);
		else if (counter == 1)
			vertex_texcoord_indicies.push_back(temp_glint);
		else
			vertex_normal_indicies.push_back(temp_glint);

		int next_char = ss.peek();
		if (next_char == '/' || next_char == ' ' || next_char == '\n')
			ss.ignore(1);

		counter = (counter + 1) % 3;
	}
}

Mesh* OBJLoader::constructMesh(bool valid_triangle)
{
	std::vector<Vertex> vertices = std::vector<Vertex>(vertex_position_indicies.size());
	std::vector<GLuint> indices = valid_triangle ? vertex_position_indicies : std::vector<GLuint>();
	int loop_size = valid_triangle ? vertex_positions.size() : vertex_position_indicies.size();

	for (int i = 0; i < loop_size; i++)
	{
		GLuint position_indice = vertex_position_indicies[i];
		GLuint texcoord_indice = vertex_texcoord_indicies[i];
		GLuint normal_indice = vertex_normal_indicies[i];
		
		int vertex_index = valid_triangle ? vertex_position_indicies[i] : i;
		vertices[vertex_index].position = vertex_positions[position_indice];
		vertices[vertex_index].texcoord = vertex_texcoords[texcoord_indice];
		vertices[vertex_index].normal = vertex_normals[normal_indice];
	}

	return new Mesh(vertices, indices);
}
