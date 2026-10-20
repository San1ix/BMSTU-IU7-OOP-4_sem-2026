#ifndef EDGE_H
#define EDGE_H

typedef struct
{
    int point_1_idx;
    int point_2_idx;
} edge_t;

typedef struct
{
    edge_t *data;
    int edges_count;
} edges_t;

edges_t* alloc_edges(const int count);
void free_edges(edges_t *edges);

void set_edge(edge_t *dst, const edge_t *src);
edge_t *get_edge(const edges_t *edges, const int idx);
int get_edges_count(const edges_t *edges);

int is_edges_valid(const edges_t *edges);

#endif
