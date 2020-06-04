//
//  check_inputs.c
//  Cache_simulator1
//
//  Created by Dheeraj Kumar Ramchandani on 04/06/20.
//  Copyright © 2020 Dheeraj Kumar Ramchandani. All rights reserved.
//

#include "check_inputs.h"
#include <stdlib.h>



int isPow2(int x) {
  int i;
  for(i = 0; i < 31; i++) {
    if(x == 1<<i)
      return 1;
  }
  return 0;
}

int validCacheSize(u_int32_t cache_size) {
  if(isPow2(cache_size))
    return cache_size;
  return 0;
}

int validAssociativity(int assoc) {
    if(!isPow2(assoc))
        return 0;
    
  return assoc;
}

int validBlockSize(int blocksize) {
  if(isPow2(blocksize))
    return blocksize;
  return 0;
}

char validReplaceAlg(const char *replacealg) {
  char replaceAlg='l';
  if(strcmp(replacealg,"-LRU") == 0)
    replaceAlg = 'l';
  else if(strcmp(replacealg,"-FIFO") == 0)
    replaceAlg = 'f';
  return replaceAlg;
}

char validWritePolicy(const char *writepolicy) {
  char writePolicy ='t';
  if(strcmp(writepolicy,"-wt") == 0)
    writePolicy = 't';
  else if(strcmp(writepolicy,"-wb") == 0)
    writePolicy = 'b';
  return writePolicy;
}


int valid_inputs(const char *cache_size,const char *assoc,const char *block_size,const char *write_policy,const char *replace_alg, Cache *currsim)
{
    int x = validCacheSize(atoi(cache_size));
    if( x)
        currsim->cachesize=x;
    else return 0;
    
    x = validAssociativity(atoi( assoc));
    if( x)
        currsim->associativity=x;
    else return 0;
    
    x = validBlockSize(atoi( block_size));
    if( x)
        currsim->block_size =x;
    else return 0;
    
    currsim->cache_lines = (currsim->cachesize / ( currsim->associativity * currsim->block_size));
    
    
    currsim->write_policy = validWritePolicy(write_policy);
    currsim->replace_algo = validReplaceAlg(replace_alg);
    
    return 1;
                                            
    
        
}


