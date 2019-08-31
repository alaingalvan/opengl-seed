#include "CrossWindow/Main/Main.h"
#include "CrossWindow/CrossWindow.h"
#include "glad/glad.h"
#include "CrossWindow/Graphics.h"
#include "glm/glm.hpp"


void xmain(int argc, const char** argv)
{
	// Configure our Window
	xwin::WindowDesc wdesc;
	wdesc.title = "OpenGL Seed";
	wdesc.name = "MainWindow";
	wdesc.visible = true;
	wdesc.width = 1280;
	wdesc.height = 720;
	wdesc.fullscreen = false;

	xwin::Window window;
	xwin::EventQueue eventQueue;

	if (!window.create(wdesc, eventQueue))
	{
		return;
	};

	// 🏁 Engine loop
	bool isRunning = true;
	while (isRunning)
	{
		bool shouldRender = true;

		// ♻️ Update the event queue
		eventQueue.update();

		// 🎈 Iterate through that queue:
		while (!eventQueue.empty())
		{
			//Update Events
			const xwin::Event& event = eventQueue.front();

			if (event.type == xwin::EventType::Close)
			{
				window.close();
				shouldRender = false;
				isRunning = false;
			}

			eventQueue.pop();
		}
	}
}