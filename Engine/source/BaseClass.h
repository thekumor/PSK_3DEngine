#pragma once

namespace eng
{

	class BaseClass
	{
	public:
		BaseClass() = default;

		// Checks if the class is valid.
		inline bool IsValid() { return m_Valid;}

		// Sets the class as valid or not.
		void SetValid(bool valid);

	private:
		bool m_Valid = true;
	};

}