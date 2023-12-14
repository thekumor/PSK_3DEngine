#pragma once

#include <iostream>
#include "BaseClass.h"

namespace eng
{

	namespace showcase
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

}