#pragma once

#include <vector>
#include <memory>

#include "base_obj.h"
#include "scene.h"

class Composite : public BaseObj
{
public:
    Composite() = default;
    explicit Composite(std::vector<std::shared_ptr<BaseObj>> objects);
    Composite(const Composite& other);
    ~Composite() override = default;

    bool add(std::shared_ptr<BaseObj> obj) override;
    bool remove(const iterator& it) override;
    void accept(Visitor& visitor) override;
    std::shared_ptr<BaseObj> clone() const override;

    bool is_visible() const override 
    { 
        return true; 
    }

    bool is_composite() const override 
    { 
        return true; 
    }

    Point get_center() const override;

    iterator begin() noexcept override;
    iterator end() noexcept override;

    std::vector<std::size_t> get_child_ids() const;

private:
    std::vector<std::shared_ptr<BaseObj>> objects;
};