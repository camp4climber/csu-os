#include "queue.h"
#include "util.h"

#define MIN_ARGS 3
#define USAGE "./multi-lookup <inputFilePath> ... <outputFilePath>"
#define INPUTFS "%1024s"
#define MAX_INPUT_FILES 10
#define MAX_RESOLVER_THREADS 10
#define MIN_RESOLVER_THREADS 2
#define MAX_NAME_LENGTH 1025
#define MAX_IP_LENGTH INET6_ADDRSTRLEN

int req_done = 0;
queue request_queue;
pthread_mutex_t queue_mutex;
pthread_mutex_t output_mutex;
FILE* output_file = NULL;

void* requester(void *filename);
void* resolver();
