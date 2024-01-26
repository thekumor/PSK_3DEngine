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

	/// <summary>
	/// Technologiczne demo.
	/// </summary>
	class Demo : public BaseClass, public EventInteractive
	{
	public:
		Demo() = default;

		/// <summary>
		/// Tworzy demo i je uruchamia.
		/// </summary>
		/// <param name="engine">Silnik dla dema</param>
		void Run(Engine& engine);
	private:
		bool m_LightingEnabled;
	};

}