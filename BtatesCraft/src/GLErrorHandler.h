#pragma once


#ifdef _MSVC_VER
#define ASSERT(x) if(!(x)) __debugbreak();
#else
#include <assert.h>
#define ASSERT(x) assert(x)
#endif

#ifdef _DEBUG
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogError(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x //Re
#endif // DEBUG

void GLClearError();

bool GLLogError(const char* function, const char* file, int line);

