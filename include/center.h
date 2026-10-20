#ifndef CENTER_H
#define CENTER_H

#include "point.h"
#include "exit_code.h"

void init_center(point_t *center);
void set_center(point_t *center, const point_t *point);
void get_center(const point_t *center, point_t *point);

exit_code_t calc_center(point_t *center, const points_t *points);

#endif