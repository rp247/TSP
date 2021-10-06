#include "dfs.h"
#include "graph.h"
#include "path.h"
#include "set.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER 512 // max city name 512 bytes

/* used in dfs print (cant intialize set at runtime) */
static bool verbose;

/* helper function to print usage message */
static void usage(char *argv) {
    fprintf(stdout, "\
SYNOPSIS\n\
  Traveling Salesman Problem using DFS.\n\
\n\
USAGE\n\
  %s [-u] [-v] [-h] [-i infile] [-o outfile]\n\
\n\
OPTIONS\n\
  -u             Use undirected graph.\n\
  -v             Enable verbose printing.\n\
  -h             Program usage and help.\n\
  -i infile      Input containing graph (default: stdin)\n\
  -o outfile     Output of computed path (default: stdout)\n",
        argv);

    return;
}

/* helper extern func called from dfs to print (or not) the path. (prints all path if verbose set) */
void dfs_print(Path *shortest, char *cities[], FILE *outfile) {
    // continue testing nowhere to go
    if (verbose) {
        path_print(shortest, outfile, cities); // print the path
    }
    return;
}

/* helper/cleanup function if an error occurs in main */
static void main_err(
    char *err, FILE *input_file, FILE *output_file, char *cities[], int num_cities) {
    if (input_file)
        fclose(input_file);
    if (output_file)
        fclose(output_file);

    /* free cities array */
    for (int i = 0; i < num_cities; i++) {
        if (!cities[i]) {
            break;
        }
        free(cities[i]);
    }
    cities = NULL;
    if (err)
        fprintf(stderr, "%s", err);
    return;
}

int main(int argc, char **argv) {

    /* adding flags to set */
    Set set = set_empty();
    enum flags { Undirected = 0, Verbose };

    /* for getopt/parsing arguments */
    int c;
    char *optlist = "hvui:o:";

    /* values for arguments */
    FILE *input_file = stdin; // default file
    FILE *output_file = stdout;

    /* adding flags and parsing args */
    while ((c = getopt(argc, argv, optlist)) != -1) {
        switch (c) {
        case 'h': usage(argv[0]); return 0;
        case 'v':
            set = set_insert(set, Verbose);
            verbose = true; // a hack for dfs print
            break;
        case 'u': set = set_insert(set, Undirected); break;
        case 'i':
            /* open file if possible */
            input_file = fopen(optarg, "r");
            if (!input_file) {
                fprintf(stderr, "Error: Cannot open input file.\n");
                return -1;
            }
            break;
        case 'o':
            output_file = fopen(optarg, "w");
            if (!output_file) {
                fprintf(stderr, "Error: Cannot open ouput file.\n");
                return -1;
            }
            break;
        default: usage(argv[0]); return -1;
        }
    }

    /* to hold each string as it is parsed */
    char temp_str[BUFFER] = "\0";

    /* pointing to err or source string (another temp string) */
    char *const_temp_str = NULL;

    /* get number of cities/nodes */
    fgets(temp_str, BUFFER, input_file);
    int num_cities = atol(temp_str); // change later

    /* invalid number of cities */
    if (num_cities < 0) {
        const_temp_str = "Error: malformed number of vertices.\n";
        main_err(const_temp_str, input_file, output_file, NULL, 0);
        return -1;
    }

    /* nowhere to go (cities == 0 or 1) */
    if (num_cities == 0 || num_cities == 1) {
        const_temp_str = "There's nowhere to go.\n";
        main_err(const_temp_str, input_file, output_file, NULL, 0);
        return 0;
    }

    /* parse cities (individual elements dynamically alloacted)*/
    char *cities[num_cities];

    for (int i = 0; i < num_cities; i++) {

        const_temp_str = fgets(temp_str, BUFFER, input_file);

        /* couldnt read city name */
        if (!const_temp_str) {
            const_temp_str = "Error: Not enough cities.\n";
            main_err(const_temp_str, input_file, output_file, cities, i);
            return -1;
        }

        /* remove newline */
        if (const_temp_str[strlen(const_temp_str) - 1] == '\n') {
            const_temp_str[strlen(const_temp_str) - 1] = '\0'; // null terminate and rem \n
        }

        /* no error. copy city value */
        if (const_temp_str) {
            cities[i] = (char *) malloc((strlen(const_temp_str) * sizeof(char)) + 1); // +1 for \0
            strncpy(cities[i], const_temp_str, strlen(const_temp_str) + 1);
        }
    }

    /* parse and add edges/vertices */

    /* create graph with num_cities edges and undirected if flag passed */
    Graph *G = graph_create(num_cities, set_member(set, Undirected));
    /* cannot create graph (num cities > VERTICES ) */
    if (!G) {
        const_temp_str = "Error: Cannot create graph (vertices > 26).\n";
        main_err(const_temp_str, input_file, output_file, cities, num_cities);
        if (G)
            graph_delete(&G); // free graph mem (redundant)
        return -1;
    }

    uint32_t row, col, weight;
    int scanned;
    //for (int i = 0; i < num_cities; i++) {
    while (
        (scanned = fscanf(input_file, "%" PRIu32 " %" PRIu32 " %" PRIu32 "\n", &row, &col, &weight))
        != EOF) {
        /* malformed edge */
        if (scanned != 3) {
            const_temp_str = "Error: malformed edge.\n";
            main_err(const_temp_str, input_file, output_file, cities, num_cities);
            if (G)
                graph_delete(&G); // free graph mem
            return -1;
        }

        graph_add_edge(G, row, col, weight); // else add edge
    }

    /* call dfs */
    Path *curr = path_create();
    Path *shortest = path_create();

    dfs(G, START_VERTEX, curr, shortest, cities, output_file);

    /* print shortest path or nowhere to go */
    if (path_length(shortest) == 0) {
        fprintf(output_file, "No Hamiltonian path found.\n");
    } else {
        path_print(shortest, output_file, cities); // print the path
    }
    fprintf(output_file, "Total recursice calls: %" PRIu64 "\n", rec_call);

    /* cleaning up */
    if (G)
        graph_delete(&G);
    if (curr)
        path_delete(&curr);
    if (shortest)
        path_delete(&shortest);
    const_temp_str = NULL;
    main_err(const_temp_str, input_file, output_file, cities, num_cities);
    return 0;
}
