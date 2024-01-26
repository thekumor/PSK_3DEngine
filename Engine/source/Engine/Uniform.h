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

	/// <summary>
	/// Wartość własna dla shaderów.
	/// </summary>
	class Uniform : public BaseClass
	{
	public:
		Uniform(const std::string& name, const Program& prog);
		Uniform() = default;

		/// <summary>
		/// Ustawia wartość uniformu w formacie float.
		/// </summary>
		/// <param name="value">Wartość uniformu</param>
		void SetFloat(float value);

		/// <summary>
		/// Ustawia wartość uniformu w formacie wektora 4-elementowego float.
		/// </summary>
		/// <param name="value">Wartość uniformu</param>
		void SetVec4f(const glm::fvec4& value);

		/// <summary>
		/// Ustawia wartość uniformu w formacie wektora 4-elementowego double.
		/// </summary>
		/// <param name="value">Wartość uniformu</param>
		void SetVec4d(const glm::dvec4& value);

		/// <summary>
		/// Ustawia wartość uniformu w formacie int.
		/// </summary>
		/// <param name="value">Wartość uniformu</param>
		void SetInt(int value);

	private:
		/// <summary>
		/// Program do którego uniform jest przypięty.
		/// UWAGA: To jest kopia!
		/// </summary>
		Program m_Prog;

		/// <summary>
		/// Identyfikacja (lokalizacja) uniformu.
		/// </summary>
		std::uint32_t m_Location = 0;

		/// <summary>
		/// Nazwa dla uniformu.
		/// </summary>
		std::string m_Name = "";

		/// <summary>
		/// Wartość uniformu.
		/// </summary>
		std::any m_Value = {};
	};

}