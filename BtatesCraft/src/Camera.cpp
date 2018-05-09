#include "Camera.h"
#include <iostream>

Camera::Camera(GLFWwindow* Window)
:window(Window)
{
	Position = glm::vec3(0.0f, 18.0f, 0.0f);
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Camera::~Camera()
{
}

void Camera::Input(float deltaTime)
{
	KeyboardInput(deltaTime);
	MouseInput(deltaTime);
	Right = glm::normalize(glm::cross(Front, Up));
	UpdateViewMat();
}

void Camera::UpdateViewMat()
{
	View = glm::lookAt(Position, Position + Front, Up);
}

void Camera::KeyboardInput(float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Position += Speed*deltaTime * Front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Position -= Speed*deltaTime * Front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Position -= glm::normalize(glm::cross(Front, Up)) * Speed*deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Position += glm::normalize(glm::cross(Front, Up)) * Speed*deltaTime;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		Position+= Speed*deltaTime * Up;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		Position -= Speed*deltaTime * Up;
}

void Camera::MouseInput(float deltaTime)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (firstMouseMovment)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouseMovment = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; 

	lastX = xpos;
	lastY = ypos;


	xoffset *= Sensitivity;
	yoffset *= Sensitivity;

	Yaw += xoffset;
	Pitch += yoffset;


		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	
		if (Yaw > 360)
			Yaw = 0;
		if (Yaw < 0)
			Yaw = 360;

		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
}
