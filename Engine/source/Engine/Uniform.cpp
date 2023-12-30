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

	void Uniform::SetVec4f(const glm::fvec4& value)
	{
		m_Prog.Bind();

		m_Value = value;
		glUniform4f(m_Location, value.x, value.y, value.z, value.w);
	}

	void Uniform::SetVec4d(const glm::dvec4& value)
	{
		m_Prog.Bind();

		m_Value = value;
		glUniform4d(m_Location, value.x, value.y, value.z, value.w);
	}

}