#pragma once

#include "libs.h"

/*
	Keywords :
	- static
	- function overloading
	- standard streams
*/

class Debug
{
public:
	static void log(const char object);
	static void log(const std::string object);
	static void log(const int object);
	static void log(const float object);
	static void log(const glm::vec2 object);
	static void log(const glm::vec3 object);
	static void logError(const char object);
	static void logError(const std::string object);
	static void logError(const int object);
	static void logError(const float object);
	static void logError(const glm::vec2 object);
	static void logError(const glm::vec3 object);
};
