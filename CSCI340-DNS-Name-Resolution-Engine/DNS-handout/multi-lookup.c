#include <stdio.h>
#include <string.h>
#include "multi-lookup.h"

pthread_mutex_t queueMutex;
pthread_mutex_t outputMutex;

int main(int argc, char *argv[])
{
	if (argc < MIN_ARGS)
	{
		printf("Usage:\n%s\n", USAGE);
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
