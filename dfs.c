#include "dfs.h"

#include "graph.h"
#include "path.h"
#include "stack.h"
#include "tsp.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

uint64_t rec_call = 0;

/* PSEUDOCODE CREDITS: built upon modified version of pseudocode provided in the lab documentation */
/* depth first search (dfs) implementation */
void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {

    uint32_t pop_here; // used for path pop vertex
    rec_call++; // counts recursive calls

    graph_mark_visited(G, v);

    /* reject the current path if it is longer than shortest */
    if (path_length(shortest) != 0 && path_length(curr) >= path_length(shortest)) {
        graph_mark_unvisited(G, v);
    }

    /* all vertices visited once*/
    else if (path_vertices(curr) == graph_vertices(G) - 1) {
        graph_mark_unvisited(G, v); // mark last one unvisited

        /* check if hamiltoninan (all vertices in stack and can go back to origin) */
        if (graph_has_edge(G, v, START_VERTEX)) {

            /* account for last distance */
            path_push_vertex(curr, START_VERTEX, G); // push curr vertex on stack

            /* update shortest if possible (no shortest yet or curr < shortest)*/
            if (path_length(shortest) == 0 || (path_length(curr) < path_length(shortest))) {
                path_copy(shortest, curr);
                /* print the path if possible (verbose on) */
                dfs_print(shortest, cities, outfile);
            }

            /* unaccount for last distance */
            path_pop_vertex(curr, &pop_here, G);
        }

        return;
    }

    /* else continue recursing */
    else {
        /* for each vertex */
        for (uint32_t i = 0; i < graph_vertices(G); i++) {
            /* has weight and not visited already */
            if (graph_has_edge(G, v, i) && !graph_visited(G, i)) {
                path_push_vertex(curr, i, G); // push curr vertex on stack
                dfs(G, i, curr, shortest, cities, outfile); // recurse
                path_pop_vertex(curr, &pop_here, G); // push curr vertex on stack
            }
        }
    }

    graph_mark_unvisited(G, v);
}
