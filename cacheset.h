#ifndef CACHESET_H
#define CACHESET_H

#include <math.h>
#include <stdlib.h>

typedef struct{
unsigned int* tags;
int tagBits;
int byteOffsetBits;
unsigned int indexSize;
unsigned int indexMask;
}CacheSet;

int getIndex(CacheSet* thisCacheSet, int address){
	int index = address >> thisCacheSet->byteOffsetBits;
	index &= thisCacheSet->indexMask;
	return index;
}

//cacheSize and lineSize are in bytes!!!
CacheSet* initCacheSet(int cacheSize, int lineSize){
 CacheSet* thisCacheSet = malloc(sizeof(CacheSet));
 int indexSize = cacheSize/lineSize;
 int byteOffsetBits = log2(lineSize);
	int indexBits = log2(indexSize);
 int tagBits = 32 - byteOffsetBits - indexBits;
 thisCacheSet->tags = calloc(sizeof(int), indexSize);
 	thisCacheSet->indexSize = indexSize;
	thisCacheSet->tagBits = tagBits;
	thisCacheSet->byteOffsetBits = byteOffsetBits;
	thisCacheSet->indexMask = (1 << indexBits) - 1; 
	return thisCacheSet;
}

//does not check to see if address is already in cach
void insertIntoCacheSet(CacheSet* thisCacheSet, int address){
	//get address to insert to
	int index = getIndex(thisCacheSet, address);
	//do tag
	int tag = address >> (32 - thisCacheSet->tagBits);
	//insert
	thisCacheSet->tags[index] = tag;
	return;
}

int isInCacheSet(CacheSet* thisCacheSet, int address){
    int index = getIndex(thisCacheSet, address);
	int tag = address >> (32 - thisCacheSet->tagBits);
	if(thisCacheSet->tags[index] == tag){
		return 1;
	}
	return 0;
}

#endif
