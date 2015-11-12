#include <stdio.h>
#include <string.h>
#include "multi-lookup.h"

queue hostQueue;
pthread_mutex_t queueMutex;
pthread_mutex_t outputMutex;

int main(int argc, char *argv[])
{
	pthread_mutex_init(&queueMutex, NULL);
	pthread_mutex_init(&outputMutex, NULL);
	
	queueInit(%hostQueue, 100);

	if (argc < MIN_ARGS)
	{
		printf("Too Few Arguments.\nUsage: %s\n", USAGE);
		return 1;
	}
	if (argc > MAX_INPUT_FILES + 1)
	{
		printf("Too Many Arguments.\nMax is 10.\nUsage: %s\n", USAGE);
		return 1;
	} 

	return 0;
}

void requester(char *file_name)
{
}

void resolver()
{
}
