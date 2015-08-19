#pragma once

/**
*
* This is an interface to allow me to choose what program I want to run from main. This may include various tests.
*/

class Runnable
{
public:
	virtual void run() = 0;
};