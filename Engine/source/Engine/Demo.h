#pragma once

#include <iostream>
#include <Engine/BaseClass.h>

namespace eng::showcase
{

	// Demo technologiczne.
	class Demo : public BaseClass
	{
	public:
		Demo() = default;

		// Tworzy elementy demo i uruchamia je.
		void Run();
	};

}