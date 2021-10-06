#ifndef __DFS_H__
#define __DFS_H__

#include "graph.h"
#include "path.h"
#include "stack.h"

extern uint64_t rec_call; // for recursive call count
extern void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[],
    FILE *outfile); // depth first search

#endif /* __DFS_H__ */
