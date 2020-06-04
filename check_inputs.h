//
//  check_inputs.h
//  Cache_simulator1
//
//  Created by Dheeraj Kumar Ramchandani on 04/06/20.
//  Copyright © 2020 Dheeraj Kumar Ramchandani. All rights reserved.
//

#ifndef check_inputs_h
#define check_inputs_h

#include <stdio.h>

#include <stdio.h>
#include "cache.h"

int isPow2(int x);

int validCacheSize(u_int32_t cache_size);

int validAssociativity(int assoc) ;
int validBlockSize(int blocksize) ;

char validReplaceAlg( const char *replacealg);
char validWritePolicy( const char *writepolicy);

int valid_inputs( const char *, const char *,const char *,const char *,const char*,Cache *currsim);


#endif /* check_inputs_h */
