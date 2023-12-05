#include "Renderer.h"

namespace eng
{

    Renderer* Renderer::Get()
    {
        static Renderer* instance = new Renderer();
        return instance;
    }

}