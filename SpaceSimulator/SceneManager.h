#pragma once
#include "ShaderManager.h"
#include "IListener.h"
#include "ModelsManager.h"
#include <Windows.h>

#define FPS 40

/**
* SceneManager extends IListener
*/
namespace Managers
{
	class SceneManager : public Core::IListener
	{
	public:
		SceneManager();
		~SceneManager();

		virtual void notifyBeginFrame();
		virtual void notifyDisplayFrame();
		virtual void notifyEndFrame();
		virtual void notifyReshape(int width, int height, int previous_width, int previous_height);

		void setModelsManager(Managers::ModelsManager*& models_manager);
		CameraManager* getCamera();

	private:
		//Managers::ShaderManager* shader_manager;
		Managers::ModelsManager* models_manager;
		glm::mat4 projection_matrix;
		glm::mat4 view_matrix;
		bool drawn;
		long long lastDraw;
		long long drawTime;
		long long milliseconds_now();
		CameraManager* camera;
	};
}
