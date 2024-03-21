#include <Window/Window.h>
#include <Renderer/Renderer.h>

int main()
{
	Window* basicWindow = new Window({ 1280, 720 }, "D3D Window");
	
	basicWindow->Initialize();

	Renderer* basicRenderer = new Renderer(basicWindow);

	while (basicWindow->isVisible())
	{
		basicWindow->Run();
		basicRenderer->ClearColor({ 0.6f, 0.0f, 0.2f, 0.3f });
		basicRenderer->Present();
	}

	delete basicWindow;
	delete basicRenderer;
	return 0;
}