#pragma once

#include "base_exception.h"

class ReaderException : public BaseException
{
public:
    ReaderException(const char* time, const char* filename, std::size_t line, const char* class_name, const char* method_name, const char* info = "Reader exception.") : BaseException(time, filename, line, class_name, method_name, info) {}
};

class TxtNoFileException : public ReaderException
{
public:
    TxtNoFileException(const char* time, const char* filename, std::size_t line, const char* class_name, const char* method_name, const char* info = "Cannot open file.") : ReaderException(time, filename, line, class_name, method_name, info) {}
};

class TxtReadException : public ReaderException
{
public:
    TxtReadException(const char* time, const char* filename, std::size_t line, const char* class_name, const char* method_name, const char* info = "Cannot read from file.") : ReaderException(time, filename, line, class_name, method_name, info) {}
};

class ObjNoFileException : public ReaderException
{
public:
    ObjNoFileException(const char* time, const char* filename, std::size_t line, const char* class_name, const char* method_name, const char* info = "Cannot open OBJ file.") : ReaderException(time, filename, line, class_name, method_name, info) {}
};

class ObjReadException : public ReaderException
{
public:
    ObjReadException(const char* time, const char* filename, std::size_t line, const char* class_name, const char* method_name, const char* info = "Cannot read from OBJ file.") : ReaderException(time, filename, line, class_name, method_name, info) {}
};