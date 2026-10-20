#pragma once

#include <QObject>
#include <QTimer>

#include "doors.h"
#include "config.h"

class Cabin : public QObject 
{
    Q_OBJECT

public:
    enum class State 
    { 
        IDLE, 
        MOVING_UP, 
        MOVING_DOWN 
    };

    explicit Cabin(QObject *parent = nullptr);
    
    State getState() const 
    { 
        return m_state; 
    }

    int getCurrentFloor() const 
    { 
        return m_currentFloor; 
    }

    QString getStateString() const;
    Doors* getDoors() 
    { 
        return &m_doors; 
    }

public slots:
    void slot_idle();
    void slot_moving_up();
    void slot_moving_down();

signals:
    void floorPassed(int floor);
    void stateChanged(int state);
    void stopped();

private:
    void setState(State newState);
    void onEnterState(State state);
    void onExitState(State state);
    
    void onMoveTimer();

    State m_state;
    int m_currentFloor;
    QTimer *m_moveTimer;
    Doors m_doors;
};