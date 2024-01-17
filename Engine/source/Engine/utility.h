#pragma once

#include <cstdint>
#include <iostream>

#include <glad/glad.h>

namespace eng
{

	/// <summary>
	/// Funkcja zwrotna dla wiadomości OpenGL.
	/// </summary>
	/// <param name="source">Źródło</param>
	/// <param name="type">Typ wiadomości</param>
	/// <param name="id">Identyfikator wiadomości</param>
	/// <param name="severity">Ważność wiadomości</param>
	/// <param name="length">Długość wiadomości</param>
	/// <param name="message">Wiadomość z OpenGL</param>
	/// <param name="userParam">Parametr użytkownika</param>
	void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

}