#include "edge.h"

#include <stdlib.h>

static edge_t *get_edge_from_array(edge_t *edges, const int count, const int idx);

edges_t* alloc_edges(const int count)
{
    if (count < 1)
        return NULL;

    edges_t *edges = (edges_t*)malloc(sizeof(edges_t));
    if (edges)
    {
        edge_t *data = (edge_t*)calloc(count, sizeof(edge_t));
        if (!edges)
            free(edges);
        else
        {
            edges->data = data;
            edges->edges_count = count;
        }
    }

    return edges;
}

void free_edges(edges_t *edges)
{
    if (edges)
    {
        if (edges->data)
            free(edges->data);
        free(edges);
    }
}

void set_edge(edge_t *dst, const edge_t *src)
{
    if (dst && src)
    {
        dst->point_1_idx = src->point_1_idx;
        dst->point_2_idx = src->point_2_idx;
    }
}

edge_t *get_edge(const edges_t *edges, const int idx)
{
    edge_t *edge = NULL;

    if (edges && edges->data)
        edge = get_edge_from_array(edges->data, edges->edges_count, idx);

    return edge;
}

static edge_t *get_edge_from_array(edge_t *edges, const int count, const int idx)
{
    edge_t *edge = NULL;

    if (idx <count && idx > -1)
        edge = &edges[idx];

    return edge;
}

int get_edges_count(const edges_t *edges)
{
    int count = 0;

    if (edges && edges->data)
        count = edges->edges_count;

    return count;
}

int is_edges_valid(const edges_t *edges)
{
    int is_valid = 0;

    if (edges && edges->data && edges->edges_count > 0)
        is_valid = 1;

    return is_valid;
}
