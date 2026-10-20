#pragma once

#include "base_exception.h"

class DirectorException : public BaseException
{
public:
    DirectorException(const char* time, const char* filename, std::size_t line, const char* class_name, const char* method_name, const char* info = "Director exception.") : BaseException(time, filename, line, class_name, method_name, info) {}
};