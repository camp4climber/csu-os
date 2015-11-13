#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "multi-lookup.h"
#include "queue.h"

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

	for (i = 0; i < num_req_threads; i++)
	{
		pthread_join(req_threads[i], NULL);
	}

	//flag to let us know req is done.
	req_done = 1;

	//for all resolver threads
		//join

	for (i = 0; i < num_res_threads; i++)
	{
		pthread_join(res_threads[i], NULL);
	}

	fclose(output_file);
	pthread_mutex_destroy(&queue_mutex);
	pthread_mutex_destroy(&output_mutex);
	queue_cleanup(&request_queue);
	return 0;
}

//Reading the input file and putting stuff in the queue.
//We'll have one thread per file.
void* requester(void *file_name)
{
	char host[MAX_NAME_LENGTH];
	char* temp;

	//open file
	FILE* input_file = fopen(file_name, "r");

	//scan file
	while (fscanf(input_file, INPUTFS, host) == 1)
	{
		while(1)
		{
			//lock mutex
			pthread_mutex_lock(&queue_mutex);
			
			//if q full
			if (queue_is_full(&request_queue))
			{
				//unlock mutex
				pthread_mutex_unlock(&queue_mutex);
				//sleep
				usleep(rand() % 100);
			}
			else
			{
				//malloc memory for queue to use
				temp = malloc(MAX_NAME_LENGTH);
				strncpy(temp, host, MAX_NAME_LENGTH);
				//push to the queue
				queue_push(&request_queue, temp);
				//unlock mutex
				pthread_mutex_unlock(&queue_mutex);
				//break
				break;
			}
		}
	}

	//close file
	fclose(input_file);
	return NULL;
}

//Going through our queue and resolving domains to their IP.
//We'll have a minimum of 2 threads doing this.
void* resolver()
{
	char* host;
	char ip[MAX_IP_LENGTH];

	//while q not empty or requesters still working
	while (!queue_is_empty(&request_queue) || !req_done)
	{
		//lock q mutex
		pthread_mutex_lock(&queue_mutex);
		//if q not empty
		if (!queue_is_empty(&request_queue))
		{
			//pop q host
			host = queue_pop(&request_queue);

			//if host
			if (host)
			{
				//unlock q mutex
				pthread_mutex_unlock(&queue_mutex);
				//dnsresolve
				dnslookup(host, ip, sizeof(ip));
				//lock out mutex
				pthread_mutex_lock(&output_mutex);
				//write to output
				fprintf(output_file, "%s,%s\n", host, ip);
				//unlock out mutex
				pthread_mutex_unlock(&output_mutex);
			}
			free(host);
		}
		else
		{
			//unlock q mutex
			pthread_mutex_unlock(&queue_mutex);
		}
	}
	return NULL;
}
