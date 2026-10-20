#include "base_exception.h"

BaseException::BaseException(const char* time, const char* filename, std::size_t line, const char* class_name, const char* method_name, const char* info)
{
    snprintf(err_msg, err_size, "Time: %s, file: %s, line: %zu, class: %s, method: %s\nInfo: %s", time, filename, line, class_name, method_name, info);
}

const char* BaseException::what() const noexcept
{
    return err_msg;
}