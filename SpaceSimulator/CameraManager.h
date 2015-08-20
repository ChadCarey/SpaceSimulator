#pragma once
#include "glm\glm.hpp"
#include "GL\freeglut.h"
#include "glm\gtc\matrix_transform.hpp"
#include <iostream>

namespace Managers
{
	class CameraManager
	{
	public:
		// CONSTRUCTORS
		CameraManager();
		CameraManager(const CameraManager&);

		// GETTERS
		glm::mat4 getViewMatrix() const;
		glm::vec3 getCameraPosition() const;
		glm::vec3 getCameraTarget() const;
		glm::vec3 getCameraUp() const;

		// SETTERS
		void setCameraPosition(const glm::vec3&);
		void setCameraTarget(const glm::vec3&);
		void setCameraUp(const glm::vec3&);

		// METHODS
		void rotateLeft(int left);
		inline void rotateRight(int right);

		void lookUp(int value);
		inline void lookDown(int value);

		void lookLeft(int value);
		inline void lookRight(int value);
		
		void panRight(int right);
		inline void panLeft(int left);

		void panUp(int up);
		inline void panDown(int down);

		void moveForward(int forward);
		inline void moveBackward(int backward);

		glm::mat4 LookAt(glm::vec3& position, //camera position (eye)
			glm::vec3& target,  //camera target
			glm::vec3& up) const; // ?related to viewing angle?

	private:
		// VARIABLES
		glm::vec3 cameraPosition;
		glm::vec3 cameraTarget; 
		glm::vec3 cameraUp;
	};
}