#include "actions.h"
#include <QDebug>


typedef void (*transform_func_t)(point_t *point, const params_t *params, const point_t *center);

static exit_code_t transform_model(model_t *model, transform_func_t transform_func, const params_t *params);
static void move_point(point_t *point, const params_t *params, const point_t *center);
static void rotate_point(point_t *point, const params_t *params, const point_t *center);
static void scale_point(point_t *point, const params_t *params, const point_t *center);
static void rotate_point_x(point_t *point, const params_t *params, const point_t *center);
static void rotate_point_y(point_t *point, const params_t *params, const point_t *center);
static void rotate_point_z(point_t *point, const params_t *params, const point_t *center);

exit_code_t move_model(model_t *model, const params_t params)
{
    return transform_model(model, move_point, &params);
}

exit_code_t rotate_model(model_t *model, const params_t params)
{
    return transform_model(model, rotate_point, &params);
}

exit_code_t scale_model(model_t *model, const params_t params)
{
    if (params.x_param == 0 || params.y_param == 0 || params.z_param == 0)
        return RC_FAIL_INVALID_PARAMS;

    return transform_model(model, scale_point, &params);
}

static exit_code_t transform_model(model_t *model, transform_func_t transform_func, const params_t *params)
{
    exit_code_t rc = RC_OK;

    if (!is_loaded(model))
        rc = RC_FAIL_MODEL_NOT_LOADED;
    else if (!transform_func || !params)
        rc = RC_FAIL_INVALID_PARAMS;
    else 
    {
        point_t center;
        get_center(&model->center, &center);

        int count = get_points_count(model->points);
        for (int i = 0; i < count; i++)
        {
            point_t *point = get_point(model->points, i);
            transform_func(point, params, &center);
        }
    }

    return rc;
}

static void move_point(point_t *point, const params_t *params, const point_t *center)
{
    if (point && params)
    {
        (void)center;
        point->x += params->x_param;
        point->y += params->y_param;
        point->z += params->z_param;
    }
}

static void rotate_point(point_t *point, const params_t *params, const point_t *center)
{
    rotate_point_x(point, params, center);
    rotate_point_y(point, params, center);
    rotate_point_z(point, params, center);
}

static void scale_point(point_t *point, const params_t *params, const point_t *center)
{
    if (point && center && params)
    {
        double x = point->x - center->x;
        double y = point->y - center->y;
        double z = point->z - center->z;

        point->x = center->x + x * params->x_param;
        point->y = center->y + y * params->y_param;
        point->z = center->z + z * params->z_param;
    }
}

static void rotate_point_x(point_t *point, const params_t *params, const point_t *center)
{
    if (point && center && params)
    {
        double y = point->y - center->y;
        double z = point->z - center->z;
        double rad = params->x_param * M_PI / 180.0;
        double cos_a = cos(rad);
        double sin_a = sin(rad);

        point->y = center->y + y * cos_a - z * sin_a;
        point->z = center->z + y * sin_a + z * cos_a;
    }
}

static void rotate_point_y(point_t *point, const params_t *params, const point_t *center)
{
    if (point && center && params)
    {
        double x = point->x - center->x;
        double z = point->z - center->z;
        double rad = params->y_param * M_PI / 180.0;
        double cos_a = cos(rad);
        double sin_a = sin(rad);

        point->x = center->x + x * cos_a + z * sin_a;
        point->z = center->z - x * sin_a + z * cos_a;
    }
}
static void rotate_point_z(point_t *point, const params_t *params, const point_t *center)
{
    if (point && center && params)
    {
        double x = point->x - center->x;
        double y = point->y - center->y;
        double rad = params->z_param * M_PI / 180.0;
        double cos_a = cos(rad);
        double sin_a = sin(rad);

        point->x = center->x + x * cos_a - y * sin_a;
        point->y = center->y + x * sin_a + y * cos_a;
    }
}
