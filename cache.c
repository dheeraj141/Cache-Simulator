//
//  cache.c
//  Cache_simulator1
//
//  Created by Dheeraj Kumar Ramchandani on 04/06/20.
//  Copyright © 2020 Dheeraj Kumar Ramchandani. All rights reserved.
//

#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "cache.h"


void print_stats( statistics *stat)
{
    printf("Memory reads : %d\n",stat->reads);
    printf("Memory writes : %d\n",stat->writes);
    printf("Cache hits : %d\n",stat->hits);
    printf("Cache misses : %d\n",stat->misses);
    
    printf( "Hit Rate %f\n", (double)(stat->hits)/( stat->hits + stat->misses));
    return;
}

FILE *trace;
# define INT_MAX 2147483647;

int simulate( Cache *cache, const char *tracefile, statistics *stat )
{
    
    // variable for the address
    char line[50];
    //char eip[20];
    char mode;
    char memory_address[20];
    unsigned  long  address;
   // unsigned long eip;
    int i;
    
    
    // local varibles stored for connvenience
    int set_size, numSets, blockSize, writePolicy, replaceAlg;
    
    /*set pointers*/
    Set *currSet;
    Set *baseSet;
    Line *currentLine;
    
    
    set_size = cache->associativity;
    numSets = cache->cache_lines;
    blockSize = cache->block_size;
    writePolicy= cache->write_policy;
    replaceAlg = cache->replace_algo;
    
    
    // variables for each address accessed
    int tag, set, block_offset;
    
    int block_bits, set_bits;
    
    
    // masks for extracting the values
   unsigned int block_mask , tag_mask, set_mask;
    
    block_mask = blockSize -1;
    
    
    block_bits = log2( blockSize);
    set_bits = log2( numSets);
    
    set_mask = ( numSets -1) << block_bits;
    
    tag_mask = -1^set_mask^block_mask;
    
    
    // open the trace file
    
    trace  = fopen( tracefile, "r");
    if(!trace)
    {
        printf("could not open the trace file\n");
        return -1;
    }
    
    // dynamic allocation of the cache lines
    
    baseSet = ( Set*)  malloc( numSets *sizeof( Set));
    
    for( i =0; i<numSets; i++)
    {
        currSet = baseSet+i;
        currSet->baseLine = (Line*) malloc(set_size*sizeof(Line));
        memset(currSet->baseLine, 0, sizeof( sizeof(Line)));
    }
    
    currSet = baseSet;
    
    
    // reading the addresses from the memory trace file
    while( fgets(line, 50, trace)!= NULL)
    {
        // sscanf(line, "%lx, %c, %lx", &eip, &mode, &address);
        
        
        int j = 0; int k = 0;
        while( j < 50 && ( line[j]!= 'W' && line[j] != 'R' ))
              j++;
        mode  = line[j];
        j+=2;
        while( line[j] !='\n')
        {
            memory_address[k] = line[j];
            j++; k++;
        }
        
        address = strtoul( memory_address, NULL, 16);
        // address is read and now extract the set , block and tag from it
        
        block_offset = address&block_mask;
        set = ( address &set_mask) >>block_bits;
        
        tag = (( address & tag_mask)>>block_bits)>>set_bits;
        
        
        currSet = baseSet + set;
        
        // flag for checking the hits
        int flag , victim, min_priority; flag = victim = 0;
        min_priority =INT_MAX;
        for(i =0; i<set_size; i++)
        {
            currentLine = currSet->baseLine+i;
            
            // match the tag
            if( currentLine->valid ==1 && currentLine->tag == tag )
            {
                stat->hits++;
                currentLine->priority++;
                
                if( mode =='W')
                {
                    if( writePolicy =='t')
                        stat->writes++;
                    else // write it only in cache and update the dirty bit
                        currentLine->dirty =1;
                }
                
                flag =1;
                break;
                
            }
            else if( min_priority > currentLine->priority)
            {
                min_priority = currentLine->priority;
                victim = i;
                
            }
            
        }
        // cache miss LRU policy remove the least recently used block
        if( !flag)
        {
            stat->misses++;
            // line to be removed
            currentLine = currSet->baseLine+ victim;
            if( currentLine->dirty ==1)
            {
                 stat->writes++;
                currentLine->dirty = 0;
            }
            // remove the block and read the new memory block in the victim line
            currentLine->tag = tag;
            currentLine->min_block = block_offset-block_offset%blockSize;
            currentLine->max_block = currentLine->min_block +blockSize;
            currentLine->valid =1;
            
            
            // it was a write request memory write which misses in the cache now if write policy is write through then
            // read ++ and write++; read from memory and
            if( mode =='W')
            {
                if( writePolicy =='t')
                {
                    // confusion is there regarding read ++ there will be read++ or not
                    stat->reads++;
                    stat->writes++;
                }
                else
                {
                    stat->reads++;
                    currentLine->dirty=1;
                }
                
                
            }
            else // only memory read so read++
                stat->reads++;
            
               
            
            
        }
        
    }
    
 
/*
// free the memory
    
    for( i = 0; i<numSets; i++)
    {
        currSet = baseSet+i;
        for( j = 0; j<set_size; j++)
        {
            currentLine = currSet->baseLine+j;
            free( currentLine);
            
        }
    }
    free( baseSet);
 
 */
    fclose(trace);
    
    
    // print the statistics
    print_stats(stat);
    
    return 0;
    
    
    
    
    
}





