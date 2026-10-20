#pragma once

#include "object_impl.h"

class Visitor
{
public:
    Visitor() = default;
    virtual ~Visitor() = default;

    virtual void visit(ObjectImpl& impl) = 0;
};