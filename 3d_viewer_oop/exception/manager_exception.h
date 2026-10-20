#pragma once

#include "base_exception.h"

class ManagerException : public BaseException
{
public:
    ManagerException(const char* time, const char* filename,std::size_t line, const char* class_name, const char* method_name, const char* info = "Manager exception.") : BaseException(time, filename, line, class_name, method_name, info) {}
};

class LoadManagerException : public ManagerException
{
public:
    LoadManagerException(const char* time, const char* filename, std::size_t line, const char* class_name, const char* method_name, const char* info = "Load manager exception.") : ManagerException(time, filename, line, class_name, method_name, info) {}
};

class LoadManagerWrongReaderException : public LoadManagerException
{
public:
    LoadManagerWrongReaderException(const char* time, const char* filename, std::size_t line, const char* class_name, const char* method_name, const char* info = "Wrong reader type.") : LoadManagerException(time, filename, line, class_name, method_name, info) {}
};

class LoadManagerWrongDirectorException : public LoadManagerException
{
public:
    LoadManagerWrongDirectorException(const char* time, const char* filename, std::size_t line, const char* class_name, const char* method_name, const char* info = "Wrong director type.") : LoadManagerException(time, filename, line, class_name, method_name, info) {}
};