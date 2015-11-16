#pragma once
#include "ISceneListener.h"
#include "Planet.h"
#include "Skybox.h"
#include "PlanetManager.h"

class SpaceListener : public GraphicsEngine::EngineInterface::ISceneListener
{
public:
	SpaceListener();
	~SpaceListener();

	virtual void beginFrameCallback() override;
	virtual void drawFrameCallback() override;
	virtual void endFrameCallback() override;
	virtual bool closeCallback() override;
	virtual void windowReshapeCallback(int width, int height, int previousWidth, int previousHeight) override;

	virtual void mouseMoveCallback(int x, int y, int centerX, int centerY) override;
	virtual void mouseDragCallback(int x, int y, int centerX, int centerY) override;
	virtual void mouseClickCallback(int a, int b, int c, int d) override;
	virtual void keyboardPressCallback(const unsigned char& letter, const int& a, const int& b) override;
	virtual void keyboardReleaseCallback(const unsigned char& letter, const int& a, const int& b) override;
private:
	PlanetManager solarSystem;
    Skybox* skybox;
	bool paused;
	void fire();
    void addMoons(Planet* p, int numMoons);
};