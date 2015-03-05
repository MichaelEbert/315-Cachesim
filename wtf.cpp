int main(int argc, char* argv[]){
	if(argc < 2){
		printf("Error: No input file.\n");
		return 1;
	}
	FILE* inputFile;
	inputFile = fopen(argv[1], "r"); 
