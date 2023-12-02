#include "Engine.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_TITLE "Test"

int main()
{
	eng::Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	engine.Run();
}