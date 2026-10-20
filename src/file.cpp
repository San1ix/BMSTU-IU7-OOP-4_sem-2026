#include "file.h"

static int count_nums_in_line(const char *str);
static exit_code_t read_int_from_file(FILE *file, int *value);
static exit_code_t read_point(FILE *file, point_t *point);
static exit_code_t read_edge(FILE *file, edge_t *edge, const int max_idx);
static int has_extra_data(FILE *file);
static exit_code_t read_all_points(FILE *file, points_t *points, const int points_count);
static exit_code_t read_all_edges(FILE *file, edges_t *edges, const int edges_count, const int max_idx);

static exit_code_t read_points_section(FILE *file, model_t *model, int *points_count);
static exit_code_t read_edges_section(FILE *file, model_t *model, int *edges_count);

static exit_code_t write_point(FILE *file, const point_t *point);
static exit_code_t write_edge(FILE *file, const edge_t *edge);
static exit_code_t write_all_points(FILE *file, const points_t *points);
static exit_code_t write_all_edges(FILE *file, const edges_t *edges);

exit_code_t load_model_from_file(model_t *model, const char *filename)
{
    if (!model || !filename)
        return RC_FAIL_FILE_LOAD;

    exit_code_t rc = RC_OK;

    int points_count = 0;
    int edges_count = 0;

    FILE *file = fopen(filename, "r");
    if (!file)
        rc = RC_FAIL_FILE_LOAD;
    else
    {
        rc = read_points_section(file, model, &points_count);
        if (rc == RC_OK)
        {
            rc = read_edges_section(file, model, &edges_count);
            if (rc == RC_OK && has_extra_data(file))
                rc = RC_FAIL_FILE_CONTENT;
        }

        fclose(file);
    }

    if (rc == RC_OK)
    {
        if (!is_loaded(model))
            rc = RC_FAIL_MODEL_NOT_LOADED;
        else
            update_model_center(model);
    }

    return rc;
}

exit_code_t save_model_to_file(const model_t *model, const char *filename)
{
    if (!model || !filename)
        return RC_FAIL_SAVE_MODEL;

    if (!is_loaded(model))
        return RC_FAIL_MODEL_NOT_LOADED;

    exit_code_t rc = RC_OK;

    FILE *file = fopen(filename, "w");
    if (!file)
        rc = RC_FAIL_SAVE_MODEL;
    else
    {
        rc = write_all_points(file, model->points);
        if (rc == RC_OK)
            rc = write_all_edges(file, model->edges);

        fclose(file);
    }

    return rc;
}



static exit_code_t read_points_section(FILE *file, model_t *model, int *points_count)
{
    exit_code_t rc = read_int_from_file(file, points_count);

    if (rc == RC_OK)
    {
        model->points = alloc_points(*points_count);
        if (!model->points)
            rc = RC_FAIL_MEM;
        else
        {
            rc = read_all_points(file, model->points, *points_count);
            if (rc != RC_OK)
            {
                free_points(model->points);
                model->points = NULL;
            }
        }
    }

    return rc;
}

static exit_code_t read_edges_section(FILE *file, model_t *model, int *edges_count)
{
    exit_code_t rc = read_int_from_file(file, edges_count);

    if (rc == RC_OK)
    {
        model->edges = alloc_edges(*edges_count);
        if (!model->edges)
            rc = RC_FAIL_MEM;
        else
        {
            int points_count = get_points_count(model->points);
            rc = read_all_edges(file, model->edges, *edges_count, points_count);
            if (rc != RC_OK)
            {
                free_edges(model->edges);
                model->edges = NULL;
            }
        }
    }

    return rc;
}

static int count_nums_in_line(const char *str)
{
    int count = 0;
    int in_num = 0;

    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++)
    {
        if (isspace(str[i]))
            in_num = 0;
        else if (!in_num)
        {
            in_num = 1;
            count++;
        }
    }

    return count;
}

static exit_code_t read_int_from_file(FILE *file, int *value)
{
    exit_code_t rc = RC_OK;

    char buf[MAX_LINE_LENGTH];

    if (fgets(buf, sizeof(buf), file) == NULL)
        rc = RC_FAIL_FILE_CONTENT;
    else
    {
        if (count_nums_in_line(buf) != 1)
            rc = RC_FAIL_FILE_CONTENT;
        else if (sscanf(buf, "%d", value) != 1 || *value <= 0)
            rc = RC_FAIL_FILE_CONTENT;
    }

    return rc;
}

static exit_code_t read_point(FILE *file, point_t *point)
{
    exit_code_t rc = RC_OK;

    char buf[MAX_LINE_LENGTH];

    if (fgets(buf, sizeof(buf), file) == NULL)
        rc = RC_FAIL_FILE_CONTENT;
    else
    {
        if (count_nums_in_line(buf) != 3)
            rc = RC_FAIL_FILE_CONTENT;
        else
        {    
            double x, y, z;
            if (sscanf(buf, "%lf %lf %lf", &x, &y, &z) != 3)
                rc = RC_FAIL_FILE_CONTENT; 
            else
            {
                point->x = x;
                point->y = y;
                point->z = z;
            }   
        }        
    }

    return rc;
}

static exit_code_t read_edge(FILE *file, edge_t *edge, const int max_idx)
{
    exit_code_t rc = RC_OK;

    char buf[MAX_LINE_LENGTH];
    int idx1;
    int idx2;

    if (fgets(buf, sizeof(buf), file) == NULL)
        rc = RC_FAIL_FILE_CONTENT;
    else
    {
        if (count_nums_in_line(buf) != 2)
            rc = RC_FAIL_FILE_CONTENT;
        else if (sscanf(buf, "%d %d", &idx1, &idx2) != 2)
            rc = RC_FAIL_FILE_CONTENT;
        else
        {
            if (idx1 < 0 || idx1 >= max_idx || idx2 < 0 || idx2 >= max_idx)
                rc = RC_FAIL_RANGE;
            else
            {
                edge->point_1_idx = idx1;
                edge->point_2_idx = idx2;
            }
        }
    }

    return rc;
}

static int has_extra_data(FILE *file)
{
    int has_extra = 0;
    char buf[MAX_LINE_LENGTH];
    long orig_pos = ftell(file);

    if (fgets(buf, sizeof(buf), file) != NULL)
        for (int i = 0; buf[i] != '\0' && !has_extra; i++)
            if (!isspace(buf[i]) && buf[i] != '\n')
                has_extra = 1;

    fseek(file, orig_pos, SEEK_SET);

    return has_extra;
}

static exit_code_t read_all_points(FILE *file, points_t *points, const int points_count)
{
    exit_code_t rc = RC_OK;

    for (int i = 0; i < points_count && rc == RC_OK; i++)
    {
        point_t new_point;
        rc = read_point(file, &new_point);
        if (rc == RC_OK)
        {
            point_t *dst = get_point(points, i);
            if (dst)
                set_point(dst, &new_point);
            else
                rc = RC_FAIL_RANGE;
        }
    }

    return rc;
}

static exit_code_t read_all_edges(FILE *file, edges_t *edges, const int edges_count, const int max_idx)
{
    exit_code_t rc = RC_OK;

    for (int i = 0; i < edges_count && rc == RC_OK; i++)
    {
        edge_t new_edge;
        rc = read_edge(file, &new_edge, max_idx);
        if (rc == RC_OK)
        {
            edge_t *dst = get_edge(edges, i);
            if (dst)
                set_edge(dst, &new_edge);
            else
                rc = RC_FAIL_RANGE;
        }
    }

    return rc;
}

static exit_code_t write_point(FILE *file, const point_t *point)
{
    exit_code_t rc = RC_OK;

    if (!point)
        rc = RC_FAIL_SAVE_MODEL;
    else
        fprintf(file, "%lf %lf %lf\n", point->x, point->y, point->z);

    return rc;
}

static exit_code_t write_edge(FILE *file, const edge_t *edge)
{
    exit_code_t rc = RC_OK;
    
    if (!edge)
        rc = RC_FAIL_SAVE_MODEL;
    else
        fprintf(file, "%d %d\n", edge->point_1_idx, edge->point_2_idx);
            
    return rc;
}

static exit_code_t write_all_points(FILE *file, const points_t *points)
{
    exit_code_t rc = RC_OK;

    int points_count = get_points_count(points);
    fprintf(file, "%d\n", points_count);

    for (int i = 0; rc == RC_OK && i < points_count; i++)
    {
        point_t *point = get_point(points, i);
        rc = write_point(file, point);
    }

    return rc;
}

static exit_code_t write_all_edges(FILE *file, const edges_t *edges)
{
    exit_code_t rc = RC_OK;

    int edges_count = get_edges_count(edges);
    fprintf(file, "%d\n", edges_count);

    for (int i = 0; rc == RC_OK && i < edges_count; i++)
    {
        edge_t *edge = get_edge(edges, i);
        rc = write_edge(file, edge);
    }

    return rc;
}