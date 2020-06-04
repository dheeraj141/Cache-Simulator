//
//  main.c
//  Cache_simulator1
//
//  Created by Dheeraj Kumar Ramchandani on 04/06/20.
//  Copyright © 2020 Dheeraj Kumar Ramchandani. All rights reserved.
//

#include <stdio.h>
#include "cache.h"
#include "check_inputs.h"

int main(int argc, const char * argv[]) {
    
    Cache currsim;
    
    statistics stat;
    stat.hits = stat.reads = stat.writes = stat.misses = 0;
    
    printf( " number of arguments are %d\n", argc);
    
    
    

    if( argc != 7 )
    {
        printf( " insufficient arguments\n");
        return -1;
        
    }
     
    
   else
    {
        
        //currsim.cachesize = 8192;
        //currsim.associativity=4;
        //currsim.block_size = 32;
        //currsim.cache_lines = 64;currsim.replace_algo = 'l';
        //currsim.write_policy = 'b';
        
        
        //simulate(&currsim, "./trace1.txt", &stat);
        if( valid_inputs( argv[1], argv[2] , argv[3], argv[4], argv[5], &currsim) )
        {
            simulate(&currsim,argv[6], &stat);
            
        }
        
        
        
    }
    
    return 0;
}
