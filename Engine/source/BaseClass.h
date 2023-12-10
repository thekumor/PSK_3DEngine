#pragma once

namespace eng
{

	class BaseClass
	{
	public:
		BaseClass() = default;

		// Sprawdza czy klasa jest prawidłowa.
		inline bool IsValid() { return m_Valid;}

		// Ustawia czy klasa jest prawidłowa.
		void SetValid(bool valid);

	private:
		// Za pomocą tej zmiennej można ustawić prawidłowość klasy.
		bool m_Valid = true;
	};

}