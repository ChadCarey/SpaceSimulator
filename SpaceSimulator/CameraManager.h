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

		// SETTERS
		void setCameraPosition(const glm::vec3&);

		// METHODS

		void look(int dx, int dy);

		void lookUp(float value);
		inline void lookDown(float value) { lookUp(-value); };

		void lookRight(float value);
		inline void lookLeft(float value) { lookRight(-value); };
		
		void panRight(float right);
		inline void panLeft(float left) { panRight(-left); }

		void panUp(float up);
		inline void panDown(float down) { panUp(-down); };

		void moveForward(float forward);
		inline void moveBackward(float backward) { moveForward(-backward); }

		glm::mat4 LookAt(glm::vec3& position, //camera position (eye)
			glm::vec3& target,  //camera target
			glm::vec3& up) const; // ?related to viewing angle?

	private:
		// VARIABLES
		glm::vec3 cameraPosition;
		glm::vec3 cameraUp;
		glm::vec3 forwardVector;
		glm::vec3 upVector;

		// GETTERS
		glm::vec3 getCameraUp() const;

		glm::vec3 getForwardVector() const;
		glm::vec3 getRightVector() const;
		glm::vec3 getUpVector() const;

		// SETTERS
		void setCameraUp(const glm::vec3&);

		void setForwardVector(const glm::vec3&);
		void setUpVector(const glm::vec3&);

		// FUNCTIONS
		void correctUp();
	};
}