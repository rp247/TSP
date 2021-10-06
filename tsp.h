#ifndef __TSP_H__
#define __TSP_H__

#include "path.h"

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

extern void dfs_print(
    Path *shortest, char *cities[], FILE *outfile); // helper to print from dfs (if possible)

#endif /* __TSP_H__ */
