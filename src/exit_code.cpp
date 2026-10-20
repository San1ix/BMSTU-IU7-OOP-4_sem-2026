#include "exit_code.h"

void show_err_msg(const exit_code_t rc, QWidget *parent)
{
    switch(rc)
    {
        case RC_OK:
            break;
        case RC_FAIL_FILE_LOAD:
            QMessageBox::critical(parent, "Ошибка работы с файлом", "Не получается открыть файл");
            break;
        case RC_FAIL_FILE_CONTENT:
            QMessageBox::critical(parent, "Ошибка работы с файлом", "Невалидные данные");
            break;
        case RC_FAIL_EMPTY_FILE:
            QMessageBox::critical(parent, "Ошибка работы с файлом", "Пустой файл");
            break;
        case RC_FAIL_NO_POINTS:
            QMessageBox::critical(parent, "Ошибка работы с данными", "Нет точек");
            break;
        case RC_FAIL_NO_EDGES:
            QMessageBox::critical(parent, "Ошибка работы с данными", "Нет ребер");
            break;
        case RC_FAIL_MEM:
            QMessageBox::critical(parent, "Ошибка работы с памятью", "Не получается выделить память");
            break;
        case RC_FAIL_RANGE:
            QMessageBox::critical(parent, "Ошибка работы с данными", "Выход за пределы допустимых значений");
            break;
        case RC_FAIL_INVALID_PARAMS:
            QMessageBox::critical(parent, "Ошибка работы с моделью", "Переданы некорректные параметры для преобразований");
            break;
        case RC_FAIL_MODEL_NOT_LOADED:
            QMessageBox::critical(parent, "Ошибка работы с моделью", "Модель не загружена");
            break;
        case RC_FAIL_SCENE_NOT_LOADED:
            QMessageBox::critical(parent, "Ошибка работы с холстом", "Холст не загружен");
            break;
        case RC_FAIL_UNKNOWN_CMD:
            QMessageBox::critical(parent, "Ошибка работы с моделью", "Неизвестная команда");
            break;
        case RC_FAIL_SAVE_MODEL:
            QMessageBox::critical(parent, "Ошибка работы с файлом", "Не удалось сохранить модель");
            break;
    }
}