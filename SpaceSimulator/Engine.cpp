#include "Engine.h"
using namespace BasicEngine;
using namespace Core;

Engine::Engine()
{

}

//You can set params for init
bool Engine::Init()
{
	WindowInfo window(std::string("in2gpu OpenGL Chapter 2 tutorial"), 400, 200, 800, 600, true);
	ContextInfo context(4, 2, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);

	Init_GLUT::init(window, context, frameBufferInfo);
	
	m_scene_manager = new Managers::SceneManager();
	
	IListener* ptr = m_scene_manager;
	Init_GLUT::setListener(ptr);
	
	m_shader_manager = new Managers::ShaderManager();
	m_shader_manager->createProgram("colorShader",
									"Vertex_Shader.glsl",
									"Fragment_Shader.glsl");

	m_texture_loader = new TextureLoader();
	
	if (m_scene_manager && m_shader_manager)
	{
		m_models_manager = new Managers::ModelsManager();
		m_scene_manager->setModelsManager(m_models_manager);
	}
	else
	{
		return false;
	}

	return true;
}

//Create the loop
void Engine::Run()
{
	Init_GLUT::run();
}


Managers::SceneManager* Engine::GetScene_Manager() const
{
	return m_scene_manager;
}

Managers::ShaderManager* Engine::GetShader_Manager() const
{
	return m_shader_manager;
}

Managers::ModelsManager* Engine::GetModels_Manager() const
{
	return m_models_manager;
}

Managers::CameraManager* Engine::GetCamera_Manager() const
{
	return GetScene_Manager()->getCamera();
}

TextureLoader* Engine::GetTexture_Loader() const
{
	return m_texture_loader;
}

Engine::~Engine()
{
	if (m_scene_manager)
		delete m_scene_manager;

	if (m_shader_manager)
		delete m_shader_manager;

	if (m_models_manager)
		delete m_models_manager;

	if (m_texture_loader)
		delete m_texture_loader;
}