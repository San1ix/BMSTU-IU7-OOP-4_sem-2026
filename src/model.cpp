#include "model.h"

void init_model(model_t *model)
{
    if (model)
    {
        model->points = NULL;
        model->edges = NULL;
        init_center(&model->center);
    }
}

void free_model(model_t *model)
{
    if (model)
    {
        if (model->edges)
            free_edges(model->edges);
        if (model->points)
            free_points(model->points);
        init_model(model);
    }
}

exit_code_t update_model_center(model_t *model)
{
    exit_code_t rc = RC_OK;

    if (!is_loaded(model))
        rc = RC_FAIL_MODEL_NOT_LOADED;
    else
        rc = calc_center(&model->center, model->points);

    return rc;
}

void set_model_center(model_t *model, const point_t *center)
{
    if (model && center)
        set_center(&model->center, center);
}

int is_loaded(const model_t *model)
{
    int loaded = 0;

    if (model && is_points_valid(model->points) && is_edges_valid(model->edges))
        loaded = 1;

    return loaded;
}
