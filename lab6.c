#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cacheset.h"
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
	int cacheSize = 2048;
	int associativity = 2;
	int blockSize = 1;

	int curAddr;

	Cache* thisCache = initCache(associativity, cacheSize, blockSize*2*2);
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

	printf("Cache #1\n");
	printf("Cache size: %dB\tAssociativity: %d\tBlock size: %d\n",cacheSize, associativity, blockSize);
	printf("Hits: %d\tHit rate = %0.2lf%\n", numHits, 100 * (double)numHits/numAddr);

}
