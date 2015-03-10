#include <cstdio>
#include <cstdlib>
#include <cmath>
int main(int argc, char** argv){
	
	return 0;
}
/*
in cacheSim:
int cacheSize;
int lineSize;
int associativity;
int indexSize = cacheSize/lineSize;

each cache set is made of:
tag, data
tag, data size depend on initial conditions.
*/
class Line{
private:
	char* data;
	int tag;
	int tagBits;
public:
	Line(int tagBits, int byteOffsetBits);
	~Line(){delete[] data;}
};
Line::Line(int tagBits, int byteOffsetBits){
	this->tagBits = tagBits;
	int dataBytes = 1 << (byteOffsetBits-1);
	data = new char[dataBytes];
}
 
	


class CacheSet{
private:
	Line* lines;
public:
	CacheSet(int size, int lineSize);
	~CacheSet(){delete[] lines;}
};

CacheSet::CacheSet(int size, int lineSize){
	int indexSize = size/lineSize;
	
	int byteOffsetBits = log2(lineSize);
	int indexBits = log2(indexSize);
	int tagBits = 32 - byteOffsetBits - indexBits;

	lines = new Line(tagBits, byteOffsetBits)[indexSize];
}
