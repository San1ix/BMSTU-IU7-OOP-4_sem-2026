#include "transform_visitor.h"

#include "object_impl.h"

TransformVisitor::TransformVisitor(const TransformParams& params) : params(params) {}

void TransformVisitor::visit(ObjectImpl& impl)
{
    impl.transform(params);
}