#include "../Includes/MathHelper.h"

float lerp(float a, float b, float t)
{
	return a * (1.0 - t) + (b * t);
}

glm::vec2 lerp(glm::vec2 a, glm::vec2 b, float t)
{
	return glm::vec2(lerp(a.x, b.x, t), lerp(a.y, b.y, t));
}

glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float t)
{
	return glm::vec3(lerp(a.x, b.x, t), lerp(a.y, b.y, t), lerp(a.z, b.z, t));
}

glm::vec4 lerp(glm::vec4 a, glm::vec4 b, float t)
{
	return glm::vec4(lerp(a.x, b.x, t), lerp(a.y, b.y, t), lerp(a.z, b.z, t), lerp(a.w, b.w, t));
}

float linear(float x)
{
	return x;
}

float easeInQuad(float x)
{
	return x * x;
}

float easeOutQuad(float x)
{
	return 1 - (1 - x) * (1 - x);
}

float easeInOutQuad(float x)
{
	return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2;
}

float easeSin(float x)
{
	float result = sin(x * M_PI);
	if (result < 0.0f)
		result = 0.0f;
	return result;
}

float easeOutBack(float x)
{
	const float c1 = 1.70158;
	const float c3 = c1 + 1;

	return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
}

float easeOutBounce(float x)
{

	const float n1 = 7.5625;
	const float d1 = 2.75;

	if (x < 1 / d1)
	{
		return n1 * x * x;
	}
	else if (x < 2 / d1)
	{
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	}
	else if (x < 2.5 / d1)
	{
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	}
	else
	{
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
}

float easeInBounce(float x)
{
	return 1 - easeOutBounce(1 - x);
}

float easeInOutBounce(float x)
{
	return x < 0.5
		? (1 - easeOutBounce(1 - 2 * x)) / 2
		: (1 + easeOutBounce(2 * x - 1)) / 2;
}

float easeInElastic(float x)
{
	const float c4 = (2 * M_PI) / 3;

	return x = 0
		? 0
		: x = 1
		? 1
		: -pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4);
}

float easeInOutCirc(float x)
{
	return x < 0.5
		? (1 - sqrt(1 - pow(2 * x, 2))) / 2
		: (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
}

float shake(float x)
{
	float result = sin(x * M_PI) * abs(sin(x * M_PI * 5.0f));
	if (result < 0.0f)
		result = 0.0f;
	return result;
}

float jump(float x)
{
	return abs(sin(x * M_PI * 2));
}
