#pragma once

#include "base_memento.h"

class SceneMemento : public BaseMemento
{
public:
    explicit SceneMemento(const std::vector<std::shared_ptr<BaseObj>>& objects);
    ~SceneMemento() override = default;
    const std::vector<std::shared_ptr<BaseObj>>& get_state() const override;

private:
    std::vector<std::shared_ptr<BaseObj>> state;
};