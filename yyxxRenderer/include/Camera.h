#pragma once
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	glm::vec3 Pos;
	glm::vec3 Front;
	glm::vec3 Up;
	float Speed;

	float Yaw = 0.0f;
	float Pitch = 0.0f;
	float MouseSensitivity = 0.1f;
	float Zoom = 45.0f;

	Camera()
	{
		Pos = glm::vec3(0.0, 0.0, 0.0);
		Front = glm::vec3(0.0, 0.0, -1.0);
		Up = glm::vec3(0.0, 1.0, 0.0);
		Speed = 0.1f;
	}
	Camera(glm::vec3 cameraP,
		glm::vec3 cameraF,
		glm::vec3 cameraU,
		float cameraS)
	{
		Pos = cameraP;
		Front = cameraF;
		Up = cameraU;
		Speed = cameraS;
	}
	inline void goAhead()
	{
		Pos += Speed * Front;
	}
	inline void goBack()
	{
		Pos -= Speed * Front;
	}
	inline void goLeft()
	{
		Pos -= glm::normalize(glm::cross(Front, Up)) * Speed;
	}
	inline void goRight()
	{
		Pos += glm::normalize(glm::cross(Front, Up)) * Speed;
	}
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// update Front, Right and Up Vectors using the updated Euler angles
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
	}
	void ProcessMouseScroll(float yoffset)
	{
		Zoom -= (float)yoffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}
};