//Include other class files functions
#ifndef ADDER
#define ADDER 1
#define BLOCK_SIZE 64



class Encrypter{
	
	public:
	Encrypter(){
	};
	~Encrypter(){
	};
	
	int * breakInBlocks(int* content, int blockNo);
	int * permuteKey(int* block);
	int * initialPermute(int* block);
	int * divideBlocks(int* block, int blockSize, int part);
	int * expansionFunction(int* block, int expSize);
	int * decimalToBinaryConverter(unsigned int value, int size);
	int * concatenateBlock(int* blockA, int sizeA, int* blockB, int sizeB);
	int** concatenateAndPermuteKey(int** leftKeys, int** rightKeys, int subKeySize, int noOfKeys);
	int* rounds(int* leftBlock, int* rightBlock, int** concatAndPermutedSubkeys);
	int binaryToDecimaConverter(char* input, int size);
	
	
	
};

	
	#endif
