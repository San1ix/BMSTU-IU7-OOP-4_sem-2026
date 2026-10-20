#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    m_manager = new Manager(this);
    
    connect(m_manager, &Manager::stateChanged, this, &MainWindow::onManagerStateChanged);
    connect(m_manager, &Manager::assignTarget, [this](int elevatorId, int floor) 
    {
        if (m_elevators.contains(elevatorId))
            m_elevators[elevatorId]->call(floor);
    });
    
    const int NUM_ELEVATORS = 2;
    for (int id = 1; id <= NUM_ELEVATORS; id++) 
    {
        Elevator *elevator = new Elevator(id, this);
        m_elevators[id] = elevator;
        m_manager->registerElevator(elevator);
        
        connect(elevator, &Elevator::stateUpdated, this, &MainWindow::onElevatorStateUpdated);
    }
    
    setupShaftArrays();
    setupElevatorConnections();
    
    updateShaftVisual(1, 1, 0);
    updateShaftVisual(2, 1, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupShaftArrays()
{
    ui->el_1_dir_on_display->setAlignment(Qt::AlignCenter);
    ui->el_2_dir_on_display->setAlignment(Qt::AlignCenter);
    
    ui->el_1_dir_on_display->setText("■ СТОП");
    ui->el_2_dir_on_display->setText("■ СТОП");
    ui->el_1_dir_on_display->setStyleSheet("font-size: 14px; font-weight: bold; color: #BDBDBD;");
    ui->el_2_dir_on_display->setStyleSheet("font-size: 14px; font-weight: bold; color: #BDBDBD;");

    shaft_1_labels = 
    {
        ui->floor_1_el_1, ui->floor_2_el_1, ui->floor_3_el_1,
        ui->floor_4_el_1, ui->floor_5_el_1, ui->floor_6_el_1,
        ui->floor_7_el_1, ui->floor_8_el_1, ui->floor_9_el_1
    };

    shaft_2_labels = 
    {
        ui->floor_1_el_2, ui->floor_2_el_2, ui->floor_3_el_2,
        ui->floor_4_el_2, ui->floor_5_el_2, ui->floor_6_el_2,
        ui->floor_7_el_2, ui->floor_8_el_2, ui->floor_9_el_2
    };

    QFont mono_font("Courier New", 12, QFont::Bold);
    for (auto lbl : shaft_1_labels) 
    {
        lbl->setFont(mono_font);
        lbl->setAlignment(Qt::AlignCenter);
    }
    for (auto lbl : shaft_2_labels) 
    {
        lbl->setFont(mono_font);
        lbl->setAlignment(Qt::AlignCenter);
    }
    
    m_managerLabels[1] = ui->el_1_manager;
    m_managerLabels[2] = ui->el_2_manager;
    m_controllerLabels[1] = ui->el_1_controller;
    m_controllerLabels[2] = ui->el_2_controller;
    m_cabinLabels[1] = ui->el_1_cabin;
    m_cabinLabels[2] = ui->el_2_cabin;
    m_doorsLabels[1] = ui->el_1_doors;
    m_doorsLabels[2] = ui->el_2_doors;
    m_floorLabels[1] = ui->el_1_cur_floor;
    m_floorLabels[2] = ui->el_2_cur_floor;
    m_targetLabels[1] = ui->el_1_target;
    m_targetLabels[2] = ui->el_2_target;
    m_directionLabels[1] = ui->el_1_direction;
    m_directionLabels[2] = ui->el_2_direction;
    m_queueLabels[1] = ui->el_1_queue;
    m_queueLabels[2] = ui->el_2_queue;
}

void MainWindow::setupElevatorConnections()
{
    connect(ui->floor_call, &QPushButton::clicked, this, [this]() 
    {
        m_manager->onFloorCallPressed(ui->floor_spin_box->value());
    });

    for (int i = 1; i <= 9; i++) 
    {
        QPushButton *btn = findChild<QPushButton*>(QString("el_1_%1_btn").arg(i));
        if (btn) {
            connect(btn, &QPushButton::clicked, [this, i]() 
            {
                if (m_elevators.contains(1))
                    m_elevators[1]->call(i);
            });
        }
    }
    
    connect(ui->el_1_open_doors_btn, &QPushButton::clicked, [this]() 
    {
        if (m_elevators.contains(1))
            m_elevators[1]->openDoors();
    });
    
    connect(ui->el_1_close_doors_btn, &QPushButton::clicked, [this]() 
    {
        if (m_elevators.contains(1))
            m_elevators[1]->closeDoors();
    });

    for (int i = 1; i <= 9; ++i) {
        QPushButton *btn = findChild<QPushButton*>(QString("el_2_%1_btn").arg(i));
        if (btn) {
            connect(btn, &QPushButton::clicked, [this, i]() 
            {
                if (m_elevators.contains(2))
                    m_elevators[2]->call(i);
            });
        }
    }
    
    connect(ui->el_2_open_doors_btn, &QPushButton::clicked, [this]() 
    {
        if (m_elevators.contains(2))
            m_elevators[2]->openDoors();
    });
    
    connect(ui->el_2_close_doors_btn, &QPushButton::clicked, [this]() 
    {
        if (m_elevators.contains(2))
            m_elevators[2]->closeDoors();
    });
}

void MainWindow::onElevatorStateUpdated(int id, int controllerState, int floor, int target, int direction, const QString& queue)
{
    updateElevatorInfoPanel(id, controllerState, floor, target, direction, queue);
    
    if (m_elevators.contains(id)) {
        int doorsState = m_elevators[id]->getDoorsState();
        updateShaftVisual(id, floor, doorsState);
        updateDirectionDisplay(id, direction);
    }
}

void MainWindow::updateElevatorInfoPanel(int id, int controllerState, int floor, int target, int direction, const QString& queue)
{
    if (m_controllerLabels.contains(id)) 
        m_controllerLabels[id]->setText(controllerStateToString(controllerState));
    
    if (m_floorLabels.contains(id))
        m_floorLabels[id]->setText(QString::number(floor));
    
    if (m_targetLabels.contains(id))
        m_targetLabels[id]->setText(target == NO_TARGET ? "-" : QString::number(target));
    
    if (m_directionLabels.contains(id))
        m_directionLabels[id]->setText(directionToString(direction));
    
    if (m_queueLabels.contains(id))
        m_queueLabels[id]->setText(queue);
    
    if (m_elevators.contains(id)) 
    {
        if (m_cabinLabels.contains(id)) 
            m_cabinLabels[id]->setText(m_elevators[id]->getCabinStateString());
        if (m_doorsLabels.contains(id))
            m_doorsLabels[id]->setText(m_elevators[id]->getDoorsStateString());
    }
}

void MainWindow::onManagerStateChanged(const QString& state)
{
    for (int id = 1; id <= 2; id++) 
        if (m_managerLabels.contains(id))
            m_managerLabels[id]->setText(state);
}

void MainWindow::updateShaftVisual(int id, int currentFloor, int doorsState)
{
    const QVector<QLabel*> &shaft = (id == 1) ? shaft_1_labels : shaft_2_labels;

    for (int i = 0; i < 9; i++)
        shaft[i]->setText("______");

    if (currentFloor >= 1 && currentFloor <= 9) 
    {
        QString elView;
        switch(doorsState) 
        {
            case 0: 
                elView = "__||__"; 
                break;
            case 1: 
                elView = "_|__|_"; 
                break;
            case 2: 
                elView = "_[__]_"; 
                break;
            case 3: 
                elView = "__[]__"; 
                break;
            default: 
                elView = "__||__"; 
                break;
        }
        shaft[currentFloor - 1]->setText(elView);
    }
}

void MainWindow::updateDirectionDisplay(int id, int direction)
{
    QLabel *dirLabel = (id == 1) ? ui->el_1_dir_on_display : ui->el_2_dir_on_display;
    
    if (direction == 1) 
    {
        dirLabel->setText("▲ ВВЕРХ");
        dirLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #81C784;");
    } 
    else if (direction == -1) 
    {
        dirLabel->setText("▼ ВНИЗ");
        dirLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #64B5F6;");
    } 
    else 
    {
        dirLabel->setText("■ СТОП");
        dirLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #BDBDBD;");
    }
}

QString MainWindow::doorsStateToString(int state) const
{
    switch(state) 
    {
        case 0: 
            return "CLOSED";
        case 1: 
            return "CLOSING";
        case 2: 
            return "OPENED";
        case 3: 
            return "OPENING";
        default: 
            return "UNKNOWN";
    }
}

QString MainWindow::controllerStateToString(int state) const
{
    switch(state) 
    {
        case 0: 
            return "FREE";
        case 1: 
            return "ROUTING";
        case 2: 
            return "WAITING_CABIN";
        case 3: 
            return "WAITING_DOORS_OPEN";
        case 4: 
            return "WAITING_DOORS_CLOSE";
        default: 
            return "UNKNOWN";
    }
}

QString MainWindow::cabinStateToString(int state) const
{
    switch(state) 
    {
        case 0: 
            return "IDLE";
        case 1: 
            return "MOVING_UP";
        case 2: 
            return "MOVING_DOWN";
        default: 
            return "UNKNOWN";
    }
}

QString MainWindow::directionToString(int direction) const
{
    switch(direction) 
    {
        case 1: 
            return "UP";
        case -1: 
            return "DOWN";
        default: 
            return "STOP";
    }
}