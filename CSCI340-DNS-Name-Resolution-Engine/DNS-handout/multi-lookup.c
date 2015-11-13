#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "multi-lookup.h"
#include "queue.h"

queue requestQueue;
pthread_mutex_t queueMutex;
pthread_mutex_t outputMutex;

int main(int argc, char *argv[])
{
	pthread_mutex_init(&queueMutex, NULL);
	pthread_mutex_init(&outputMutex, NULL);
	
	queue_init(&requestQueue, 100);

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

//Reading the input file and putting stuff in the queue.
//We'll have one thread per file.
void requester(char *file_name)
{
	//open file
	//scan file
		//while(1)
			//lock mutex
			//if q full
				//unlock mutex
				//sleep
			//else
				//push to the queue
				//unlock mutex
				//break
	//close file
}

//Going through our queue and resolving domains to their IP.
//We'll have a minimum of 2 threads doing this.
void resolver()
{

}
