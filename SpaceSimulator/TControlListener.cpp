#include "TControlListener.h"
#include <iostream>
using namespace GraphicsEngine::EngineInterface;
using namespace std;


TControlListener::TControlListener()
{

}

void TControlListener::mouseMoveCallback()
{
	cout << "Mouse moved\n";
}

void TControlListener::mouseDragCallback()
{
	cout << "mouse draged\n";
}

void TControlListener::keyboardPressCallback()
{
	cout << "keyboard press\n";
}

void TControlListener::keyboardReleaseCallback()
{
	cout << "keyboard release\n";
}