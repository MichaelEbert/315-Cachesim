#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cache.h"
int main(int argc, char* argv[]){
	if(argc < 2){
		printf("Error: No input file.\n");
		return 1;
	}
	FILE* inputFile;
	inputFile = fopen(argv[1], "r");
	
	typedef struct way {
		int *arr;
		int arrSize;
	} way;

	int i = 0;
	int numHits = 0;
	int numAddr = 0;
	int numWords = 1;
	int cacheSize = 2;

	// Processing an address
	int curAddr = 0;
	int curTag = 0;
	int curIndex = 0;
	
	// Calculating bits
	int numIndexBits = log2(cacheSize/2) + 10 - numWords;
	int offset = log2(numWords) + 2;
	int numTagBits = 32 - numIndexBits - offset;
	int numIndicies = 1 << numIndexBits;

	// Masks
	int indexMask = (1 << numIndexBits) - 1;
	int tagMask = (1 << numTagBits) - 1;

	int tag[numIndicies];

	for (i = 0; i < numIndicies; i++) {
		tag[i] = 0;
	}
	CacheSet* oneCacheSet = initCacheSet(2048, 1);
	while (fscanf(inputFile, "%d", &curAddr) != EOF) {
		fscanf(inputFile, " %x", &curAddr);
		if(isInCacheSet(oneCacheSet, curAddr)){
			numHits++;
		}
		else{
			insertIntoCacheSet(oneCacheSet, curAddr);
		}
		numAddr++;
	}

	printf("Cache #1\n");
	printf("Number of addresses: %d\n", numAddr);
	printf("Hit rate = %0.2lf%\n", 100 * (double)numHits/numAddr);

}
