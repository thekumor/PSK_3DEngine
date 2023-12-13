#include "Shader.h"

namespace eng
{
    
    Shader::Shader(GLenum type, const std::string& filePath)
    {
    }

    Shader::~Shader()
    {
    }

    std::string Shader::LoadFromFile(const std::string& filePath)
    {
        return std::string();
    }

	Program::Program(const Shader& vertex, const Shader& fragment)
	{

	}

	Program::~Program()
	{

	}

}