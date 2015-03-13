#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cacheset.h"
#include "cache.h"

#define NUM_TEST_CASES 7
int main(int argc, char* argv[]){
	if(argc < 2){
		printf("Error: No input file.\n");
		return 1;
	}
	FILE* inputFile;
	inputFile = fopen(argv[1], "r");
	
    int testParams[][3] = {{2048,1,1},{2048,1,2},{2048,1,4},{2048,2,1},{2048,4,1},{2048,4,4},{4096,1,1}};

    for(int i = 0; i < NUM_TEST_CASES; i++){
        int curAddr;
        int numHits = 0;
        int numAddr = 0;
        int cacheSize = testParams[i][0];
        int associativity = testParams[i][1];
        int blockSize = testParams[i][2];
    	Cache* thisCache = initCache(associativity, cacheSize, blockSize*4);
    	
    	while (fscanf(inputFile, "%d", &curAddr) != EOF) {
    		fscanf(inputFile, " %x", &curAddr);
    		if(isInCache(thisCache, curAddr)){
    			numHits++;
    		}
    		else{
    			insertIntoCache(thisCache, curAddr);
    		}
    		numAddr++;
    	}
    	printf("Cache #%d\n",i);
    	printf("Cache size: %dB\tAssociativity: %d\tBlock size: %d\n",cacheSize, associativity, blockSize);
    	printf("Hits: %d\tHit rate = %0.2lf%%\n", numHits, 100 * (double)numHits/numAddr);
    	printf("---------------------------\n");
    	rewind(inputFile);
    }

}
