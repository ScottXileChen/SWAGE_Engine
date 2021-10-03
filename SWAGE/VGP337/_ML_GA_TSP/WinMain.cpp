#include <SWAGE/Inc/SWAGE.h>
#include "GameState.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SWAGE::MainApp().AddState<GameState>("GameState");
	SWAGE::MainApp().Run({ L"Hello Genetic Algorithm - TSP" });
	return 0;
}