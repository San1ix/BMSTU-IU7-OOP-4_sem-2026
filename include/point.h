#ifndef POINT_H
#define POINT_H

typedef struct
{
    double x;
    double y;
    double z;
} point_t;

typedef struct
{
    point_t *data;
    int points_count;
} points_t;

points_t* alloc_points(const int count);
void free_points(points_t *points);

void set_point(point_t *dst, const point_t *src);
point_t* get_point(const points_t *points, const int idx);
int get_points_count(const points_t *points);

int is_points_valid(const points_t *points);

#endif
