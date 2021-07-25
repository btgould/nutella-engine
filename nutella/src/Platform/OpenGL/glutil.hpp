#pragma once

#include "ntpch.hpp"
#include "glad/glad.h"

#include <signal.h>

#ifndef NT_DIST
static void glClearError() {
	while (glGetError() != GL_NO_ERROR)
		;
}

static bool glLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		NT_CORE_ERROR("OpenGL Error: {0} in {1} in {2}:{3}", error, function, file, line);
		return false;
	}

	return true;
}

	#define GL_CALL(x)                                                                             \
		glClearError();                                                                            \
		x;                                                                                         \
		NT_CORE_ASSERT(glLogCall(#x, __FILE__, __LINE__), "OpenGL Error!")
#else
static void glClearError() {}

static bool glLogCall(const char* function, const char* file, int line) {
	return true;
}

	#define GL_CALL(x) x;

#endif
