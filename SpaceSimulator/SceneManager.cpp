#include "SceneManager.h"
using namespace Managers;

SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);

	/*view_matrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f,
							0.0f, 0.0f, -1.0f, 0.0f,
							0.0f, 3.5f, 20.0f, 1.0f); // manipulate this to move the camera (glm::lookat is better than just this)
							*/
	lastDraw = 0.0;
	drawTime = 1000.0 / FPS;
	drawn = true;
	camera = CameraManager::getInstance();
}

SceneManager::~SceneManager() {}

void SceneManager::notifyBeginFrame()
{
	long long currentTime = milliseconds_now(); // GLITCH: jerky cube
	if ((currentTime - lastDraw) >= drawTime && drawn)
	{
		/*std::cout << "\nCurrentTime: " << currentTime
			<< "\nLastDraw: " << lastDraw
			<< "\nDrawTime: " << drawTime << std::endl;*/
		models_manager->Update();
		lastDraw = currentTime;
		drawn = false;
	}
}

void SceneManager::notifyDisplayFrame()
{
	if (!drawn)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		models_manager->Draw();
		models_manager->Draw(projection_matrix, view_matrix);
		drawn = true;
	}
}

void SceneManager::notifyEndFrame() {}

void SceneManager::notifyReshape(int width, int height, int previous_width, int previous_height)
{
	// aspect ratio
	float ar = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
	float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;

	projection_matrix = glm::perspective(angle, ar, near1, far1);
}

void SceneManager::setModelsManager(Managers::ModelsManager*& models_m)
{
	models_manager = models_m;
}

long long SceneManager::milliseconds_now() 
{
	static LARGE_INTEGER s_frequency;
	static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
	if (s_use_qpc) {
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return (1000LL * now.QuadPart) / s_frequency.QuadPart;
	}
	else {
		return GetTickCount();
	}
}

CameraManager* SceneManager::getCamera()
{
	return this->camera;
}