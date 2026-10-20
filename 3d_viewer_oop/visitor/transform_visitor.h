#pragma once

#include "visitor.h"
#include "transform_params.h"

class TransformVisitor : public Visitor
{
public:
    explicit TransformVisitor(const TransformParams& params);
    ~TransformVisitor() override = default;

    void visit(ObjectImpl& impl) override;

private:
    TransformParams params;
};