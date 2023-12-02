#pragma once

#include <iostream>

namespace eng
{

	namespace showcase
	{

		// Class that can run a demo showcase.
		class Demo
		{
		public:
			Demo() = default;

			// Creates elements and runs the demo.
			void Run();
		};

	}

}