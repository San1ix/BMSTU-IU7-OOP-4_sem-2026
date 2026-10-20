#pragma once

#include "invisible_obj.h"
#include "base_viewer_impl.h"

#include <memory>

class BaseViewer : public InvisibleObj
{
public:
    BaseViewer() = default;
    ~BaseViewer() override = default;

    virtual std::shared_ptr<BaseViewerImpl> get_impl() const = 0;
};
