#include "controller.h"

Controller::Controller(int id, QObject *parent) : QObject(parent), m_id(id), m_state(State::FREE), m_currentFloor(1), m_target(NO_TARGET), m_direction(Direction::STOP)
{
    setState(State::FREE);
}

QList<int> Controller::getQueue() const
{
    QList<int> result;
    for (int f : m_queue) 
        result.append(f);
    return result;
}

void Controller::addTarget(int floor)
{
    if (floor == m_currentFloor)
    {
        if (m_state == State::FREE || m_state == State::WAITING_DOORS_OPEN || m_state == State::WAITING_DOORS_CLOSE)
            setState(State::WAITING_DOORS_OPEN);
        else if (m_state == State::WAITING_CABIN)
        {
            auto it = std::find(m_queue.begin(), m_queue.end(), floor);
            if (it == m_queue.end())
                m_queue.push_back(floor);
        }
        return;
    }
    
    auto it = std::find(m_queue.begin(), m_queue.end(), floor);
    if (it == m_queue.end())
        m_queue.push_back(floor);
    
    if (m_state == State::FREE)
        setState(State::ROUTING);
    else if (m_state == State::WAITING_DOORS_OPEN || m_state == State::WAITING_DOORS_CLOSE)
        setState(State::ROUTING);
}

void Controller::setState(State newState)
{
    if (m_state == newState) return;
    
    onExitState(m_state);
    m_state = newState;
    onEnterState(newState);
}

void Controller::onEnterState(State state)
{
    QString queueStr = "[ ";
    for (int f : m_queue) queueStr += QString::number(f) + " ";
    queueStr += "]";

    switch(state)
    {
    case State::ROUTING:
        chooseTarget();
        if (m_target == m_currentFloor)
        {
            m_queue.remove(m_target);
            setState(State::WAITING_DOORS_OPEN);
        }
        else
        {
            if (m_direction == Direction::UP)
                emit requestCabinMoveUp();
            else if (m_direction == Direction::DOWN)
                emit requestCabinMoveDown();
            setState(State::WAITING_CABIN);
        }
        break;
        
    case State::WAITING_DOORS_OPEN:
        emit requestDoorsOpen();
        break;
        
    case State::FREE:
        m_direction = Direction::STOP;
        m_target = NO_TARGET;
        break;
        
    default:
        break;
    }
    
    emit stateUpdated(m_id, (int)m_state, m_currentFloor, m_target, (int)m_direction, queueStr);
}

void Controller::onExitState(State state) {}

void Controller::slot_free() {}
void Controller::slot_routing() {}
void Controller::slot_waiting_cabin() {}
void Controller::slot_waiting_doors_open() {}
void Controller::slot_waiting_doors_close() {}

void Controller::chooseTarget()
{
    if (m_queue.empty())
    {
        m_target = NO_TARGET;
        m_direction = Direction::STOP;
        return;
    }
    
    int nextTarget = NO_TARGET;
    
    if (m_direction == Direction::UP)
    {
        for (int floor : m_queue)
            if (floor > m_currentFloor) 
            { 
                nextTarget = floor; 
                break; 
            }

        if (nextTarget == NO_TARGET)
        {
            for (int floor : m_queue)
                if (floor < m_currentFloor) 
                    nextTarget = floor;

            if (nextTarget != NO_TARGET)
                m_direction = Direction::DOWN;
        }
    }
    else if (m_direction == Direction::DOWN)
    {
        for (int floor : m_queue)
            if (floor < m_currentFloor) 
            { 
                nextTarget = floor; 
                break; 
            }

        if (nextTarget == NO_TARGET)
        {
            for (int floor : m_queue)
                if (floor > m_currentFloor) 
                    nextTarget = floor;

            if (nextTarget != NO_TARGET)
                m_direction = Direction::UP;
        }
    }
    else
    {
        nextTarget = m_queue.front();
        int minDist = abs(nextTarget - m_currentFloor);
        for (int floor : m_queue)
        {
            int dist = abs(floor - m_currentFloor);
            if (dist < minDist)
            {
                minDist = dist;
                nextTarget = floor;
            }
        }
        m_direction = (nextTarget > m_currentFloor) ? Direction::UP : Direction::DOWN;
    }
    
    m_target = nextTarget;
}

void Controller::onFloorPassed(int floor)
{
    m_currentFloor = floor;
    
    if (m_state == State::WAITING_CABIN && m_currentFloor == m_target)
    {
        m_direction = Direction::STOP;
        emit requestCabinStop();
    }
    
    QString queueStr = "[ ";
    for (int f : m_queue) 
        queueStr += QString::number(f) + " ";
    queueStr += "]";

    emit stateUpdated(m_id, (int)m_state, m_currentFloor, m_target, (int)m_direction, queueStr);
}

void Controller::onCabinStopped()
{
    if (m_state == State::WAITING_CABIN)
    {
        m_queue.remove(m_target);
        m_target = NO_TARGET;
        m_direction = Direction::STOP;
        
        if (m_queue.empty())
            setState(State::WAITING_DOORS_OPEN);
        else
            setState(State::ROUTING);
    }
}

void Controller::onDoorsOpened()
{
    if (m_state == State::WAITING_DOORS_OPEN)
        setState(State::WAITING_DOORS_CLOSE);
}

void Controller::onDoorsClosed()
{
    if (m_state == State::WAITING_DOORS_CLOSE)
    {
        if (m_queue.empty())
        {
            m_direction = Direction::STOP;
            setState(State::FREE);
        }
        else
            setState(State::ROUTING);
    }
}