#ifndef EXIT_CODE_H
#define EXIT_CODE_H

#include <QMessageBox>
#include <QWidget>

typedef enum
{
    RC_OK = 0,

    RC_FAIL_FILE_LOAD,
    RC_FAIL_FILE_CONTENT,
    RC_FAIL_EMPTY_FILE,

    RC_FAIL_NO_POINTS,
    RC_FAIL_NO_EDGES,

    RC_FAIL_MEM,
    RC_FAIL_RANGE,
    RC_FAIL_INVALID_PARAMS,

    RC_FAIL_MODEL_NOT_LOADED,
    RC_FAIL_SCENE_NOT_LOADED,
    RC_FAIL_UNKNOWN_CMD,
    RC_FAIL_SAVE_MODEL
} exit_code_t;

void show_err_msg(const exit_code_t rc, QWidget *parent);

#endif
