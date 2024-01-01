#pragma once

#include <iostream>

#include <glm/glm.hpp>

#include <Engine/objects.h>
#include <Engine/Uniform.h>
#include <Engine/Shader.h>
#include <Engine/Engine.h>
#include <Engine/globals.h>
#include <Engine/BaseClass.h>

namespace eng::showcase
{

	// Demo technologiczne.
	class Demo : public BaseClass
	{
	public:
		Demo() = default;

		// Tworzy elementy demo i uruchamia je.
		void Run(Engine& engine);
	};

}