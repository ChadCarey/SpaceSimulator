#pragma once
#include "Runnable.h"
#include "SpaceSimulator.h"
#include "EngineTest.h"

int main(int argc, char **argv)
{
	Runnable* program;
	program = new SpaceSimulator();
	program->run();
	delete program;


	return 0;
}