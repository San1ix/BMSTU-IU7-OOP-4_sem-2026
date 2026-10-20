#include "point.h"

#include <stdlib.h>

static point_t* get_point_from_array(point_t *points, const int count, const int idx);

points_t* alloc_points(const int count)
{
    if (count < 1)
        return NULL;

    points_t *points = (points_t*)malloc(sizeof(points_t));
    if (points)
    {
        point_t *data = (point_t*)calloc(count, sizeof(point_t));
        if (!data)
            free(points);
        else
        {
            points->data = data;
            points->points_count = count;
        }
    }

    return points;
}

void free_points(points_t *points)
{
    if (points)
    {
        if (points->data)
            free(points->data);
        free(points);
    }
}

void set_point(point_t *dst, const point_t *src)
{
    if (dst && src)
    {
        dst->x = src->x;
        dst->y = src->y;
        dst->z = src->z;
    }
}

point_t* get_point(const points_t *points, const int idx)
{
    point_t *point = NULL;

    if (points && points->data)
        point = get_point_from_array(points->data, points->points_count, idx);

    return point;
}

static point_t* get_point_from_array(point_t *points, const int count, const int idx)
{
    point_t *point = NULL;
    
    if (idx < count && idx > -1)
        point = &points[idx];

    return point;
}

int get_points_count(const points_t *points)
{
    int count = 0;
    
    if (points && points->data)
        count = points->points_count;

    return count;
}

int is_points_valid(const points_t *points)
{
    int is_valid = 0;

    if (points && points->data && points->points_count > 0)
        is_valid = 1;

    return is_valid;
}

