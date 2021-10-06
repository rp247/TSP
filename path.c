#include "path.h"

#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* Path definition (Credits: From the lab documentation) */
struct Path {
    Stack *vertices;
    uint32_t length;
};

/* creates a path */
Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));

    if (p) {
        p->length = 0; // default zero
        p->vertices = stack_create(VERTICES); // stack that can hold VERTICES elements

        /* failed to create stack */
        if (!p->vertices) {
            free(p);
            p = NULL;
        }
    }

    return p;
}

/* deletes a path */
void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        stack_delete(&((*p)->vertices));
        free(*p);
        *p = NULL;
    }
    return;
}

/* pushes a vertex to a path */
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    if (!p || !G || stack_full(p->vertices))
        return false;

    /* if empty then length += ORIGIN to current vertex */
    if (stack_empty(p->vertices)) {
        p->length += graph_edge_weight(G, START_VERTEX, v);
    }

    /* else length += top of stack to current vertex */
    else {
        uint32_t peeked_v;
        stack_peek(p->vertices, &peeked_v); // get top of stack
        p->length += graph_edge_weight(G, peeked_v, v); // weight from tos to v
    }

    return stack_push(p->vertices, v);
}

/* pops a vertex from a path */
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (!p || !G || !v || stack_empty(p->vertices))
        return false;

    stack_pop(p->vertices, v);

    /* if empty then length -= ORIGIN to popped vertex */
    if (stack_empty(p->vertices)) {
        p->length -= graph_edge_weight(G, START_VERTEX, *v);
    }

    /* else length -= top of stack to popped vertex */
    else {
        uint32_t peeked_v;
        stack_peek(p->vertices, &peeked_v);
        p->length -= graph_edge_weight(G, peeked_v, *v); // weight from tos to v
    }

    return true;
}

/* returns total vertices in the path */
uint32_t path_vertices(Path *p) {
    if (!p || !p->vertices)
        return 0;
    return stack_size(p->vertices);
}

/* returns the path length */
uint32_t path_length(Path *p) {
    if (!p)
        return 0;
    return p->length;
}

/* copies a path from dst to src */
void path_copy(Path *dst, Path *src) {
    if (!dst || !src)
        return;
    stack_copy(dst->vertices, src->vertices); // copy stack
    dst->length = src->length; // copy length
    return;
}

/* prints a path */
void path_print(Path *p, FILE *outfile, char *cities[]) {
    if (!p)
        return;

    fprintf(outfile, "Path length: %" PRIu32 "\n", path_length(p));
    fprintf(outfile, "Path: ");
    fprintf(outfile, "%s -> ", cities[START_VERTEX]);
    stack_print(p->vertices, outfile, cities);
    return;
}
