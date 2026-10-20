#pragma once

#include <memory>

#include "base_manager.h"
#include "transform_params.h"

class TransformManager : public BaseManager
{
public:
    static std::shared_ptr<TransformManager> get_instance();
    TransformManager(const TransformManager&) = delete;
    TransformManager& operator=(const TransformManager&) = delete;

    void transform_object(std::size_t id, const TransformParams& params);

private:
    TransformManager() = default;
};