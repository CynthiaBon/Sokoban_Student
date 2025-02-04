#pragma once

#include "MonoBehaviour.h"
#include "Shader.h"

/*
	Keywords :
	- inheritance 
	- static
	- view matrix
*/

class Camera : public MonoBehaviour
{
public:
	Camera(GameObject* game_object);
	~Camera();

	static Camera* getMain();
	void setMain();
	
private:
	static void updateViewMatrix(const Transform* camera_transform);

private:
	static Camera* m_main;
};