#include "../Includes/Debug.h"

void Debug::log(const char object)
{
	std::cout << object << "\n";
}

void Debug::log(const std::string object)
{
	std::cout << object << "\n";
}

void Debug::log(const int object)
{
	std::cout << object << "\n";
}

void Debug::log(const float object)
{
	std::cout << object << "\n";
}

void Debug::log(const glm::vec2 object)
{
	std::cout << "(" << object.x << ", " << object.y << ")\n";
}

void Debug::log(const glm::vec3 object)
{
	std::cout << "(" << object.x << ", " << object.y << ", " << object.z << ")\n";
}

void Debug::logError(const char object)
{
	std::cerr << "ERROR: " << object << "\n";
}

void Debug::logError(const std::string object)
{
	std::cerr << "ERROR: " << object << "\n";
}

void Debug::logError(const int object)
{
	std::cerr << "ERROR: " << object << "\n";
}

void Debug::logError(const float object)
{
	std::cerr << "ERROR: " << object << "\n";
}

void Debug::logError(const glm::vec2 object)
{
	std::cerr << "ERROR: (" << object.x << ", " << object.y << ")\n";
}

void Debug::logError(const glm::vec3 object)
{
	std::cerr << "ERROR: (" << object.x << ", " << object.y << ", " << object.z << ")\n";
}
