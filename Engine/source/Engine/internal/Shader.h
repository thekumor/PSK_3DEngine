#pragma once

#include <cstdint>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <Engine/BaseClass.h>

namespace eng
{

	// Shader który steruje rysowaniem obiektów.
	class Shader : public BaseClass
	{
	public:
		Shader(std::uint32_t type, const std::string& filePath);
		Shader() = default;
		~Shader();

		static std::string LoadFromFile(const std::string& filePath);

	private:
		// Typ, czyli albo shader werteksów albo fragmentów.
		std::uint32_t m_Type = 0;

		// Identyfikator shadera.
		std::uint32_t m_Id = 0;

		// Kod shadera.
		std::string m_Code = "";

		// Œcie¿ka do pliku shadera (jeœli pobrane z niego).
		std::optional<std::string> m_FilePath;
	};

	// Zbiór dwóch shaderów (vertex + fragment).
	class Program
	{
	public:
		Program(const Shader& vertex, const Shader& fragment);
		Program() = default;
		~Program();

	private:
		// Identyfikator programu.
		std::uint32_t m_Id = 0;

		// Shader od werteksów.
		Shader m_VertexShader;

		// Shader od fragmentów.
		Shader m_FragmentShader;
	};

}