#include "model_draw.h"

static void draw_edges(const points_t *points, const edges_t *edges, QGraphicsScene *scene, const int width, const int height, const pen_params_t *params);
static void draw_center(const point_t *center, QGraphicsScene *scene, const int width, const int height, const pen_params_t *params);
static void draw_edge(const point_t *point_1, const point_t *point_2, QGraphicsScene *scene, const int width, const int height, const QPen &pen, const double angle);
static QPointF project_to_2d(const point_t *point, const int width, const int height, const double angle);

exit_code_t draw_model(model_t *model, canvas_t canvas, const draw_params_t *params)
{
    exit_code_t rc = RC_OK;

    if (!is_loaded(model))
        rc = RC_FAIL_MODEL_NOT_LOADED;
    else if (!canvas.scene)
        rc = RC_FAIL_SCENE_NOT_LOADED;
    else if (!params)
        rc = RC_FAIL_INVALID_PARAMS;
    else
    {
        canvas.scene->clear();
        draw_edges(model->points, model->edges, canvas.scene, canvas.width, canvas.height, &params->edge_params);
        draw_center(&model->center, canvas.scene, canvas.width, canvas.height, &params->center_params);
    }

    return rc;
}

static void draw_center(const point_t *center, QGraphicsScene *scene, const int width, const int height, const pen_params_t *params)
{
    QPen pen(params->color);
    pen.setWidth(params->width);
    
    QPointF center_2d = project_to_2d(center, width, height, params->angle);
    
    int size = params->width;
    QGraphicsLineItem *line1 = new QGraphicsLineItem(center_2d.x() - size, center_2d.y(), center_2d.x() + size, center_2d.y());
    QGraphicsLineItem *line2 = new QGraphicsLineItem(center_2d.x(), center_2d.y() - size, center_2d.x(), center_2d.y() + size);

    line1->setPen(pen);
    scene->addItem(line1);
    
    line2->setPen(pen);
    scene->addItem(line2);
}

static void draw_edges(const points_t *points, const edges_t *edges, QGraphicsScene *scene, const int width, const int height, const pen_params_t *params)
{
    QPen pen(params->color);
    pen.setWidth(params->width);

    int count = get_edges_count(edges);
    for (int i = 0; i < count; i++)
    {
        edge_t *edge = get_edge(edges, i);
        if (edge)
        {
            point_t *point_1 = get_point(points, edge->point_1_idx);
            point_t *point_2 = get_point(points, edge->point_2_idx);

            draw_edge(point_1, point_2, scene, width, height, pen, params->angle);
        }
    }
}


static void draw_edge(const point_t *point_1, const point_t *point_2, QGraphicsScene *scene, const int width, const int height, const QPen &pen, const double angle)
{
    if (point_1 && point_2)
    {
        QPointF point_1_2d = project_to_2d(point_1, width, height, angle);
        QPointF point_2_2d = project_to_2d(point_2, width, height, angle);

        QGraphicsLineItem *line = new QGraphicsLineItem(point_1_2d.x(), point_1_2d.y(), point_2_2d.x(), point_2_2d.y());
        line->setPen(pen);
        scene->addItem(line);
    }
}

static QPointF project_to_2d(const point_t *point, const int width, const int height, const double angle)
{
    QPointF res(0, 0);

    double rad = angle * M_PI / 180.0;
    double cos_angle = std::cos(rad);
    double sin_angle = std::sin(rad);

    double x = point->x + point->z * cos_angle * 0.5;
    double y = point->y + point->z * sin_angle * 0.5;

    x = width / 2.0 + x;
    y = height / 2.0 - y;

    res.setX(x);
    res.setY(y);

    return res;
}
