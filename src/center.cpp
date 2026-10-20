#include "center.h"

void init_center(point_t *center)
{
    if (center)
    {
        center->x = 0;
        center->y = 0;
        center->z = 0;
    }
}

void set_center(point_t *center, const point_t *point)
{
    if (center && point)
        set_point(center, point);
}

void get_center(const point_t *center, point_t *point)
{
    if (center && point)
        set_point(point, center);
}


exit_code_t calc_center(point_t *center, const points_t *points)
{
    exit_code_t rc = RC_OK;

    if (!center || !is_points_valid(points))
        rc = RC_FAIL_NO_POINTS;
    else
    {
        double x_sum = 0;
        double y_sum = 0;
        double z_sum = 0;
        int count = get_points_count(points);

        for (int i = 0; i < count; i++)
        {
            point_t *point = get_point(points, i);
            if (point)
            {
                x_sum += point->x;
                y_sum += point->y;
                z_sum += point->z;
            }
        }

        center->x = x_sum / count;
        center->y = y_sum / count;
        center->z = z_sum / count;
    }
    
    return rc;
}
