#pragma once
#include <iostream>

#define ENABLE_LOGGING

#ifdef ENABLE_LOGGING

#define VASE_LOG_INFO(item) std::cout << "[INFO] " << item << '\n'
#define VASE_LOG_ERROR(item) std::cerr << "[ERROR] " << item << '\n'

#define glError() {GLint err; while ((err = glGetError()) != GL_NO_ERROR) {VASE_LOG_ERROR("GL error: " << err);}}
#else

#define VASE_LOG_INFO(item)
#define VASE_LOG_ERROR(item)

#endif
