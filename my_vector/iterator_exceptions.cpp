#include "iterator_exceptions.h"

errDeletedVector::errDeletedVector(const char* filename, int line, const char* func_name, const char* err_msg)
    : BaseIteratorError(filename, line, func_name, err_msg) {}

errIndexOutOfRange::errIndexOutOfRange(const char* filename, int line, const char* func_name, const char* err_msg)
    : BaseIteratorError(filename, line, func_name, err_msg) {}

errDifferentVectors::errDifferentVectors(const char* filename, int line, const char* func_name, const char* err_msg)
    : BaseIteratorError(filename, line, func_name, err_msg) {}