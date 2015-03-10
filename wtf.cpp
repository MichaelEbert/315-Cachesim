class Line{
int tag;
int tagBits;
char* testarr;
public:
	Line(int tagBits, int dataBits);
};

Line::Line(int tagBits, int dataBits){
	this->tagBits = tagBits;
	testarr = new char[dataBits];
}

int main(int argc, char* argv[]){
	Line myLine = Line(3,4);
	return 0;
}
