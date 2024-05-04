#define DEBUG 0

#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)