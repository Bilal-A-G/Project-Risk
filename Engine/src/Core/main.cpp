#include "EntryPoint.h"

void main() 
{
	Start();

	while (App::isRunning)
	{
		Update();
	}
}