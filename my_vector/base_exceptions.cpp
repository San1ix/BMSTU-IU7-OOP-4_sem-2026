#include "base_exceptions.h"
#include <cstdio>

BaseError::BaseError(const char* file_name, int line, const char* func_name, const char* err_name)
{
    snprintf(err_message, sizeof(err_message), "\nInfo: %s\nFile: %s\nLine: %d\nFunction: %s\n", err_name, file_name, line, func_name);
}

const char* BaseError::what() const noexcept
{
    return err_message;
}

BaseContainerError::BaseContainerError(const char* file_name, int line, const char* func_name, const char* err_name)
    : BaseError(file_name, line, func_name, err_name) {}

BaseIteratorError::BaseIteratorError(const char* file_name, int line, const char* func_name, const char* err_name)
    : BaseError(file_name, line, func_name, err_name) {}