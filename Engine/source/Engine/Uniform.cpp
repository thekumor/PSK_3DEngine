#include "Uniform.h"

namespace eng
{

	Uniform::Uniform(const std::string& name, const Program& prog)
		: m_Name(name), m_Prog(prog)
	{
		m_Location = glGetUniformLocation(prog.GetId(), name.c_str());
	}

	void Uniform::SetFloat(float value)
	{
		m_Prog.Bind();

		m_Value = value;
		glUniform1f(m_Location, value);

		//m_Prog.Unbind();
	}

}