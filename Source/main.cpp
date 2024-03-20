#include <Window/Window.h>


int main()
{
	Window* basicWindow = new Window({ 1280, 720 }, "D3D Window");

	basicWindow->Initialize();

	while (basicWindow->isVisible())
	{
		basicWindow->Run();
	}

	delete basicWindow;
	return 0;
}