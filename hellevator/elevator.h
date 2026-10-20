#pragma once

#include <QObject>
#include <QList>

#include "controller.h"
#include "cabin.h"

class Elevator : public QObject 
{
    Q_OBJECT

public:
    explicit Elevator(int id, QObject *parent = nullptr);
    
    void call(int floor);
    void openDoors();
    void closeDoors();
    
    int getId() const 
    { 
        return m_id; 
    }

    int getCurrentFloor() const 
    { 
        return m_controller->getCurrentFloor(); 
    }

    bool isFree() const 
    { 
        return m_controller->isFree(); 
    }
    
    int getDoorsState() const 
    { 
        return (int)m_cabin->getDoors()->getState(); 
    }

    QString getDoorsStateString() const 
    { 
        return m_cabin->getDoors()->getStateString(); 
    }

    QString getCabinStateString() const 
    { 
        return m_cabin->getStateString(); 
    }

signals:
    void stateUpdated(int id, int controllerState, int floor, int target, int direction, const QString& queue);
    void floorChanged(int floor);

private slots:
    void onControllerStateUpdated(int id, int state, int floor, int target, int direction, const QString& queue);
    void onFloorPassed(int floor);
    void onDoorsStateChanged(int state);

private:
    QString getQueueString();

    int m_id;
    Controller *m_controller;
    Cabin *m_cabin;
};