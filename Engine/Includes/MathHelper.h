#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <glm.hpp>

float lerp(float a, float b, float t);
glm::vec2 lerp(glm::vec2 a, glm::vec2 b, float t);
glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float t);
glm::vec4 lerp(glm::vec4 a, glm::vec4 b, float t);
float linear(float x);
float easeInQuad(float x);
float easeOutQuad(float x);
float easeInOutQuad(float x);
float easeSin(float x);

float easeOutBack(float x);
float easeOutBounce(float x);
float easeInBounce(float x);
float easeInOutBounce(float x);
float easeInElastic(float x);
float easeInOutCirc(float x);

float shake(float x);
float jump(float x);