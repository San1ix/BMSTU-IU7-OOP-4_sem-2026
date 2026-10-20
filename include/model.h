#ifndef MODEL_H
#define MODEL_H

#include "exit_code.h"
#include "point.h"
#include "edge.h"
#include "center.h"

using namespace std;

typedef struct
{
    points_t *points;
    edges_t *edges;
    point_t center;
} model_t;


void init_model(model_t *model);
void free_model(model_t *model);

exit_code_t update_model_center(model_t *model);
void set_model_center(model_t *model, const point_t *center); 

int is_loaded(const model_t *model);

#endif