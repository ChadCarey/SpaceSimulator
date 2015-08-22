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
		void rotateLeft(float left);
		inline void rotateRight(float right);

		void look(int dx, int dy);

		void lookUp(float value);
		inline void lookDown(float value);

		void lookLeft(float value);
		inline void lookRight(float value);
		
		void panRight(float right);
		inline void panLeft(float left) { panRight(-left); }

		void moveForward(float forward);
		inline void moveBackward(float backward) { moveForward(-backward); }

		void panUp(float up);
		inline void panDown(float down);

		glm::mat4 LookAt(glm::vec3& position, //camera position (eye)
			glm::vec3& target,  //camera target
			glm::vec3& up) const; // ?related to viewing angle?

	private:
		// VARIABLES
		glm::vec3 cameraPosition;
		glm::vec3 cameraTarget; 
		glm::vec3 cameraUp;

		int angleX;
		int angleY;
	};
}