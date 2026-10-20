#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QPen>
#include <QColor>
#include <cmath>

#include "model.h"
#include "exit_code.h"
#include "actions.h"

typedef struct
{
    QColor color;
    int width;
    double angle;
} pen_params_t;

typedef struct
{
    pen_params_t edge_params;
    pen_params_t center_params;
} draw_params_t;

exit_code_t draw_model(model_t *model, canvas_t canvas, const draw_params_t *params_t);

#endif