#pragma once

#include <QObject>
#include <QVector>

#include "elevator.h"

struct ElevatorInfo 
{
    int id;
    int floor;
    bool isFree;
    int direction;
    int currentTarget;
};

class Manager : public QObject 
{
    Q_OBJECT

public:
    enum class State 
    { 
        IDLE, 
        DECISION, 
        HOLDING 
    };

    explicit Manager(QObject *parent = nullptr);
    
    void registerElevator(Elevator* elevator);
    void onFloorCallPressed(int floor);
    void onElevatorStateUpdated(int id, int controllerState, int floor, int target, int direction, const QString& queue);

public slots:
    void slot_idle();
    void slot_decision();
    void slot_holding();

signals:
    void stateChanged(const QString& state);
    void assignTarget(int elevatorId, int floor);

private:
    void setState(State newState);
    void onEnterState(State state);
    bool findBestElevator();

    State m_state;
    QVector<int> m_waitList;
    QVector<ElevatorInfo> m_elevators;
};