#pragma once

#include "base_exceptions.h"

class errDeletedVector : public BaseIteratorError
{
public:
    errDeletedVector(const char* filename, int line, const char* func_name, const char* err_msg = "Iterator points to deleted vector");
};

class errIndexOutOfRange : public BaseIteratorError
{
public:
    errIndexOutOfRange(const char* filename, int line, const char* func_name, const char* err_msg = "Iterator index out of bounds");
};

class errDifferentVectors : public BaseIteratorError
{
public:
    errDifferentVectors(const char* filename, int line, const char* func_name, const char* err_msg = "Iterators belong to different vectors");
};