#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog> 
#include <QMessageBox>
#include <QColor>

#include "exit_code.h"
#include "cmd_manager.h"
#include "file.h"
#include "model.h"
#include "model_draw.h"

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QColor color;
    int width;
    double angle;
    bool use_input_center;

    void update_btns_state();
    void clean_input_boxes();
    exit_code_t draw_model();

private slots:
    void on_move_btn_clicked();
    void on_rotate_btn_clicked();
    void on_scale_btn_clicked();
    void on_open_file_btn_clicked();
    void on_save_to_file_btn_clicked();
    void on_color_btn_clicked();
    void on_input_center_radio_btn_clicked();
    void on_xc_box_editingFinished();
    void on_yc_box_editingFinished();
    void on_zc_box_editingFinished();
    void on_width_box_valueChanged(int value);
    void on_angle_box_valueChanged(double value);
};
#endif // MAINWINDOW_H
