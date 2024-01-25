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

	private:
		/// <summary>
		/// Odbiornik zdarzeń.
		/// </summary>
		EventReceiver m_Receiver;
	};

	class Texture : public BaseObject
	{
	public:
		Texture(const std::string& filePath);
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

		glm::fvec4 GetCenter() const;

		void Draw(Renderer* renderer);

		void Rotate(float radians);

		inline Triangle& GetLeftTriangle() { return m_LeftTriangle; }
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

		void Draw(Renderer* renderer);

		void Rotate(float radians);

	private:
		void CreateMesh();
		glm::fvec4 GetPoint(float theta, float phi);
		glm::vec4 m_Position = {};
		float m_Radius = 0.0f;
		glm::fvec4 m_Color = {};
		std::vector<std::shared_ptr<Triangle>> m_Triangles = {};
	};

}