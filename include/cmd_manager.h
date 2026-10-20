#ifndef CMD_MANAGER_H
#define CMD_MANAGER_H

#include "exit_code.h"
#include "model.h"
#include "file.h"
#include "model_draw.h"
#include "actions.h"

typedef enum 
{
    LOAD_MODEL,
    SAVE_MODEL,
    DRAW_MODEL,
    MOVE_MODEL,
    ROTATE_MODEL,
    SCALE_MODEL,
    SET_CENTER,
    UPDATE_CENTER,
    CLEAN_MODEL,
    CHECK_MODEL
} command_t;

typedef struct
{
    command_t cmd;
    canvas_t scene;
    const draw_params_t *draw_params;
    const char *filename;
    params_t transformation;
    point_t center;
} request_t;

exit_code_t perform_cmd(request_t &request);

#endif