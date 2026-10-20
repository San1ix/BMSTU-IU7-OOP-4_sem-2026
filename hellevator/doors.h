#pragma once

#include <QObject>
#include <QTimer>

#include "config.h"

class Doors : public QObject 
{
    Q_OBJECT

public:
    enum class State 
    { 
        CLOSED, 
        CLOSING, 
        OPENED, 
        OPENING 
    };

    explicit Doors(QObject *parent = nullptr);
    
    State getState() const 
    { 
        return m_state; 
    }

    QString getStateString() const;
    void resetWaitTimer();

public slots:
    void slot_closed();
    void slot_closing();
    void slot_opened();
    void slot_opening();

signals:
    void stateChanged(int state);
    void doorsOpened();
    void doorsClosed();

private:
    void setState(State newState);
    void onEnterState(State state);
    void onExitState(State state);
    
    void onMoveTimeout();
    void onWaitTimeout();

    State m_state;
    QTimer *m_moveTimer;
    QTimer *m_waitTimer;
};