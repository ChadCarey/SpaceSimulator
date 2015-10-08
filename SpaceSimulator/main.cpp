#pragma once
#include "Runnable.h"
#include "SpaceSimulator.h"
#include "EngineTest.h"
#include "EngineTest.h"
#include <iostream>

Runnable* getProgram()
{
	int program = 0;
	while (true)
	{
		std::cout << "1. Test\n"
			<< "2. Space Simulator\n";
		std::cout << "Which program do you want to use?: ";
		std::cin >> program;
		switch (program)
		{
		case 1:
			return new EngineTest();
		case 2:
			return new SpaceSimulator();
		}
	}
}

int main(int argc, char **argv)
{
	Runnable* program;
	program = getProgram();
	program->run();
	delete program;


	return 0;
}