#include "TEventScheduler.h"
#include <iostream>
using namespace GraphicsEngine::EngineInterface;
using namespace std;

TEventScheduler::TEventScheduler()
{

}

void TEventScheduler::event1()
{
	cout << "event 1 fired\n";
}

void TEventScheduler::systemEvents()
{
	cout << "system event fired\n";
}