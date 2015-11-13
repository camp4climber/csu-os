#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "multi-lookup.h"
#include "queue.h"

queue request_queue;
pthread_mutex_t queue_mutex;
pthread_mutex_t output_mutex;
FILE* output_file = NULL;

void* requester(void *filename);
void* resolver();

int main(int argc, char *argv[])
{
	int i;
	int num_req_threads = argc-2;
	int num_res_threads = MIN_RESOLVER_THREADS;

	pthread_t req_threads[num_req_threads];
	pthread_t res_threads[num_res_threads];

	pthread_mutex_init(&queue_mutex, NULL);
	pthread_mutex_init(&output_mutex, NULL);

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	queue_init(&request_queue, 100);

	if (argc < MIN_ARGS)
	{
		printf("Too Few Arguments.\nUsage: %s\n", USAGE);
		exit(1);
	}
	if (argc > MAX_INPUT_FILES + 1)
	{
		printf("Too Many Arguments.\nMax is 10.\nUsage: %s\n", USAGE);
		exit(1);
	}

	output_file = fopen(argv[(argc-1)], "w");
	if (!output_file) 
	{
		printf("Can't open output file.");
		exit(1);
	}

	//for each input file
		//spawn a requester thread

	for (i = 0; i < num_req_threads; i++)
	{
		pthread_create(&req_threads[i], &attr, requester, argv[i+1]);
	}

	//for however many resolver threads 
		//spawn a resolver thread		

	for (i = 0; i < num_res_threads; i++)
	{
		pthread_create(&res_threads[i], &attr, resolver, NULL);
	}

	//for all of the request threads
		//join

	//for all resolver threads
		//join

	return 0;
}

//Reading the input file and putting stuff in the queue.
//We'll have one thread per file.
void* requester(void *file_name)
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
	return NULL;
}

//Going through our queue and resolving domains to their IP.
//We'll have a minimum of 2 threads doing this.
void* resolver()
{
	//while q not empty or requesters still working
		//lock q mutex
		//if q not empty
			//pop q host
			//if host
				//unlock q mutex
				//dnsresolve
				//lock out mutex
				//write to output
				//unlock out mutex
		//else
			//unlock q mutex
	return NULL;
}
