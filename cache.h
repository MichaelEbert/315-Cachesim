#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>
#include <stdlib.h>

#include "cacheset.h"

typedef struct{
	CacheSet* cacheSets;
	int numCacheSets;
	int** lruTable;
}Cache;

int leastRecentlyUsed(Cache* thisCache, int index){
	int lru = thisCache->lruTable[index][0];
	for(int i = 1; i < thisCache->numCacheSets; i++){
		thisCache->lruTable[index][i-1] = thisCache->lruTable[index][i];
	}
	thisCache->lruTable[index][thisCache->numCacheSets-1] = lru;
	return lru;
}

void updateUsed(Cache* thisCache, int index, int cacheNum){
	//find index of cacheNum
	int cacheNumIndex = -1;
	for(int i = 0; i < thisCache->numCacheSets; i++){
		if(thisCache->lruTable[index][i] == cacheNum){
			cacheNumIndex = i;
			break;
		}
	}
	if(cacheNumIndex < 0){
		printf("error with cacheNum: not found in lruTable!");
	}
	for(int i = cacheNumIndex+1; i < thisCache->numCacheSets; i++){
		thisCache->lruTable[index][i-1] = thisCache->lruTable[index][i];
	}
	thisCache->lruTable[index][thisCache->numCacheSets-1] = cacheNum;
	return;
}

//CacheSize  and line size are in bytes!
Cache*  initCache(int associativity, int cacheSize, int lineSize){
	Cache* thisCache = malloc(sizeof(Cache));
	thisCache->cacheSets = malloc(sizeof(CacheSet) * associativity);
	for(int i = 0; i < associativity; i++){
		thisCache->cacheSets[i] = *initCacheSet(cacheSize/associativity, lineSize);
	}
	thisCache->numCacheSets = associativity;
	thisCache->lruTable = malloc(sizeof(int*) * thisCache->cacheSets[0].indexSize);
	//initialize lruTable entries to {0,1,2,...,associativity-1}
	for(int i = 0; i < thisCache->cacheSets[0].indexSize; i++){
		thisCache->lruTable[i] = malloc(sizeof(int) * thisCache->numCacheSets);
		for(int j = 0; j < associativity; j++){
			thisCache->lruTable[i][j] = j;
		}
	}
	return thisCache;
}

//search through the cachesets to see if the address is in any of them
int isInCache(Cache* thisCache, int address){
	for(int i = 0; i < thisCache->numCacheSets; i++){
		if(isInCacheSet(&thisCache->cacheSets[i], address)){
			updateUsed(thisCache, getIndex(&thisCache->cacheSets[0], address), i);	
			return 1;
		}
	}
	return 0;
}

//note: does not check to see if address is already in cache
void insertIntoCache(Cache* thisCache, int address){
	int index = getIndex(&thisCache->cacheSets[0], address);
	insertIntoCacheSet(&thisCache->cacheSets[leastRecentlyUsed(thisCache, index)], address);
	return;
}


#endif	
