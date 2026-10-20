#include "caretaker.h"

void Caretaker::add(std::shared_ptr<BaseMemento> memento)
{
    if (snapshots.size() >= max_size)
        snapshots.pop_front();
    snapshots.push_back(std::move(memento));
}

std::shared_ptr<BaseMemento> Caretaker::pop()
{
    if (snapshots.empty())
        return nullptr;
    auto memento = snapshots.back();
    snapshots.pop_back();
    return memento;
}

std::size_t Caretaker::size() const
{
    return snapshots.size();
}