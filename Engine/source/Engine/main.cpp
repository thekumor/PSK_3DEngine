#include <Engine/Engine.h>

#define WINDOW_WIDTH 1360
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE "3D Engine"

int main()
{
	eng::Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	engine.Run();
}