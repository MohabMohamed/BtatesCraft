#include "BlockPicker.h"
#include "Camera.h"

BlockPicker::BlockPicker(GLFWwindow* window, Camera * camera, glm::mat4& Proj)
	:window(window), CurCamera(camera),Proj(Proj)
{
	View = camera->GetViewMat();
}

glm::vec3 BlockPicker::GetRay()
{
	return Ray;
}

void BlockPicker::Update()
{
	View = CurCamera->GetViewMat();
	CalculateRay();
}

void BlockPicker::CalculateRay()
{
	double xMouse, yMouse;
	glfwGetCursorPos(window, &xMouse, &yMouse);
	glm::vec2 NormCoord = GetNormDeviceCoord(xMouse, yMouse);
	glm::vec4 ClipCoord = glm::vec4(NormCoord, -1.0f, 1.0f);
	glm::vec4 EyeCoord =  GetEyeCoord(ClipCoord);
	Ray = glm::normalize(GetWorldCoord(EyeCoord));
}

glm::vec2 BlockPicker::GetNormDeviceCoord(float xMouse, float yMouse)
{
	int hight, width;
	glfwGetWindowSize(window, &width, &hight);
	float x = 2.0f* xMouse / width -1.0f;
	float y = 2.0f* yMouse / hight - 1.0f;


	return glm::vec2(x,-1*y);
}

glm::vec4 BlockPicker::GetEyeCoord(glm::vec4& ClipCoord)
{
	glm::vec4 EyeCooerd = glm::inverse(Proj) *ClipCoord ;
	EyeCooerd.z = -1.0f;
	EyeCooerd.w = 0.0f;
	return EyeCooerd;
}

glm::vec3 BlockPicker::GetWorldCoord(glm::vec4 & EyeCoord)
{
	glm::vec4 WorldCoord = glm::inverse(View)*EyeCoord ;

	return glm::vec3(WorldCoord.x, WorldCoord.y, WorldCoord.z);
}



