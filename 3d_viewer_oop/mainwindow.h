#pragma once
#include <QMainWindow>
#include "ui_mainwindow.h"
#include "facade.h"
#include "memento/caretaker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_browse_btn_clicked();
    void on_load_model_btn_clicked();
    void on_show_invisible_edges_check_toggled(bool);

    void on_add_viewer_btn_clicked();
    void on_set_active_btn_clicked();
    void on_delete_btn_clicked();
    void on_move_viewer_left_btn_clicked();
    void on_move_viewer_right_btn_clicked();
    void on_move_viewer_up_btn_clicked();
    void on_move_viewer_down_btn_clicked();
    void on_rotate_viewer_btn_clicked();

    void on_delete_selected_btn_clicked();
    void on_move_btn_clicked();
    void on_rotate_btn_clicked();
    void on_scale_btn_clicked();

    void on_set_center_btn_clicked();

    void on_add_composite_btn_clicked();
    void on_del_composite_btn_clicked();
    void on_move_composite_btn_clicked();
    void on_rotate_composite_btn_clicked();
    void on_scale_composite_btn_clicked();

    void on_undo_btn_clicked();

private:
    void draw_scene();
    void update_viewers_list();
    void update_objects_list();
    void update_composite_tab();
    void log(const QString& message);

    Ui::MainWindow* ui;
    Facade facade;
    Caretaker caretaker;

    static constexpr int scene_width = 500;
    static constexpr int scene_height = 500;
};