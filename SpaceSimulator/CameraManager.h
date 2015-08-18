#pragma once
#include <glm\glm.hpp>
#include <GL\glut.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace Managers
{
	class CameraManager
	{
	public:
		// CONSTRUCTORS
		static CameraManager* getInstance(); // Singleton
		
		// GETTERS
		glm::mat4 getViewMatrix();
		glm::vec3 getCameraPosition();
		glm::vec3 getCameraTarget();
		glm::vec3 getCameraUp();

		// SETTERS
		void setCameraPosition(const glm::vec3&);
		void setCameraTarget(const glm::vec3&);
		void setCameraUp(const glm::vec3&);

		// METHODS
		void rotatate(int x, int y);
		void rotatateX(int x);
		void rotatateY(int y);
		void panRight(int left);
		void panUp(int up);
		void moveForward(int forward);
		glm::mat4 LookAt(glm::vec3& position, //camera position (eye)
			glm::vec3& target,  //camera target
			glm::vec3& up); // ?related to viewing angle?

	private:
		// CONTRUCTORS
		CameraManager();
		CameraManager(const CameraManager&);

		// VARIABLES
		glm::vec3 cameraPosition; 
		glm::vec3 cameraTarget; 
		glm::vec3 cameraUp;
		static CameraManager* instance;

		// METHODS
		CameraManager& operator=(const CameraManager&);
	};
}