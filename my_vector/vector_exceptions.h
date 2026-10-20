#pragma once

#include "base_exceptions.h"

class errMemory : public BaseContainerError
{
public:
    errMemory(const char* filename, int line, const char* func_name, const char* err_msg = "Memory allocation failed");
};

class errArrNull : public BaseContainerError
{
public:
    errArrNull(const char* filename, int line, const char* func_name, const char* err_msg = "Null array pointer");
};

class errDivisionZero : public BaseContainerError
{
public:
    errDivisionZero(const char* filename, int line, const char* func_name, const char* err_msg = "Division by zero");
};

class errVectorsSizeNotEqual : public BaseContainerError
{
public:
    errVectorsSizeNotEqual(const char* filename, int line, const char* func_name, const char* err_msg = "Vector sizes don't match");
};

class errSizeNotCompatible : public BaseContainerError
{
public:
    errSizeNotCompatible(const char* filename, int line, const char* func_name, const char* err_msg = "Vector size incompatible with operation");
};