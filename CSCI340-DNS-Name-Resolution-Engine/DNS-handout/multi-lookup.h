#include "queue.h"
#include "util.h"

#define MIN_ARGS 3
#define USAGE "./multi-lookup <inputFilePath> ... <outputFilePath>"
#define SBUFSIZE 1025
#define INPUTFS "%1024s"
#define MIN_RESOLVER_THREADS 2
