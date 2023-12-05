#pragma once

namespace eng
{

	// Used to render objects. Singleton.
	class Renderer
	{
	public:
		Renderer(const Renderer&) = delete;
		Renderer& operator=(Renderer&) = delete;

		// Gets the singleton instance.
		static Renderer* Get();
	private:
		Renderer() = default;
	};

}