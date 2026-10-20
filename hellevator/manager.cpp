#include "manager.h"

Manager::Manager(QObject *parent) : QObject(parent), m_state(State::IDLE)
{
    setState(State::IDLE);
}

void Manager::registerElevator(Elevator* elevator)
{
    m_elevators.push_back({elevator->getId(), elevator->getCurrentFloor(), true, 0});
    connect(elevator, &Elevator::stateUpdated, this, &Manager::onElevatorStateUpdated);
}

void Manager::setState(State newState)
{
    if (m_state == newState) 
        return;
    
    m_state = newState;
    onEnterState(newState);
}

void Manager::onEnterState(State state)
{
    switch(state)
    {
        case State::DECISION:
            emit stateChanged("DECISION");
            
            if (m_waitList.isEmpty())
            {
                setState(State::IDLE);
                return;
            }
            
            if (!findBestElevator())
                setState(State::HOLDING);
            break;
            
        case State::IDLE:
            emit stateChanged("IDLE");
            break;
            
        case State::HOLDING:
            emit stateChanged("HOLDING");
            break;
    }
}


void Manager::slot_idle()
{
    emit stateChanged("IDLE");
}

void Manager::slot_decision()
{
    emit stateChanged("DECISION");
    
    if (m_waitList.isEmpty())
    {
        setState(State::IDLE);
        return;
    }
    
    bool found = findBestElevator();
    
    if (!found)
        setState(State::HOLDING);
}

void Manager::slot_holding()
{
    emit stateChanged("HOLDING");
}

void Manager::onFloorCallPressed(int floor)
{
    if (!m_waitList.contains(floor))
        m_waitList.append(floor);
    
    if (m_state == State::IDLE)
        setState(State::DECISION);
    else if (m_state == State::HOLDING)
        setState(State::DECISION);
}

void Manager::onElevatorStateUpdated(int id, int controllerState, int floor, int target, int direction, const QString& queue)
{
    bool freed = false;
    
    for (auto &el : m_elevators)
    {
        if (el.id == id)
        {
            bool wasFree = el.isFree;
            el.floor = floor;
            el.isFree = (controllerState == 0);
            el.direction = direction;
            
            if (!wasFree && el.isFree)
                freed = true;
            break;
        }
    }
    
    if (freed && !m_waitList.isEmpty() && m_state == State::HOLDING)
        setState(State::DECISION);
}

bool Manager::findBestElevator()
{
    if (m_waitList.isEmpty())
        return false;
    
    int target = m_waitList.first();
    int bestId = -1;
    int minCost = -1;
    
    for (const auto &el : m_elevators)
    {
        int cost = -1;
        
        if (el.isFree)
            cost = abs(el.floor - target);
        else if (el.direction == 1 && target > el.floor)
            cost = target - el.floor;
        else if (el.direction == -1 && target < el.floor)
            cost = el.floor - target;
        
        if (cost != -1 && (minCost == -1 || cost < minCost))
        {
            minCost = cost;
            bestId = el.id;
        }
    }
    
    if (bestId == -1)
        return false;
    
    m_waitList.removeFirst();
    
    for (auto &el : m_elevators)
    {
        if (el.id == bestId)
        {
            el.isFree = false;
            break;
        }
    }
    
    emit assignTarget(bestId, target);
    
    if (!m_waitList.isEmpty())
        setState(State::DECISION);
    else
        setState(State::IDLE);
    
    return true;
}