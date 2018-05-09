#pragma once
#include <memory>
#include "glm/glm.hpp"
#include "GL/glfw3.h"
class Camera;

class BlockPicker 
{
private :
	glm::vec3 Ray;
	Camera* CurCamera;
	glm::mat4 View,Proj;
	GLFWwindow* window;
public:
	BlockPicker(GLFWwindow* window,Camera* camera,glm::mat4& Proj);
	glm::vec3 GetRay();
	void Update();
private:
	void CalculateRay();
	glm::vec2 GetNormDeviceCoord(float xMouse,float yMouse);
	glm::vec4 GetEyeCoord(glm::vec4& ClipCoord);
	glm::vec3 GetWorldCoord(glm::vec4& EyeCoord);
};
