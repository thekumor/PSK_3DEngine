#include <Engine/Engine.h>
#include <Engine/globals.h>

// Zmienna globalna.
eng::EventSource eng::g_EventSource = {};

#define WINDOW_WIDTH 1360
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE "3D Engine"

int main()
{
	eng::Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	engine.Run();
}