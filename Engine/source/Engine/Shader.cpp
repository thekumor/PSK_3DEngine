#include "Shader.h"

namespace eng
{

	Shader::Shader(ShaderType type, const std::string& filePath)
		: m_Type(type), m_FilePath(filePath)
	{
		m_Id = glCreateShader(type == ShaderType::Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

		std::optional<std::string> code = Shader::LoadFromFile(filePath);
		if (code)
		{
			const char* src = code->c_str();
			glShaderSource(m_Id, 1, &src, nullptr);
			glCompileShader(m_Id);

			std::int32_t result = 0;
			glGetShaderiv(m_Id, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				std::int32_t length = 0;
				glGetShaderiv(m_Id, GL_INFO_LOG_LENGTH, &length);

				char* msg = reinterpret_cast<char*>(alloca(sizeof(char) * length));
				glGetShaderInfoLog(m_Id, length, &length, msg);
				std::cout << "Failed to compile shader! Type: " << (type == ShaderType::Vertex ? "vertex" : "fragment") << std::endl;
				std::cout << "Message: " << msg << std::endl;

				glDeleteShader(m_Id);
				SetValid(false);
			}
		}
	}

	Shader::~Shader()
	{
		if (m_ProgramId != 0)
			glDetachShader(m_Id, m_ProgramId);
	}

	std::optional<std::string> Shader::LoadFromFile(const std::string& filePath)
	{
		std::ifstream file(filePath);
		if (file)
		{
			std::string code = "";
			std::string line = "";

			while (std::getline(file, line))
				code += line + "\n";

			file.close();

			return code;
		}
		else
		{
			std::cout << "Failed to load shader " << filePath << "!" << std::endl;
			return {};
		}
	}

	void Shader::SetParentProgram(std::uint32_t id)
	{
		m_ProgramId = id;
	}

	Program::Program(const Shader& vertex, const Shader& fragment)
		: m_VertexShader(vertex), m_FragmentShader(fragment)
	{
		m_Id = glCreateProgram();
		glAttachShader(m_Id, vertex.GetId());
		glAttachShader(m_Id, fragment.GetId());
		glLinkProgram(m_Id);
		glValidateProgram(m_Id);

		glDeleteShader(vertex.GetId());
		glDeleteShader(fragment.GetId());
		m_VertexShader.SetParentProgram(m_Id);
		m_VertexShader.SetValid(false);
		m_FragmentShader.SetParentProgram(m_Id);
		m_FragmentShader.SetValid(false);
	}

	Program::Program(const std::string& folderPath)
		: m_VertexShader(ShaderType::Vertex, folderPath + "/" + "vertex.glsl"),
		m_FragmentShader(ShaderType::Fragment, folderPath + "/" + "fragment.glsl"),
		m_FolderPath(folderPath)
	{
		m_Id = glCreateProgram();
		glAttachShader(m_Id, m_VertexShader.GetId());
		glAttachShader(m_Id, m_FragmentShader.GetId());
		glLinkProgram(m_Id);
		glValidateProgram(m_Id);

		glDeleteShader(m_VertexShader.GetId());
		glDeleteShader(m_FragmentShader.GetId());
		m_VertexShader.SetParentProgram(m_Id);
		m_VertexShader.SetValid(false);
		m_FragmentShader.SetParentProgram(m_Id);
		m_FragmentShader.SetValid(false);
	}

	Program::~Program()
	{
		glDeleteProgram(m_Id);
	}

	void Program::Bind() const
	{
		glUseProgram(m_Id);
	}

	void Program::Unbind() const
	{
		glUseProgram(0);
	}

}