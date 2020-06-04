//
//  cache.h
//  Cache_simulator1
//
//  Created by Dheeraj Kumar Ramchandani on 04/06/20.
//  Copyright © 2020 Dheeraj Kumar Ramchandani. All rights reserved.
//

#ifndef cache_h
#define cache_h

#include <stdio.h>

// basic structure for cache

typedef struct
{
    unsigned int tag;
    int min_block, max_block;
    int valid, dirty, priority;
    
}Line;
typedef struct
{
    int cachesize;
    int block_size;
    int cache_lines;
    int associativity;
    
    int replace_algo;
    int write_policy;
    
    
    
}Cache;

// basic structure for a line of the cache


typedef struct {
  Line* baseLine;
  int size;
} Set;









// statistics about the use of the cache
typedef struct
{
    int hits, misses, reads, writes;
} statistics;


int simulate( Cache *cache,  const char *tracefile, statistics *stat );


#endif /* cache_h */
