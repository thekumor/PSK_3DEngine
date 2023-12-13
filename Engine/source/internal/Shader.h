#pragma once

#include <glad/glad.h>
#include <cstdint>
#include <string>
#include <optional>

namespace eng
{

	// Shader który steruje rysowaniem obiektów.
	class Shader
	{
	public:
		Shader(GLenum type, const std::string& filePath);
		Shader() = default;
		~Shader();

		static std::string LoadFromFile(const std::string& filePath);

	private:
		// Typ, czyli albo shader werteksów albo fragmentów.
		GLenum m_Type = 0;

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