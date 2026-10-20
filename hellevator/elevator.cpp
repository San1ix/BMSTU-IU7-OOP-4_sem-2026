#include "elevator.h"

Elevator::Elevator(int id, QObject *parent) : QObject(parent), m_id(id)
{
    m_controller = new Controller(id, this);
    m_cabin = new Cabin(this);
    
    connect(m_controller, &Controller::requestCabinMoveUp, m_cabin, &Cabin::slot_moving_up);
    connect(m_controller, &Controller::requestCabinMoveDown, m_cabin, &Cabin::slot_moving_down);
    connect(m_controller, &Controller::requestCabinStop, m_cabin, &Cabin::slot_idle);
    connect(m_controller, &Controller::requestDoorsOpen, m_cabin->getDoors(), &Doors::slot_opening);
    
    connect(m_cabin, &Cabin::floorPassed, m_controller, &Controller::onFloorPassed);
    connect(m_cabin, &Cabin::stopped, m_controller, &Controller::onCabinStopped);
    connect(m_cabin->getDoors(), &Doors::doorsOpened, m_controller, &Controller::onDoorsOpened);
    connect(m_cabin->getDoors(), &Doors::doorsClosed, m_controller, &Controller::onDoorsClosed);
    connect(m_cabin->getDoors(), &Doors::stateChanged, this, &Elevator::onDoorsStateChanged);
    
    connect(m_cabin, &Cabin::floorPassed, this, &Elevator::onFloorPassed);
    connect(m_controller, &Controller::stateUpdated, this, &Elevator::onControllerStateUpdated);
    connect(m_controller, &Controller::requestDoorsClose, m_cabin->getDoors(), &Doors::slot_closing);
}

void Elevator::call(int floor)
{
    m_controller->addTarget(floor);
}

void Elevator::openDoors()
{
    if (m_cabin->getState() == Cabin::State::IDLE)
        m_cabin->getDoors()->slot_opening();
}

void Elevator::closeDoors()
{
    if (m_cabin->getState() == Cabin::State::IDLE)
        m_cabin->getDoors()->slot_closing();
}

void Elevator::onControllerStateUpdated(int id, int state, int floor, int target, int direction, const QString& queue)
{
    emit stateUpdated(id, state, floor, target, direction, queue);
}

void Elevator::onFloorPassed(int floor)
{
    emit floorChanged(floor);
}

void Elevator::onDoorsStateChanged(int state)
{
    emit stateUpdated(m_id, (int)m_controller->getState(), m_controller->getCurrentFloor(), m_controller->getTarget(), (int)m_controller->getDirection(), getQueueString());
}

QString Elevator::getQueueString()
{
    QString res = "[ ";
    
    QList<int> queue = m_controller->getQueue();
    for (int f : queue) 
        res += QString::number(f) + " ";
    res += "]";

    return res;
}