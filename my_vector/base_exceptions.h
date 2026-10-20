#pragma once

#include <exception>

#define BUF_SIZE 512

class BaseError : public std::exception
{
public:
    BaseError(const char* file_name, int line, const char* func_name, const char* err_name = "Error");
    [[nodiscard]] const char* what() const noexcept override;

protected:
    char err_message[BUF_SIZE]{};
};

class BaseContainerError : public BaseError
{
public:
    BaseContainerError(const char* file_name, int line, const char* func_name, const char* err_name = "Container error");
};

class BaseIteratorError : public BaseError
{
public:
    BaseIteratorError(const char* file_name, int line, const char* func_name, const char* err_name = "Iterator error");
};