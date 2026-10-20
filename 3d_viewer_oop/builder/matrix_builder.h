#pragma once

#include <memory>

#include "base_builder.h"
#include "matrix_model_structure.h"

class MatrixBuilder : public BaseBuilder
{
public:
    MatrixBuilder();
    ~MatrixBuilder() override = default;

    void build_points(const std::vector<Point>& points) override;
    void build_edges(const std::vector<Edge>& edges) override;
    void build_center() override;

    std::shared_ptr<BaseModelStructure> get_structure() const override;

private:
    std::shared_ptr<MatrixModelStructure> structure;
};