#include <SWAGE/Inc/SWAGE.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	SWAGE::Core::Window window;
	window.Initialize(hInstance, L"Hello Window", 1280, 720);

	bool running = true;
	while (running && window.IsActive())
	{
		window.ProcessMessage();
		if (!window.IsActive())
			continue;

		if (GetAsyncKeyState(VK_ESCAPE))
			running = false;
	}

	window.Terminate();
	return 0;
}