#pragma once

#include <cstdint>
#include <string>
#include <any>

#include <glad/glad.h>

#include <Engine/BaseClass.h>

namespace eng
{

	class Uniform : public BaseClass
	{
	public:
		Uniform(const std::string& name, const std::any& value);
		Uniform() = default;

	private:
		// Identyfikator uniformu.
		std::uint32_t m_Id = 0;

		// Nazwa uniformu.
		std::string m_Name = "";

		// Wartość uniformu.
		std::any m_Value = {};
	};

}