#pragma once

#include <string>
#include <vector>
#include <memory>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <Engine/internal/buffers.h>
#include <Engine/Renderer.h>
#include <Engine/events.h>

namespace eng
{

	/// <summary>
	/// Klasa bazowa obiektów.
	/// </summary>
	class BaseObject
	{
	public:
		BaseObject() = default;

		/// <summary>
		/// Zwraca odbiornik zdarzeń.
		/// </summary>
		/// <returns>Odbiornik zdarzeń</returns>
		EventReceiver& GetReceiver() { return m_Receiver; }

		/// <summary>
		/// Zwraca czy posiada teksture.
		/// </summary>
		/// <returns>Czy posiada teksture</returns>
		inline bool HasTexture() const { return m_HasTexture; }

		/// <summary>
		/// Ustawia, czy posiada teksture.
		/// </summary>
		/// <param name="has">Czy używać tekstury</param>
		void SetHasTexture(bool has);

	private:
		/// <summary>
		/// Odbiornik zdarzeń.
		/// </summary>
		EventReceiver m_Receiver;

		/// <summary>
		/// Czy posiada teksture.
		/// </summary>
		bool m_HasTexture = false;
	};

	class Texture : public BaseObject
	{
	public:
		/// <summary>
		/// Konstruktor tekstury z podaną ścieżką pliku.
		/// </summary>
		/// <param name="filePath">Ścieżka do pliku tekstury</param>
		Texture(const std::string& filePath);
		/// <summary>
		/// Domyślny konstruktor tekstury.
		/// </summary>
		Texture() = default;

	private:
		std::string m_Path = "";
		std::uint32_t m_Id = 0;
	};

	/// <summary>
	/// Trójkąt, z którego można składać prymitywy.
	/// </summary>
	class Triangle : public BaseObject
	{
	public:
		Triangle(const glm::mat3x4& positions, const glm::fvec4& color);
		Triangle(const glm::mat3x4& positions, const glm::fvec4& color, const glm::mat3x2& texCoords);
		Triangle(const Triangle& other);
		Triangle() = default;

		/// <summary>
		/// Zwraca bufor werteksów.
		/// </summary>
		/// <returns>Bufor werteksów</returns>
		inline const inter::VertexBuffer& GetVertexBuffer() const { return m_VertexBuffer; }

		/// <summary>
		/// Wylicza środek trójkąta.
		/// </summary>
		/// <returns>Środek trójkąta, punkt</returns>
		glm::fvec4 GetCenter() const;

		/// <summary>
		/// Rysuje ten trójkąt.
		/// </summary>
		/// <param name="renderer">Renderer który ma go narysować</param>
		void Draw(Renderer* renderer);

		/// <summary>
		/// Rotuje ten trójkąt.
		/// </summary>
		/// <param name="radians">Radiany</param>
		void Rotate(float radians);

		void Move(glm::fvec3 offset);

	private:
		/// <summary>
		/// Tablica werteksów.
		/// </summary>
		inter::VertexArray m_VertexArray;

		/// <summary>
		/// Bufor indeksów.
		/// </summary>
		inter::IndexBuffer m_IndexBuffer;

		/// <summary>
		/// Bufor werteksów.
		/// </summary>
		inter::VertexBuffer m_VertexBuffer;
	};

	class Rectangle : public BaseObject
	{
	public:
		Rectangle(const glm::mat3x4& left, const glm::mat3x4& right, const glm::fvec4& color);
		Rectangle(const glm::mat3x4& left, const glm::fvec4& color);
		Rectangle(const Rectangle& other);
		Rectangle() = default;

		/// <summary>
		/// Zwraca środek prostokąta.
		/// </summary>
		/// <returns>Środek prostokąta, punkt</returns>
		glm::fvec4 GetCenter() const;

		/// <summary>
		/// Rysuje prostokąt za pomocą podanego renderera.
		/// </summary>
		/// <param name="renderer">Renderer, który ma narysować prostokąt</param>
		void Draw(Renderer* renderer);

		/// <summary>
		/// Rotuje prostokąt o podany kąt (w radianach).
		/// </summary>
		/// <param name="radians">Kąt rotacji w radianach</param>
		void Rotate(float radians);

		/// <summary>
		/// Zwraca lewy trójkąt prostokąta.
		/// </summary>
		/// <returns>Referencja do lewego trójkąta</returns>
		inline Triangle& GetLeftTriangle() { return m_LeftTriangle; }

		/// <summary>
		/// Zwraca prawy trójkąt prostokąta.
		/// </summary>
		/// <returns>Referencja do prawego trójkąta</returns>
		inline Triangle& GetRightTriangle() { return m_RightTriangle; }

	private:
		Triangle m_LeftTriangle, m_RightTriangle;
	};

	class Cube : public BaseObject
	{
	public:
		Cube(const glm::vec4& position, float length);
		Cube() = default;

		/// <summary>
		/// Rysuje tą kostkę.
		/// </summary>
		/// <param name="renderer">Renderer który ma ją narysować</param>
		void Draw(Renderer* renderer);

	private:
		/// <summary>
		/// Pozycja
		/// </summary>
		glm::vec4 m_Position = {};

		/// <summary>
		/// Ściany
		/// </summary>
		std::vector<std::shared_ptr<Rectangle>> m_Rectangles = { };

		/// <summary>
		/// Długość ściany.
		/// </summary>
		float length = 0.0f;
	};

	class Sphere : public BaseObject
	{
	public:
		Sphere(const glm::vec4& position, float radius, const glm::fvec4& color);

		Sphere() = default;

		/// <summary>
		/// Rysuje kulę za pomocą podanego renderera.
		/// </summary>
		/// <param name="renderer">Renderer, który ma narysować kulę</param>
		void Draw(Renderer* renderer);

		/// <summary>
		/// Rotuje kulę o podany kąt (w radianach).
		/// </summary>
		/// <param name="radians">Kąt rotacji w radianach</param>
		void Rotate(float radians);

		/// <summary>
		/// Przesuwa kulę o podany wektor przesunięcia.
		/// </summary>
		/// <param name="offset">Wektor przesunięcia</param>
		void Move(glm::fvec3 offset);

		/// <summary>
		/// Obraca kulę wokół podanej płaszczyzny okręgu.
		/// </summary>
		/// <param name="center">Środek okręgu</param>
		/// <param name="radius">Promień okręgu</param>
		/// <param name="angle">Kąt obrotu w radianach</param>
		void CircleAround(glm::fvec2 center, float radius, float angle);

		/// <summary>
		/// Zwraca pozycję kuli.
		/// </summary>
		/// <returns>Pozycja kuli, punkt</returns>
		glm::fvec4 GetPosition();

	private:
		void CreateMesh();
		glm::fvec4 GetPoint(float theta, float phi);
		glm::fvec4 m_Position = {};
		float m_Radius = 0.0f;
		glm::fvec4 m_Color = {};
		std::vector<std::shared_ptr<Triangle>> m_Triangles = {};
	};

}