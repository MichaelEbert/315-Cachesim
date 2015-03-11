#ifndef CACHE_H
#define CACHE_H
typedef struct{
	CacheSet* cacheSets;
	int numCacheSets;
}Cache;

//CacheSize  and line size are in bytes!
void initCache(int associativity, int cacheSize, int lineSize){
	Cache* thisCache = malloc(sizeof(Cache));
	thisCache->cacheSets = malloc(sizeof(CacheSet) * associativity);
	for(int i = 0; i < associativity, i++){
		initCacheSet(cacheSets[i], cacheSize/associativity, lineSize);
	}
	thisCache->numCacheSets = associativity;
	return;
}

//search through the cachesets to see if the address is in any of them
int isInCache(Cache* thisCache, int address){
	for(int i = 0; i < thisCache->numCacheSets; i++){
		if(isInCacheSet(thisCache->cacheSets[i], address)){
			//add in recently used update here?
			return 1;
		}
	}
	return 0;
}

//note: does not check to see if address is already in cache
void insertIntoCache(Cache* thisCache, int address){
	int index = indexFromCacheSet(thisCache->cacheSets[0], address);
	insertIntoCacheSet(thisCache->cacheSets[leastRecentlyUsed(thisCache, index)], address);
	return;
}


#endif	
