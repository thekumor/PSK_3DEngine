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

	/// <summary>
	/// Program który określa sposób rysowania obiektów.
	/// </summary>
	class Shader : public BaseClass
	{
	public:
		Shader(ShaderType type, const std::string& filePath);
		Shader() = default;
		~Shader();

		/// <summary>
		/// Ładuje kod z pliku.
		/// </summary>
		/// <param name="filePath">Ścieżka pliku</param>
		/// <returns>Kod z pliku, jeśli istnieje</returns>
		static std::optional<std::string> LoadFromFile(const std::string& filePath);

		/// <summary>
		/// Zwraca identyfikator shadera.
		/// </summary>
		/// <returns>Identyfikator shadera</returns>
		inline std::uint32_t GetId() const { return m_Id; }

		/// <summary>
		/// Ustawia program rodzicielski dla tego shadera.
		/// </summary>
		/// <param name="id">Identyfikator programu rodzicielskiego</param>
		void SetParentProgram(std::uint32_t id);

	private:
		/// <summary>
		/// Typ shadera.
		/// </summary>
		ShaderType m_Type = ShaderType::Invalid;

		/// <summary>
		/// Identyfikator shadera.
		/// </summary>
		std::uint32_t m_Id = 0;

		/// <summary>
		/// Identyfikator programu rodzicielskiego.
		/// </summary>
		std::uint32_t m_ProgramId = 0;

		/// <summary>
		/// Kod shadera.
		/// </summary>
		std::string m_Code = "";

		/// <summary>
		/// Ścieżka pliku z którego pobrano kod (jeżeli to zrobiono).
		/// </summary>
		std::optional<std::string> m_FilePath = {};
	};

	/// <summary>
	/// Program, czyli zbiór shaderów (w zasadzie vertex + fragment).
	/// </summary>
	class Program : public BaseClass
	{
	public:
		Program(const Shader& vertex, const Shader& fragment);
		Program(const std::string& folderPath);
		Program() = default;
		~Program();

		/// <summary>
		/// Zwraca Identyfikator programu.
		/// </summary>
		/// <returns>Identyfikator programu</returns>
		std::uint32_t GetId() const { return m_Id; }

		/// <summary>
		/// Przypina program do użycia.
		/// </summary>
		void Bind() const;

		/// <summary>
		/// Odpina program.
		/// </summary>
		void Unbind() const;

	private:
		/// <summary>
		/// Identyfikator programu.
		/// </summary>
		std::uint32_t m_Id = 0;

		/// <summary>
		/// Shader werteksów.
		/// </summary>
		Shader m_VertexShader;

		/// <summary>
		/// Shader fragmentów.
		/// </summary>
		Shader m_FragmentShader;

		/// <summary>
		/// Ścieżka folderu z którego pobrano kod shaderów (jeżeli to zrobiono).
		/// </summary>
		std::optional<std::string> m_FolderPath = {};
	};

}