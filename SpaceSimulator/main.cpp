#pragma once
#include "Runnable.h"
#include "EngineTest.h"

int main(int argc, char **argv)
{
	Runnable* program;
	program = new EngineTest();
	program->run();
	delete program;


	return 0;
}