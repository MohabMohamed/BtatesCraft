#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "GL/glfw3.h"



class Camera
{
private:
	glm::vec3 Position, Front, Up,Right;
	float Speed = 5, Sensitivity = 0.05;
	GLFWwindow * window;
	double lastX = 250, lastY = 250, Yaw=45, Pitch=45;
	bool firstMouseMovment;
public:
		 Camera(GLFWwindow*);
		 ~Camera();
	void Input(float deltaTime);
	glm::mat4 GetViewMat();
private:
	void KeyboardInput(float deltaTime);
	void MouseInput(float deltaTime);




};



