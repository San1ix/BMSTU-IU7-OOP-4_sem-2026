#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(nullptr)
    , color(QColor(255, 192, 203))
    , width(2)
    , angle(45.0)
    , use_input_center(false)
{
    ui->setupUi(this);
    this->setWindowTitle("Розовая лабка №1");

    scene = new QGraphicsScene(this);

    ui->canvas->setScene(scene);
    ui->canvas->setRenderHint(QPainter::Antialiasing);

    ui->width_box->setValue(width);
    ui->angle_box->setValue(angle);

    ui->input_center_radio_btn->setChecked(false);

    update_btns_state();
    clean_input_boxes();
}

MainWindow::~MainWindow()
{
    delete ui;
    if (scene)
        delete scene;
}

void MainWindow::update_btns_state()
{
    request_t request;
    request.cmd = CHECK_MODEL;
    bool loaded = (perform_cmd(request) == RC_OK);

    ui->move_btn->setEnabled(loaded);
    ui->rotate_btn->setEnabled(loaded);
    ui->scale_btn->setEnabled(loaded);

    ui->dx_box->setEnabled(loaded);
    ui->dy_box->setEnabled(loaded);
    ui->dz_box->setEnabled(loaded);
    
    ui->x_box->setEnabled(loaded);
    ui->y_box->setEnabled(loaded);
    ui->z_box->setEnabled(loaded);
    
    ui->kx_box->setEnabled(loaded);
    ui->ky_box->setEnabled(loaded);
    ui->kz_box->setEnabled(loaded);

    ui->xc_box->setEnabled(loaded && use_input_center);
    ui->yc_box->setEnabled(loaded && use_input_center);
    ui->zc_box->setEnabled(loaded && use_input_center);
}

void MainWindow::clean_input_boxes()
{
    ui->dx_box->setValue(0.0);
    ui->dy_box->setValue(0.0);
    ui->dz_box->setValue(0.0);
    
    ui->x_box->setValue(0.0);
    ui->y_box->setValue(0.0);
    ui->z_box->setValue(0.0);

    ui->kx_box->setValue(1.0);
    ui->ky_box->setValue(1.0);
    ui->kz_box->setValue(1.0);

    ui->xc_box->setValue(0.0);
    ui->yc_box->setValue(0.0);
    ui->zc_box->setValue(0.0);
    
    ui->width_box->setValue(2);
    ui->angle_box->setValue(45.0);
}

exit_code_t MainWindow::draw_model()
{
    if (!scene)
        return RC_FAIL_SCENE_NOT_LOADED;

    canvas_t canvas;
    canvas.scene = scene;
    QGraphicsView *view = ui->canvas;
    canvas.width = view->width();
    canvas.height = view->height();

    pen_params_t pen_params;
    pen_params.color = color;
    pen_params.width = width;
    pen_params.angle = angle;

    draw_params_t draw_params;
    draw_params.edge_params = pen_params;
    draw_params.center_params = pen_params;

    request_t request;
    request.cmd = DRAW_MODEL;
    request.scene = canvas;
    request.draw_params = &draw_params;

    return perform_cmd(request);
}

void MainWindow::on_move_btn_clicked()
{
    params_t params;
    params.x_param = ui->dx_box->value();
    params.y_param = ui->dy_box->value();
    params.z_param = ui->dz_box->value();

    request_t request;
    request.cmd = MOVE_MODEL;
    request.transformation = params;

    exit_code_t rc = perform_cmd(request);

    if (rc != RC_OK)
        show_err_msg(rc, this);
    else
    {
        if (!use_input_center)
        {
            request.cmd = UPDATE_CENTER;
            perform_cmd(request);
        }
        rc = draw_model();
    }
}

void MainWindow::on_rotate_btn_clicked()
{
    params_t params;
    params.x_param = ui->x_box->value();
    params.y_param = ui->y_box->value();
    params.z_param = ui->z_box->value();

    request_t request;
    request.cmd = ROTATE_MODEL;
    request.transformation = params;

    exit_code_t rc = perform_cmd(request);

    if (rc != RC_OK)
        show_err_msg(rc, this);
    else
    {
        if (!use_input_center)
        {
            request.cmd = UPDATE_CENTER;
            perform_cmd(request);
        }
        rc = draw_model();
    }
}

void MainWindow::on_scale_btn_clicked()
{
    params_t params;
    params.x_param = ui->kx_box->value();
    params.y_param = ui->ky_box->value();
    params.z_param = ui->kz_box->value();

    request_t request;
    request.cmd = SCALE_MODEL;
    request.transformation = params;

    exit_code_t rc = perform_cmd(request);

    if (rc != RC_OK)
        show_err_msg(rc, this);
    else
    {
        if (!use_input_center)
        {
            request.cmd = UPDATE_CENTER;
            perform_cmd(request);
        }
        rc = draw_model();
    }
}

void MainWindow::on_open_file_btn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выбор файла", "", "Текстовый файл (*.txt)");
    if (filename.isEmpty())
        return;

    clean_input_boxes();

    request_t request;
    request.cmd = LOAD_MODEL;
    QByteArray ba = filename.toUtf8();
    request.filename = ba.constData();

    exit_code_t rc = perform_cmd(request);

    if (rc != RC_OK)
    {
        scene->clear();
        show_err_msg(rc, this);
    }
    else
    {
        if (!use_input_center)
        {
            request.cmd = UPDATE_CENTER;
            perform_cmd(request);
        }
        update_btns_state();
        rc = draw_model();
    }
}

void MainWindow::on_save_to_file_btn_clicked()
{
    request_t request;
    request.cmd = CHECK_MODEL;
    
    if (perform_cmd(request) != RC_OK)
    {
        show_err_msg(RC_FAIL_MODEL_NOT_LOADED, this);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this, "Сохранить модель", "", "Текстовый файл (*.txt)");
    if (filename.isEmpty())
        return;

    request.cmd = SAVE_MODEL;
    QByteArray ba = filename.toUtf8();
    request.filename = ba.constData();

    exit_code_t rc = perform_cmd(request);

    if (rc != RC_OK)
        show_err_msg(rc, this);
}

void MainWindow::on_color_btn_clicked()
{
    QColor new_color = QColorDialog::getColor(color, this, "Выберите цвет граней");
    if (new_color.isValid())
    {
        color = new_color;
        if (ui->move_btn->isEnabled())
            draw_model();
    }
}

void MainWindow::on_input_center_radio_btn_clicked()
{
    use_input_center = ui->input_center_radio_btn->isChecked();
    
    if (!use_input_center)
    {
        request_t request;
        request.cmd = UPDATE_CENTER;
        perform_cmd(request);
    }
    else
    {
        point_t center;
        center.x = ui->xc_box->value();
        center.y = ui->yc_box->value();
        center.z = ui->zc_box->value();
        
        request_t request;
        request.cmd = SET_CENTER;
        request.center = center;
        perform_cmd(request);
    }
    
    update_btns_state();
    draw_model();
}

void MainWindow::on_xc_box_editingFinished()
{
    if (!use_input_center || !ui->move_btn->isEnabled())
        return;
        
    point_t center;
    center.x = ui->xc_box->value();
    center.y = ui->yc_box->value();
    center.z = ui->zc_box->value();
    
    request_t request;
    request.cmd = SET_CENTER;
    request.center = center;
    perform_cmd(request);
    
    draw_model();
}

void MainWindow::on_yc_box_editingFinished()
{
    if (!use_input_center || !ui->move_btn->isEnabled())
        return;
        
    point_t center;
    center.x = ui->xc_box->value();
    center.y = ui->yc_box->value();
    center.z = ui->zc_box->value();
    
    request_t request;
    request.cmd = SET_CENTER;
    request.center = center;
    perform_cmd(request);
    
    draw_model();
}

void MainWindow::on_zc_box_editingFinished()
{
    if (!use_input_center || !ui->move_btn->isEnabled())
        return;
        
    point_t center;
    center.x = ui->xc_box->value();
    center.y = ui->yc_box->value();
    center.z = ui->zc_box->value();
    
    request_t request;
    request.cmd = SET_CENTER;
    request.center = center;
    perform_cmd(request);
    
    draw_model();
}


void MainWindow::on_width_box_valueChanged(int value)
{
    width = value;
    if (ui->move_btn->isEnabled())
        draw_model();
}

void MainWindow::on_angle_box_valueChanged(double value)
{
    angle = value;
    if (ui->move_btn->isEnabled())
        draw_model();
}