#pragma once

#include <cstdint>
#include <string>
#include <any>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <Engine/BaseClass.h>
#include <Engine/Shader.h>

namespace eng
{

	// Uniform - dodatkowa wartość dla shaderów.
	class Uniform : public BaseClass
	{
	public:
		Uniform(const std::string& name, const Program& prog);
		Uniform() = default;

		// Ustawia wartość uniformu jako float.
		void SetFloat(float value);

		// Ustawia wartość uniformu jako 4-floatowy wektor.
		void SetVec4f(const glm::fvec4& value);

		// Ustawia wartość uniformu jako 4-doublowy wektor.
		void SetVec4d(const glm::dvec4& value);

	private:
		// Shadery które posiadają ten uniform.
		// UWAGA: to jest kopia, nie oryginał.
		Program m_Prog;

		// Lokalizacja uniformu w shaderze.
		std::uint32_t m_Location = 0;

		// Nazwa uniformu.
		std::string m_Name = "";

		// Wartość uniformu.
		std::any m_Value = {};
	};

}