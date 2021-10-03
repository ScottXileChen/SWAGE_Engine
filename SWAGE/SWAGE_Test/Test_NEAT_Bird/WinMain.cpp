#include <SWAGE/Inc/SWAGE.h>
#include "GameState.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SWAGE::AppConfig config;
	config.appName = L"Neat BIRD";
	config.windowHeight = 853;
	config.windowWidth = 480;
	SWAGE::MainApp().AddState<GameState>("GameState");
	SWAGE::MainApp().Run(config);
	return 0;
}