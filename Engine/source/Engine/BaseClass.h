#pragma once

namespace eng
{

	/// <summary>
	/// Klasa bazowa dla innych klas.
	/// </summary>
	class BaseClass
	{
	public:
		BaseClass() = default;

		/// <summary>
		/// Sprawdza, czy klasa jest prawidłowa.
		/// </summary>
		/// <returns>Czy klasa jest prawidłowa.</returns>
		inline bool IsValid() { return m_Valid; }

		/// <summary>
		/// Ustawia prawidłowość klasy.
		/// </summary>
		/// <param name="valid">Czy klasa ma być prawidłowa.</param>
		void SetValid(bool valid);

	private:
		/// <summary>
		/// Ta zmienna decyduje czy klasa jest prawidłowa.
		/// </summary>
		bool m_Valid = true;
	};

}