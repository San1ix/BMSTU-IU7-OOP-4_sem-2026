#include "vector_exceptions.h"

// правочка-левочка: удалила искл со знаком

errMemory::errMemory(const char* filename, int line, const char* func_name, const char* err_msg)
    : BaseContainerError(filename, line, func_name, err_msg) {}

errArrNull::errArrNull(const char* filename, int line, const char* func_name, const char* err_msg)
    : BaseContainerError(filename, line, func_name, err_msg) {}

errDivisionZero::errDivisionZero(const char* filename, int line, const char* func_name, const char* err_msg)
    : BaseContainerError(filename, line, func_name, err_msg) {}

errVectorsSizeNotEqual::errVectorsSizeNotEqual(const char* filename, int line, const char* func_name, const char* err_msg)
    : BaseContainerError(filename, line, func_name, err_msg) {}

errSizeNotCompatible::errSizeNotCompatible(const char* filename, int line, const char* func_name, const char* err_msg)
    : BaseContainerError(filename, line, func_name, err_msg) {}