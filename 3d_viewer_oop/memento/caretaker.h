#pragma once

#include "base_memento.h"

#include <deque>
#include <memory>

class Caretaker
{
public:
    Caretaker() = default;
    ~Caretaker() = default;

    void add(std::shared_ptr<BaseMemento> memento);
    std::shared_ptr<BaseMemento> pop();
    std::size_t size() const;

private:
    static constexpr std::size_t max_size = 20;
    std::deque<std::shared_ptr<BaseMemento>> snapshots;
};