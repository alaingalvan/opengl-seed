/**
 * Raw OpenGL - Hello Triangle Example
 * Author: Alain Galvan (hi@alain.xyz)
 *
 * Note: to run this you'll need to follow the instructions in the "Setup" section
 * of https://alain.xyz/blog/raw-opengl
 */
#define GL_SILENCE_DEPRECATION

#include "CrossWindow/CrossWindow.h"
#ifndef __EMSCRIPTEN__
#include "glad/glad.h"
#endif
#include "CrossWindow/Graphics.h"

#include <iostream>

#include "Triangle.h"

void xmain(int argc, const char** argv)
{
	// 🖼 Create Window
	xwin::WindowDesc wdesc;
	wdesc.title = "OpenGL Seed";
	wdesc.name = "MainWindow";
	wdesc.visible = true;
	wdesc.width = 640;
	wdesc.height = 640;
	wdesc.fullscreen = false;

	xwin::Window window;
	xwin::EventQueue eventQueue;

	if (!window.create(wdesc, eventQueue))
	{ return; };

	// ⚪ Load OpenGL
	xgfx::OpenGLDesc desc;
	xgfx::OpenGLState oglState = xgfx::createContext(&window, desc);
	xgfx::setContext(oglState);
	if (!loadOpenGL())
	{ return; }

	// 🌟 Create Triangle
	if (!createTriangle())
	{ return; }

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

			// ❌ On Close:
			if (event.type == xwin::EventType::Close)
			{
				window.close();
				shouldRender = false;
				isRunning = false;
			}

			eventQueue.pop();
		}

		// ✨ Update Visuals
		if (shouldRender)
		{
			// 🔁 Swap back buffers so we can write to the next frame buffer
			xgfx::swapBuffers(oglState);
			drawTriangle(wdesc.width, wdesc.height);
		}
	}

	// ❌ Destroy OpenGL Data Structures
	destroyTriangle();
	xgfx::destroyContext(oglState);
}
