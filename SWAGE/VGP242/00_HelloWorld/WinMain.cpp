#include <Core/Inc/Core.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	LOG("Hello, I am %s", "Scott");
	Sleep(1000);
	LOG("%d seconds have passed and I am still fine.", 1);

	int n = 42;
	ASSERT(n == 2, "42 is not 7.");

	return 0;
}