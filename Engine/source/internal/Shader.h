#pragma once

#include <glad/glad.h>
#include <cstdint>
#include <string>
#include <optional>

namespace eng
{

	// Shader kt�ry steruje rysowaniem obiekt�w.
	class Shader
	{
	public:
		Shader(GLenum type, const std::string& filePath);
		Shader() = default;
		~Shader();

		static std::string LoadFromFile(const std::string& filePath);

	private:
		// Typ, czyli albo shader werteks�w albo fragment�w.
		GLenum m_Type = 0;

		// Identyfikator shadera.
		std::uint32_t m_Id = 0;

		// Kod shadera.
		std::string m_Code = "";

		// �cie�ka do pliku shadera (je�li pobrane z niego).
		std::optional<std::string> m_FilePath;
	};

	// Zbi�r dw�ch shader�w (vertex + fragment).
	class Program
	{
	public:
		Program(const Shader& vertex, const Shader& fragment);
		Program() = default;
		~Program();

	private:
		// Identyfikator programu.
		std::uint32_t m_Id = 0;

		// Shader od werteks�w.
		Shader m_VertexShader;

		// Shader od fragment�w.
		Shader m_FragmentShader;
	};

}