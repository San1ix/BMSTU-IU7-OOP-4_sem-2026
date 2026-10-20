#include "base_model.h"

#include "visitor.h"

void BaseModel::accept(Visitor& visitor)
{
    visitor.visit(*this);
}