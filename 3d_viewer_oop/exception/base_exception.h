#pragma once

#include <exception>
#include <string>
#include <cstdio>

class BaseException : public std::exception
{
public:
    BaseException(const char* time, const char* filename, std::size_t line, const char* class_name, const char* method_name, const char* info = "Base exception.");

    const char* what() const noexcept override;

protected:
    static const std::size_t err_size = 512;
    char err_msg[err_size] = "";
};