#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QVector>
#include <QMap>

#include "elevator.h"
#include "manager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onElevatorStateUpdated(int id, int controllerState, int floor, int target, int direction, const QString& queue);
    void onManagerStateChanged(const QString& state);
    void updateShaftVisual(int id, int floor, int doorsState);
    void updateDirectionDisplay(int id, int direction);

private:
    void setupElevatorConnections();
    void setupShaftArrays();
    void updateElevatorInfoPanel(int id, int controllerState, int floor, int target, int direction, const QString& queue);
    
    QString doorsStateToString(int state) const;
    QString controllerStateToString(int state) const;
    QString cabinStateToString(int state) const;
    QString directionToString(int direction) const;

    Ui::MainWindow *ui;
    Manager *m_manager;
    QMap<int, Elevator*> m_elevators;
    
    QVector<QLabel*> shaft_1_labels;
    QVector<QLabel*> shaft_2_labels;
    
    QMap<int, QLabel*> m_controllerLabels;
    QMap<int, QLabel*> m_cabinLabels;
    QMap<int, QLabel*> m_doorsLabels;
    QMap<int, QLabel*> m_floorLabels;
    QMap<int, QLabel*> m_targetLabels;
    QMap<int, QLabel*> m_directionLabels;
    QMap<int, QLabel*> m_queueLabels;
    QMap<int, QLabel*> m_managerLabels;
};