#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* structure definition (credits: From the lab document) */
struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES]; // no dynamic. recheck??
};

/* creates/initializes a graph */
Graph *graph_create(uint32_t vertices, bool undirected) {
    if (vertices == 0 || vertices > VERTICES) {
        return NULL;
    } // change later

    Graph *G = (Graph *) calloc(vertices, sizeof(Graph));

    if (G) {
        G->vertices = vertices;
        G->undirected = undirected;

        // use memset instead? (remove comment)
        /* initializes visited array and matrix */
        for (uint32_t i = 0; i < G->vertices; i++) {
            G->visited[i] = false;
            for (uint32_t j = 0; j < G->vertices; j++) {
                G->matrix[i][j] = 0;
            }
        }
    }

    return G;
}

/* deletes a graph */
void graph_delete(Graph **G) {
    if (*G) {
        free(*G);
        *G = NULL;
    }
    return;
}

/* num of vertices in graph */
uint32_t graph_vertices(Graph *G) {
    if (!G)
        return 0; // no graph
    return G->vertices;
}

/* checks if a edge is in valid i.e vertex in range [0, max) */
static inline bool valid_edge(uint32_t i, uint32_t j, uint32_t max) {
    return i < max && j < max;
}

/* adds an edge to a graph */
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {

    if (!G || !valid_edge(i, j, G->vertices))
        return false; // no graph or invalid edge

    G->matrix[i][j] = k; // add the edge
    G->visited[i] = false;

    /* if undirected add both ways */
    if (G->undirected) {
        G->matrix[j][i] = k;
        G->visited[j] = false;
    }

    return true;
}

/* checks if graph has an edge */
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (!G)
        return false; // no stack or invalid edge
    return G->matrix[i][j] != 0;
}

/* returns edge weight if possible */
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (!G)
        return 0; // no graph
    return G->matrix[i][j];
}

/* checks if the vertex has already been visited */
bool graph_visited(Graph *G, uint32_t v) {
    if (!G)
        return true;
    return G->visited[v];
}

/* marks a vertex as visited */
void graph_mark_visited(Graph *G, uint32_t v) {
    if (!G)
        return;
    G->visited[v] = true;
    return;
}

/* marks a vertex as unvisited */
void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (!G)
        return;
    G->visited[v] = false;
    return;
}

/* prints a graph */
void graph_print(Graph *G) {
    if (!G)
        return;

    for (uint32_t i = 0; i < G->vertices; i++) {
        for (uint32_t j = 0; j < G->vertices; j++) {
            fprintf(stdout, "%2" PRIu32 " ", G->matrix[i][j]);
        }
        fprintf(stdout, "\n");
    }
    return;
}
