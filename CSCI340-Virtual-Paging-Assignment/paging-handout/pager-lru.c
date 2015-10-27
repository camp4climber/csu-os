/*
 * File: pager-lru.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains an lru pageit
 *      implmentation.
 */

#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) {

	/* This file contains the stub for an LRU pager */
	/* You may need to add/remove/modify any part of this file */

	/* Static vars */
	static int initialized = 0;
	static int tick = 1; // artificial time
	static int timestamps[MAXPROCESSES][MAXPROCPAGES];

	/* Local vars */
	int proctmp;
	int pagetmp;
	int evict = -1;
	int ticktmp = tick;

	/* initialize static vars on first run */
	if (!initialized) {
		for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++) {
			for (pagetmp = 0; pagetmp < MAXPROCPAGES; pagetmp++) {
				timestamps[proctmp][pagetmp] = 0;
			}
		}
		initialized = 1;
	}

	//for all processes
	for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++)
	{
		//update timestamps
		pagetmp = q[proctmp].pc/PAGESIZE;
		timestamps[proctmp][pagetmp] = tick;

		//if we swapped in continue
		if (pagein(proctmp, pagetmp))
			continue;
		
		//lru for each page
		for (pagetmp = 0; pagetmp < MAXPROCPAGES; pagetmp++)
		{
			//if page swapped out continue 
			if (!q[proctmp].pages[pagetmp]) continue;

			//is the timestamp less than our temp tick?
			if (timestamps[proctmp][pagetmp] < ticktmp)
			{
				//set the new temp tick
				ticktmp = timestamps[proctmp][pagetmp];
				//our lru page to evict is now this one
				evict = pagetmp;
				//if our tick value is 1 or 0, no need to check other pages.
				if (ticktmp<=1) break;
			}
		}
		
		//try to swap out
		pageout(proctmp, evict);
	}
		

	/* advance time for next pageit iteration */
	tick++;
}
