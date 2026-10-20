#pragma once

#include <QObject>
#include <list>
#include <algorithm>
#include <QList>

#include "defines.h"

class Controller : public QObject 
{
    Q_OBJECT

public:
    enum class State 
    { 
        FREE, 
        ROUTING, 
        WAITING_CABIN, 
        WAITING_DOORS_OPEN, 
        WAITING_DOORS_CLOSE 
    };

    explicit Controller(int id, QObject *parent = nullptr);
    
    int getId() const 
    { 
        return m_id; 
    }

    int getCurrentFloor() const 
    { 
        return m_currentFloor; 
    }

    int getTarget() const 
    { 
        return m_target; 
    }

    int getDirection() const 
    { 
        return (int)m_direction; 
    }

    State getState() const 
    { 
        return m_state; 
    }

    bool isFree() const 
    { 
        return m_state == State::FREE; 
    }

    QList<int> getQueue() const;
    
    void addTarget(int floor);
    
    void onFloorPassed(int floor);
    void onCabinStopped();
    void onDoorsOpened();
    void onDoorsClosed();

public slots:
    void slot_free();
    void slot_routing();
    void slot_waiting_cabin();
    void slot_waiting_doors_open();
    void slot_waiting_doors_close();

signals:
    void requestDoorsClose();
    void stateUpdated(int id, int state, int floor, int target, int direction, const QString& queue);
    void requestCabinMoveUp();
    void requestCabinMoveDown();
    void requestCabinStop();
    void requestDoorsOpen();

private:
    void setState(State newState);
    void onEnterState(State state);
    void onExitState(State state);
    void chooseTarget();

    int m_id;
    State m_state;
    int m_currentFloor;
    int m_target;
    Direction m_direction;
    std::list<int> m_queue;
};