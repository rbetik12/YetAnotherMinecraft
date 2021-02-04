#pragma once

#ifdef R_ENABLE_ASSERTS
#include "Log.h"
#define R_ASSERT(x, ...) { if(!(x)) { R_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define R_CORE_ASSERT(x, ...) { if(!(x)) { R_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define R_ASSERT(x, ...)
#define R_CORE_ASSERT(x, ...)
#endif

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)