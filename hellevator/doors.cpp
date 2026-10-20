#include "doors.h"

Doors::Doors(QObject *parent) : QObject(parent), m_state(State::CLOSED)
{
    m_moveTimer = new QTimer(this);
    m_moveTimer->setSingleShot(true);
    
    m_waitTimer = new QTimer(this);
    m_waitTimer->setSingleShot(true);
    
    connect(m_moveTimer, &QTimer::timeout, this, &Doors::onMoveTimeout);
    connect(m_waitTimer, &QTimer::timeout, this, &Doors::onWaitTimeout);
    
    setState(State::CLOSED);
}

void Doors::setState(State newState)
{
    if (m_state == newState) 
        return;
    
    onExitState(m_state);
    m_state = newState;
    onEnterState(newState);
    
    emit stateChanged((int)m_state);
}

void Doors::onEnterState(State state)
{
    switch(state)
    {
        case State::OPENING:
            m_moveTimer->start(Config::DOOR_TIME);
            break;
        case State::CLOSING:
            m_moveTimer->start(Config::DOOR_TIME);
            break;
        case State::OPENED:
            m_waitTimer->start(Config::WAIT_TIME);
            emit doorsOpened();
            break;
        case State::CLOSED:
            emit doorsClosed();
            break;
    }
}

void Doors::onExitState(State state)
{
    switch(state)
    {
        case State::OPENING:
        case State::CLOSING:
            m_moveTimer->stop();
            break;
        case State::OPENED:
            m_waitTimer->stop();
            break;
        default:
            break;
    }
}

void Doors::onMoveTimeout()
{
    if (m_state == State::OPENING)
        setState(State::OPENED);
    else if (m_state == State::CLOSING)
        setState(State::CLOSED);
}

void Doors::onWaitTimeout()
{
    if (m_state == State::OPENED)
        setState(State::CLOSING);
}

void Doors::slot_closed() {}
void Doors::slot_closing() 
{ 
    setState(State::CLOSING); 
}

void Doors::slot_opened() 
{ 
    setState(State::CLOSING); 
}

void Doors::resetWaitTimer()
{
    if (m_state == State::OPENED)
        m_waitTimer->start(Config::WAIT_TIME);
}

void Doors::slot_opening() 
{ 
    if (m_state == State::CLOSED || m_state == State::CLOSING)
        setState(State::OPENING);
    else if (m_state == State::OPENED)
        resetWaitTimer();
}

QString Doors::getStateString() const
{
    switch(m_state) 
    {
        case State::CLOSED: 
            return "CLOSED";
        case State::CLOSING: 
            return "CLOSING";
        case State::OPENED: 
            return "OPENED";
        case State::OPENING: 
            return "OPENING";
        default: 
            return "UNKNOWN";
    }
}