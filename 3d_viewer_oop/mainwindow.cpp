#include "mainwindow.h"
#include "command/load_list_model.h"
#include "command/load_matrix_model.h"
#include "command/add_obj.h"
#include "command/del_obj.h"
#include "command/move_obj.h"
#include "command/rotate_obj.h"
#include "command/scale_obj.h"
#include "command/add_viewer.h"
#include "command/del_viewer.h"
#include "command/move_viewer.h"
#include "command/rotate_viewer.h"
#include "command/set_viewer.h"
#include "command/clear_scene.h"
#include "command/draw_scene.h"
#include "command/set_center.h"
#include "command/make_composite.h"
#include "command/decompose_composite.h"
#include "manager/load_manager.h"
#include "manager/scene_manager.h"
#include "manager/viewer_manager.h"
#include "manager/draw_manager.h"
#include "math/point.h"
#include "facade/facade.h"
#include "carcass_model.h"
#include "carcass_model_impl.h"
#include "composite.h"
#include "viewer_impl_v1.h"
#include <QFileDialog>
#include <QMessageBox>
#include <set>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->setScene(new QGraphicsScene());
    ui->canvas->scene()->setSceneRect(0, 0, scene_width, scene_height);
    update_viewers_list();
    update_objects_list();
    update_composite_tab();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::log(const QString& message) { ui->logs->append(message); }

void MainWindow::draw_scene()
{
    ui->canvas->scene()->clear();
    ui->canvas->scene()->setSceneRect(0, 0, scene_width, scene_height);
    auto dm = DrawManager::get_instance();
    dm->set_drawer<Facade::DrawerCreator>(ui->canvas->scene());
    DrawScene cmd(ui->show_invisible_edges_check->isChecked());
    facade.execute(cmd);
    ui->canvas->viewport()->update();
}

void MainWindow::update_viewers_list()
{
    auto vm = ViewerManager::get_instance();
    auto ids = vm->get_viewer_ids();
    auto active = vm->get_active_viewer();
    auto main_id = active ? active->get_id() : 0;
    ui->viewers_list->setRowCount(static_cast<int>(ids.size()));
    for (int i = 0; i < static_cast<int>(ids.size()); ++i)
    {
        auto viewer = vm->get_viewer(ids[i]);
        if (!viewer) continue;
        auto impl = std::dynamic_pointer_cast<ViewerImplV1>(viewer->get_impl());
        Point pos = impl ? impl->get_position() : Point();
        ui->viewers_list->setItem(i, 0, new QTableWidgetItem(QString::number(ids[i])));
        ui->viewers_list->setItem(i, 1, new QTableWidgetItem(ids[i] == main_id ? "V" : ""));
        ui->viewers_list->setItem(i, 2, new QTableWidgetItem(QString::number(pos.get_x(), 'f', 2)));
        ui->viewers_list->setItem(i, 3, new QTableWidgetItem(QString::number(pos.get_y(), 'f', 2)));
        ui->viewers_list->setItem(i, 4, new QTableWidgetItem(QString::number(pos.get_z(), 'f', 2)));
    }
}

void MainWindow::update_objects_list()
{
    auto sm = SceneManager::get_instance();

    std::function<void(std::shared_ptr<BaseObj>, std::vector<std::shared_ptr<BaseObj>>&)> collect;
    collect = [&](std::shared_ptr<BaseObj> obj, std::vector<std::shared_ptr<BaseObj>>& out)
    {
        if (!obj) return;
        if (obj->is_composite())
        {
            for (auto it = obj->begin(); it != obj->end(); ++it)
                collect(*it, out);
        }
        else if (obj->is_visible())
        {
            out.push_back(obj);
        }
    };

    std::vector<std::shared_ptr<BaseObj>> all_models;
    for (auto id : sm->get_object_ids())
    {
        auto it = sm->get_object(id);
        if (it != sm->get_scene().end())
            collect(*it, all_models);
    }

    ui->objects_list->setRowCount(static_cast<int>(all_models.size()));
    for (int i = 0; i < static_cast<int>(all_models.size()); ++i)
    {
        auto obj = all_models[i];
        auto id = obj->get_id();
        ui->objects_list->setItem(i, 0, new QTableWidgetItem(QString::number(id)));
        auto center = obj->get_center();
        ui->objects_list->setItem(i, 1, new QTableWidgetItem(
            QString("(%1, %2, %3)").arg(center.get_x(), 0, 'f', 1)
                                   .arg(center.get_y(), 0, 'f', 1)
                                   .arg(center.get_z(), 0, 'f', 1)));
        ui->objects_list->setItem(i, 2, new QTableWidgetItem("Carcass"));
        int pts = 0;
        if (auto cm = std::dynamic_pointer_cast<CarcassModel>(obj))
        {
            auto impl = cm->get_impl();
            if (auto cimpl = std::dynamic_pointer_cast<CarcassModelImpl>(impl))
                pts = static_cast<int>(cimpl->get_structure()->get_points().size());
        }
        ui->objects_list->setItem(i, 4, new QTableWidgetItem(pts > 0 ? QString::number(pts) : "-"));
        ui->objects_list->setItem(i, 3, new QTableWidgetItem(obj->is_visible() ? "V" : "X"));
    }
}

void MainWindow::update_composite_tab()
{
    auto sm = SceneManager::get_instance();
    auto vm = ViewerManager::get_instance();
    auto obj_ids = sm->get_object_ids();
    auto viewer_ids = vm->get_viewer_ids();

    std::set<std::size_t> ids_in_composites;
    for (auto id : obj_ids)
    {
        auto it = sm->get_object(id);
        if (it == sm->get_scene().end()) continue;
        if ((*it)->is_composite())
            for (auto cid : std::dynamic_pointer_cast<Composite>(*it)->get_child_ids())
                ids_in_composites.insert(cid);
    }

    std::vector<std::pair<std::size_t, QString>> root_items;
    for (auto id : obj_ids)
    {
        if (ids_in_composites.count(id)) continue;
        auto it = sm->get_object(id);
        if (it == sm->get_scene().end()) continue;
        QString type;
        if ((*it)->is_composite()) type = "Composite";
        else if (!(*it)->is_visible()) type = "Viewer";
        else type = "Carcass";
        root_items.push_back({id, type});
    }

    ui->tableWidget->setRowCount(static_cast<int>(root_items.size()));
    for (int i = 0; i < static_cast<int>(root_items.size()); ++i)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(root_items[i].first)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(root_items[i].second));
        auto it = sm->get_object(root_items[i].first);
        if (it != sm->get_scene().end() && (*it)->is_composite())
        {
            auto comp = std::dynamic_pointer_cast<Composite>(*it);
            if (comp)
            {
                auto child_ids = comp->get_child_ids();
                QStringList list;
                for (auto cid : child_ids) list << QString::number(cid);
                ui->tableWidget->setItem(i, 2, new QTableWidgetItem(list.join(", ")));
            }
        }
        else
        {
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(""));
        }
    }
}

void MainWindow::on_browse_btn_clicked()
{
    auto filename = QFileDialog::getOpenFileName(this, "Select model file", "./data",
                                                  "Model files (*.txt *.obj);;All files (*)");
    if (!filename.isEmpty()) ui->path_to_file->setText(filename);
}

void MainWindow::on_load_model_btn_clicked()
{
    try
    {
        auto sm = SceneManager::get_instance();
        caretaker.add(sm->create_memento());
        auto filename = ui->path_to_file->text().toStdString();
        auto lm = LoadManager::get_instance();
        lm->open_file(filename);
        if (ui->list_mode->isChecked())
        {
            LoadListModelCmd cmd;
            facade.execute(cmd);
        }
        else
        {
            LoadMatrixModelCmd cmd;
            facade.execute(cmd);
        }
        auto model = lm->get_loaded_model();
        lm->close_file();
        if (model)
        {
            AddObj add_cmd(model);
            facade.execute(add_cmd);
        }
        update_objects_list();
        update_composite_tab();
        draw_scene();
        log(QString("Loaded: %1").arg(filename.c_str()));
    }
    catch (const std::exception& e) { QMessageBox::critical(this, "Error", e.what()); }
}

void MainWindow::on_show_invisible_edges_check_toggled(bool) { draw_scene(); }

void MainWindow::on_add_viewer_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    double x = ui->add_viewer_x->value(), y = ui->add_viewer_y->value(), z = ui->add_viewer_z->value();
    AddViewer cmd(Point(x, y, z));
    facade.execute(cmd);
    update_viewers_list();
    update_composite_tab();
    draw_scene();
    log(QString("Viewer added at (%1, %2, %3)").arg(x).arg(y).arg(z));
}

void MainWindow::on_set_active_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    auto selected = ui->viewers_list->selectedItems();
    if (selected.isEmpty()) return;
    SetViewer cmd(selected.first()->text().toULongLong());
    facade.execute(cmd);
    update_viewers_list();
    draw_scene();
}

void MainWindow::on_delete_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    auto selected = ui->viewers_list->selectedItems();
    if (selected.isEmpty()) return;
    DelViewer cmd(selected.first()->text().toULongLong());
    facade.execute(cmd);
    update_viewers_list();
    update_objects_list();
    update_composite_tab();
    draw_scene();
}

void MainWindow::on_move_viewer_left_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    auto selected = ui->viewers_list->selectedItems();
    if (selected.isEmpty()) return;
    double step = ui->doubleSpinBox_2->value();
    MoveViewer cmd(selected.first()->text().toULongLong(), -step, 0, 0);
    facade.execute(cmd);
    update_viewers_list();
    draw_scene();
}

void MainWindow::on_move_viewer_right_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    auto selected = ui->viewers_list->selectedItems();
    if (selected.isEmpty()) return;
    double step = ui->doubleSpinBox_2->value();
    MoveViewer cmd(selected.first()->text().toULongLong(), step, 0, 0);
    facade.execute(cmd);
    update_viewers_list();
    draw_scene();
}

void MainWindow::on_move_viewer_up_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    auto selected = ui->viewers_list->selectedItems();
    if (selected.isEmpty()) return;
    double step = ui->doubleSpinBox_2->value();
    MoveViewer cmd(selected.first()->text().toULongLong(), 0, -step, 0);
    facade.execute(cmd);
    update_viewers_list();
    draw_scene();
}

void MainWindow::on_move_viewer_down_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    auto selected = ui->viewers_list->selectedItems();
    if (selected.isEmpty()) return;
    double step = ui->doubleSpinBox_2->value();
    MoveViewer cmd(selected.first()->text().toULongLong(), 0, step, 0);
    facade.execute(cmd);
    update_viewers_list();
    draw_scene();
}

void MainWindow::on_rotate_viewer_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    auto selected = ui->viewers_list->selectedItems();
    if (selected.isEmpty()) return;
    double angle = ui->doubleSpinBox->value() * M_PI / 180.0;
    QString axis = ui->comboBox->currentText();
    double ox = 0, oy = 0, oz = 0;
    if (axis == "X") ox = angle;
    else if (axis == "Y") oy = angle;
    else if (axis == "Z") oz = angle;
    RotateViewer cmd(selected.first()->text().toULongLong(), ox, oy, oz);
    facade.execute(cmd);
    update_viewers_list();
    draw_scene();
}

void MainWindow::on_delete_selected_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    auto selected = ui->objects_list->selectedItems();
    for (auto* item : selected)
    {
        if (item->column() != 0) continue;
        DelObj cmd(item->text().toULongLong());
        facade.execute(cmd);
    }
    update_objects_list();
    update_composite_tab();
    update_viewers_list();
    draw_scene();
}

void MainWindow::on_move_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    auto selected = ui->objects_list->selectedItems();
    double dx = ui->dx->value(), dy = ui->dy->value(), dz = ui->dz->value();
    for (auto* item : selected)
    {
        if (item->column() != 0) continue;
        MoveObj cmd(item->text().toULongLong(), dx, dy, dz);
        facade.execute(cmd);
    }
    draw_scene();
}

void MainWindow::on_rotate_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    auto selected = ui->objects_list->selectedItems();
    double ox = ui->x_angle->value() * M_PI / 180.0;
    double oy = ui->y_angle->value() * M_PI / 180.0;
    double oz = ui->z_angle->value() * M_PI / 180.0;
    for (auto* item : selected)
    {
        if (item->column() != 0) continue;
        RotateObj cmd(item->text().toULongLong(), ox, oy, oz);
        facade.execute(cmd);
    }
    draw_scene();
}

void MainWindow::on_scale_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    auto selected = ui->objects_list->selectedItems();
    double kx = ui->kx->value(), ky = ui->ky->value(), kz = ui->kz->value();
    for (auto* item : selected)
    {
        if (item->column() != 0) continue;
        ScaleObj cmd(item->text().toULongLong(), kx, ky, kz);
        facade.execute(cmd);
    }
    draw_scene();
}

void MainWindow::on_set_center_btn_clicked()
{
    SetCenter cmd(ui->x_center->value(), ui->y_center->value(), ui->z_center->value());
    facade.execute(cmd);
    draw_scene();
    log("Center set");
}

void MainWindow::on_add_composite_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    std::vector<std::size_t> ids;
    for (auto* item : ui->tableWidget->selectedItems())
        if (item->column() == 0)
            ids.push_back(item->text().toULongLong());
    MakeComposite cmd(ids);
    facade.execute(cmd);
    update_objects_list();
    update_composite_tab();
    draw_scene();
    log("Composite created");
}

void MainWindow::on_del_composite_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    for (auto* item : ui->tableWidget->selectedItems())
    {
        if (item->column() != 0) continue;
        DecomposeComposite cmd(item->text().toULongLong());
        facade.execute(cmd);
    }
    update_objects_list();
    update_composite_tab();
    draw_scene();
}

void MainWindow::on_move_composite_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    double dx = ui->dx_2->value(), dy = ui->dy_2->value(), dz = ui->dz_2->value();
    for (auto* item : ui->tableWidget->selectedItems())
    {
        if (item->column() != 0) continue;
        MoveObj cmd(item->text().toULongLong(), dx, dy, dz);
        facade.execute(cmd);
    }
    draw_scene();
}

void MainWindow::on_rotate_composite_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    double ox = ui->x_angle_2->value() * M_PI / 180.0;
    double oy = ui->y_angle_2->value() * M_PI / 180.0;
    double oz = ui->z_angle_2->value() * M_PI / 180.0;
    for (auto* item : ui->tableWidget->selectedItems())
    {
        if (item->column() != 0) continue;
        RotateObj cmd(item->text().toULongLong(), ox, oy, oz);
        facade.execute(cmd);
    }
    draw_scene();
}

void MainWindow::on_scale_composite_btn_clicked()
{
    auto sm = SceneManager::get_instance();
    caretaker.add(sm->create_memento());
    double kx = ui->kx_2->value(), ky = ui->ky_2->value(), kz = ui->kz_2->value();
    for (auto* item : ui->tableWidget->selectedItems())
    {
        if (item->column() != 0) continue;
        ScaleObj cmd(item->text().toULongLong(), kx, ky, kz);
        facade.execute(cmd);
    }
    draw_scene();
}

void MainWindow::on_undo_btn_clicked()
{
    auto memento = caretaker.pop();
    if (!memento) { log("Nothing to undo"); return; }
    SceneManager::get_instance()->restore_memento(memento);
    update_objects_list();
    update_viewers_list();
    update_composite_tab();
    draw_scene();
    log("Undo done");
}