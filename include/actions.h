#ifndef ACTIONS_H
#define ACTIONS_H

#include <QGraphicsScene>
#include <cmath>

#include "exit_code.h"
#include "model.h"
#include "center.h"

typedef struct 
{
    double x_param;
    double y_param;
    double z_param;
} params_t;

typedef struct
{
    QGraphicsScene *scene;
    double height;
    double width;
} canvas_t;

exit_code_t move_model(model_t *model, const params_t params);
exit_code_t rotate_model(model_t *model, const params_t params);
exit_code_t scale_model(model_t *model, const params_t params);

#endif