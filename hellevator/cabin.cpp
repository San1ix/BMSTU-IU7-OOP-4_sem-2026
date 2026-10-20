#include "cabin.h"

Cabin::Cabin(QObject *parent) : QObject(parent), m_state(State::IDLE), m_currentFloor(1)
{
    m_moveTimer = new QTimer(this);
    m_moveTimer->setSingleShot(false);
    connect(m_moveTimer, &QTimer::timeout, this, &Cabin::onMoveTimer);
    
    setState(State::IDLE);
}

void Cabin::setState(State newState)
{
    if (m_state == newState) 
        return;
    
    onExitState(m_state);
    m_state = newState;
    onEnterState(newState);
    
    emit stateChanged((int)m_state);
}

void Cabin::onEnterState(State state)
{
    switch(state)
    {
        case State::MOVING_UP:
            m_moveTimer->start(Config::FLOOR_PASS_TIME);
            break;
        case State::MOVING_DOWN:
            m_moveTimer->start(Config::FLOOR_PASS_TIME);
            break;
        case State::IDLE:
            m_moveTimer->stop();
            emit stopped();
            m_doors.slot_opening();
            break;
    }
}

void Cabin::onExitState(State state)
{
    switch(state)
    {
        case State::MOVING_UP:
        case State::MOVING_DOWN:
            m_moveTimer->stop();
            break;
        default:
            break;
    }
}

void Cabin::onMoveTimer()
{
    if (m_state == State::MOVING_UP)
        m_currentFloor++;
    else if (m_state == State::MOVING_DOWN)
        m_currentFloor--;
    
    emit floorPassed(m_currentFloor);
}

void Cabin::slot_idle() 
{ 
    setState(State::IDLE); 
}

void Cabin::slot_moving_up() 
{ 
    setState(State::MOVING_UP); 
}

void Cabin::slot_moving_down() 
{ 
    setState(State::MOVING_DOWN); 
}

QString Cabin::getStateString() const
{
    switch(m_state) 
    {
        case State::IDLE: 
            return "IDLE";
        case State::MOVING_UP: 
            return "MOVING_UP";
        case State::MOVING_DOWN: 
            return "MOVING_DOWN";
        default: 
            return "UNKNOWN";
    }
}