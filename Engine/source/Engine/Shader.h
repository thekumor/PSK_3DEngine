#pragma once

#include <cstdint>
#include <string>
#include <optional>
#include <iostream>
#include <fstream>

#include <glad/glad.h>

#include <Engine/BaseClass.h>

namespace eng
{

	enum class ShaderType : std::uint32_t
	{
		Invalid = 0,
		Vertex = 1,
		Fragment = 2
	};

	// Shader który steruje rysowaniem obiektów.
	class Shader : public BaseClass
	{
	public:
		Shader(ShaderType type, const std::string& filePath);
		Shader() = default;
		~Shader();

		// Ładuje kod z pliku.
		static std::optional<std::string> LoadFromFile(const std::string& filePath);

		// Zwraca identyfikator shadera.
		inline std::uint32_t GetId() const { return m_Id; }

		// Ustawia identyfikator programu tego shadera.
		void SetParentProgram(std::uint32_t id);

	private:
		// Typ, czyli albo shader werteksów albo fragmentów.
		ShaderType m_Type = ShaderType::Invalid;

		// Identyfikator shadera.
		std::uint32_t m_Id = 0;

		// Identyfikator programu.
		std::uint32_t m_ProgramId = 0;

		// Kod shadera.
		std::string m_Code = "";

		// Ścieżka do pliku shadera (jeżeli pobrane z niego).
		std::optional<std::string> m_FilePath = {};
	};

	// Zbiór dwóch shaderów (vertex + fragment).
	class Program : public BaseClass
	{
	public:
		Program(const Shader& vertex, const Shader& fragment);
		Program(const std::string& folderPath);
		Program() = default;
		~Program();

		// Binduje program do użycia.
		void Bind() const;

	private:
		// Identyfikator programu.
		std::uint32_t m_Id = 0;

		// Shader od werteksów.
		Shader m_VertexShader;

		// Shader od fragmentów.
		Shader m_FragmentShader;

		// Ścieżka do folderu shaderów (jeżeli pobrane z niego).
		std::optional<std::string> m_FolderPath = {};
	};

}