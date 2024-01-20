﻿//#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <Engine/Engine.h>
#include <Engine/globals.h>
#include <Engine/Demo.h>
#include <Engine/utility.h>

/// <summary>
/// Globalne źródło zdarzeń.
/// </summary>
eng::EventSource eng::g_EventSource = {};

#define WINDOW_WIDTH 1360
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE "3D Engine"

#define ENG_ENABLE_DEMO 1

int main()
{
	using namespace eng;

	Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	// Debugowanie
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	// Demo
	showcase::Demo demo;
	if (ENG_ENABLE_DEMO)
	{
		demo.Run(engine);
	}

	// Część właściwa.
	engine.Run();
}