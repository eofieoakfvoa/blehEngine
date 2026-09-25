#pragma once
#include <glad/glad.h>

//kod copy pasted från https://www.youtube.com/watch?v=JtfeCGi0QIU


//https://learnopengl.com/In-Practice/Debugging
void GLAPIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam);

void enableReportGlErrors();

void createErrorFile();

void reportError(const char *message);