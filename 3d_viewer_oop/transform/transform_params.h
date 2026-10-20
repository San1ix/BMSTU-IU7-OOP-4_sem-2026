#pragma once

enum class TransformType
{
    Move,
    Rotate,
    Scale
};

struct TransformParams
{
    TransformType type;
    double x_param;
    double y_param;
    double z_param;
};