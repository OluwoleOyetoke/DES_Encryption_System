#include <iostream>
#include <stdlib.h>
#include <String.h>
#include <math.h>

#define BLOCK_SIZE 64
#define EXPANSION_SIZE 48
#define SUB_KEY_SIZE 28
#define PERMUTED_KEY_SIZE 56
#define PERMUTED_KEY_SIZE_TWO 48
#define PERMUTED_KEY_SIZE_THREE 32
#define ROUNDS 16

#include "Encrypter.h"

using namespace std;


	//Declare Global Variables
	int keyPermutationTable1[]={57,49,41,33,25,17,9,
								1,58,50,42,34,26,18,
								10,2,59,51,43,35,27,
								19,11,3,60,52,44,36,
								63,55,47,39,31,23,15,
								7,62,54,46,38,30,22, 
								14,6,61,53,45,37,29,
								21,13,5,28,20,12,4};
													
	int keyPermutationTable2[]={14,17,11,24,1,5, 
								3,28,15,6,21,10,
								23,19,12,4,26,8,
								16,7,27,20,13,2,
								41,52,31,37,47,55,
								30,40,51,45,33,48,
								44,49,39,56,34,53,
								46,42,50,36,29,32};	
								
	int expansionTable[] = {32, 1, 2, 3, 4, 5,
							4, 5, 6, 7, 8, 9,
							8, 9, 10, 11, 12, 13,
							12, 13, 14, 15, 16, 17,
							16, 17, 18, 19, 20, 21,
							20, 21, 22, 23, 24, 25,
							24, 25, 26, 27, 28, 29,
							28, 29, 30, 31, 32, 1};
   
    int dataPermutationTable1[]=	{58,50,42,34,26,18,10,2,
									60,52,44,36,28,20,12,4,
									62,54,46,38,30,22,14,6,
									64,56,48,40,32,24,16,8,
									57,49,41,33,25,17,9,1,
									59,51,43,35,27,19,11,3,
									61,53,45,37,29,21,13,5,
									63,55,47,39,31,23,15,7};
									
    int dataPermutationTable2[] = {16,   7, 20,  21,
									29,  12,  28,  17,
									1,  15,  23,  26,
									5,  18,  31,  10,
									2,   8,  24,  14,
									32,  27,   3,   9,
									19,  13,  30,   6,
									22,  11,   4,  25};
										  
	int dataPermutationTableFinal[] = {40,     8,   48,    16,    56,   24,    64,   32,
            						   39,     7,   47,    15,    55,   23,    63,   31,
            						   38,     6,   46,    14,    54,   22,    62,   30,
            						   37,     5,   45,    13,    53,   21,    61,   29,
            						   36,     4,   44,    12,    52,   20,    60,   28,
            						   35,     3,   43,    11,    51,   19,    59,   27,
            						   34,     2,   42,    10,    50,   18,    58,   26,
            						   33,     1,   41,     9,    49,   17,    57,   25};
	int B1[6];
	int B2[6];
	int B3[6];
	int B4[6];
	int B5[6];
	int B6[6];
	int B7[6];
	int B8[6];
	
	char sBox1XBits[4];
	char sBox1YBits[2];
	
	char sBox2XBits[4];
	char sBox2YBits[2];
		
	char sBox3XBits[4];
	char sBox3YBits[2];
	
	char sBox4XBits[4];
	char sBox4YBits[2];
		
	char sBox5XBits[4];
	char sBox5YBits[2];
	
	char sBox6XBits[4];
	char sBox6YBits[2];
		
	char sBox7XBits[4];
	char sBox7YBits[2];
		
	char sBox8XBits[4];
	char sBox8YBits[2];
		
		
			
	int sBox1XDecimal=0;
	int sBox1YDecimal=0;
		
	int sBox2XDecimal=0;
	int sBox2YDecimal=0;
		
	int sBox3XDecimal=0;
	int sBox3YDecimal=0;
		
	int sBox4XDecimal=0;
	int sBox4YDecimal=0;
	
	int sBox5XDecimal=0;
	int sBox5YDecimal=0;
		
	int sBox6XDecimal=0;
	int sBox6YDecimal=0;
	
	int sBox7XDecimal=0;
	int sBox7YDecimal=0;
		
	int sBox8XDecimal=0;
	int sBox8YDecimal=0;
	
	 //NEW
	//S-BOXES
	int sBOX1[4][16] = {{14 ,4,  13,  1,   2, 15,  11,  8,   3, 10,   6, 12,   5,  9,   0,  7},
      				{0, 15,   7,  4,  14,  2,  13,  10,  3,  6,  12, 11,   9,  5,   3,  8},
      				{4,  1,  14,  8,  13,  6,   2, 11,  15, 12,   9,  7,   3, 10,   5,  0},
     				{15, 12,   8,  2,   4,  9,   1,  7,   5, 11,   3, 14,  10,  0,   6, 13}};
     				
   	int sBOX2[4][16] = {{15,  1,   8, 14,   6, 11,   3,  4,   9,  7,  2, 13, 12,  0,   5, 10},
      				{3, 13,   4,  7,  15,  2,   8, 14,  12,  0,   1, 10,   6,  9,  11,  5},
   					{0, 14,   7, 11,  10,  4,  13,  1,   5,  8,  12,  6,   9,  3,   2, 15},
   					{13,  8,  10,  1,   3, 15,   4,  2,  11,  6,   7, 12,   0,  5,  14,  9}};
   					
   	int sBOX3[4][16] = {{10,  0,   9, 14,   6,  3,  15,  5,   1, 13,  12,  7,  11,  4,   2,  8},
     				{13, 7,   0,  9,   3,  4,   6, 10,   2,  8,   5, 14,  12, 11,  15,  1},
     				{13, 6,   4,  9,   8, 15,   3,  0,  11,  1,   2, 12,   5, 10,  14,  7},
      				{1, 10,  13,  0,   6,  9,   8,  7,   4, 15,  14,  3,  11,  5,   2, 12}};
      				
    int sBOX4[4][16] = { {7,   13,  14,  3,   0,  6,   9, 10,   1,  2,   8,  5,  11, 12,   4, 15},
     				{13,  8,   11,  5,   6, 15,   0,  3,   4,  7,   2, 12,   1, 10,  14,  9},
     				{10,  6,   9,   0,  12, 11,   7, 13,  15,  1,   3, 14,   5,  2,   8,  4},
      				{3,   15,  0,   6,  10,  1,  13,  8,   9,  4,   5, 11,  12,  7,   2, 14}};
      				
    int sBOX5[4][16] = { {2, 12,   4,  1,   7, 10,  11,  6,   8,  5,   3, 15,  13,  0,  14,  9},
     				{14, 11,  2, 12,   4,  7,  13,  1,   5,  0,  15, 10,   3,  9,   8,  6},
      				{4,  2,   1, 11,  10, 13,   7,  8,  15,  9,  12,  5,   6,  3,   0, 14},
     				{11,  8,  12,  7,   1, 14,   2, 13,   6, 15,   0,  9,  10,  4,   5,  3}};
    
    int sBOX6[4][16] = {{12,  1,  10, 15,   9,  2,   6,  8,   0, 13,   3,  4,  14,  7,   5, 11},
     				{10, 15,   4,  2,   7, 12,   9,  5,   6,  1, 13, 14,   0, 11,   3,  8},
      				{9, 14, 15,  5,   2,  8,  12,  3,   7,  0,   4, 10,   1, 13,  11,  6},
      				{4,  3,   2, 12,   9,  5,  15, 10,  11, 14,   1,  7,   10,  0,   8, 13}};
      				
    int sBOX7[4][16] = {{4, 11,   2, 14,  15,  0,   8, 13,   3, 12,   9,  7,   5, 10,   6,  1},
     				{13,  0,  11,  7,   4,  9,   1, 10,  14,  3,   5, 12,   2, 15,   8,  6},
      				{1,  4,  11, 13,  12,  3,   7, 14,  10, 15,   6,  8,   0,  5,   9,  2},
      				{6, 11,  13,  8,   1,  4,  10,  7,   9,  5,   0, 15,  14,  2,   3, 12}};
      				
    int sBOX8[4][16] = {{13,  2,   8,  4,   6, 15,  11,  1,  10,  9,   3, 14,   5,  0,  12,  7},
      				{1, 15,  13,  8,  10,  3,   7,  4,  12,  5,   6, 11,   10, 14,   9,  2},
      				{7, 11,   4,  1,   9, 12,  14,  2,   0,  6,  10, 13,  15,  3,   5,  8},
      				{2,  1,  14,  7,   4, 10,   8, 13,  15, 12,   9,  10,   3,  5,   6, 11}};
    
    
    
    /*
    	//S-BOXES
	int sBOX1[4][16] = {{14 ,4,  13,  1,   2, 15,  11,  8,   3, 10,   6, 12,   5,  9,   0,  7},
      				{0, 15,   7,  4,  14,  2,  13,  10,  3,  6,  12, 11,   9,  5,   3,  8},
      				{4,  1,  14,  8,  13,  6,   2, 11,  15, 12,   9,  7,   3, 10,   5,  0},
     				{15, 12,   8,  2,   4,  9,   1,  7,   5, 11,   3, 14,  10,  0,   6, 13}};
     				
   	int sBOX2[4][16] = {{15,  1,   8, 14,   6, 11,   3,  4,   9,  7,  2, 13, 12,  0,   5, 10},
      				{3, 13,   4,  7,  15,  2,   8, 14,  12,  0,   1, 10,   6,  9,  11,  5},
   					{0, 14,   7, 11,  10,  4,  13,  1,   5,  8,  12,  6,   9,  3,   2, 15},
   					{13,  8,  10,  1,   3, 15,   4,  2,  11,  6,   7, 12,   0,  5,  14,  9}};
   					
   	int sBOX3[4][16] = {{10,  0,   9, 14,   6,  3,  15,  5,   1, 13,  12,  7,  11,  4,   2,  8},
     				{13, 7,   0,  9,   3,  4,   6, 10,   2,  8,   5, 14,  12, 11,  15,  1},
     				{13, 6,   4,  9,   8, 15,   3,  0,  11,  1,   2, 12,   5, 10,  14,  7},
      				{1, 10,  13,  0,   6,  9,   8,  7,   4, 15,  14,  3,  11,  5,   2, 12}};
      				
    int sBOX4[4][16] = { {7,   13,  14,  3,   0,  6,   9, 10,   1,  2,   8,  5,  11, 12,   4, 15},
     				{13,  8,   11,  5,   6, 15,   0,  3,   4,  7,   2, 12,   1, 10,  14,  9},
     				{10,  6,   9,   0,  12, 11,   7, 13,  15,  1,   3, 14,   5,  2,   8,  4},
      				{3,   15,  0,   6,  10,  1,  13,  8,   9,  4,   5, 11,  12,  7,   2, 14}};
      				
    int sBOX5[4][16] = { {2, 12,   4,  1,   7, 10,  11,  6,   8,  5,   3, 15,  13,  0,  14,  9},
     				{14, 11,  2, 12,   4,  7,  13,  1,   5,  0,  15, 10,   3,  9,   8,  6},
      				{4,  2,   1, 11,  10, 13,   7,  8,  15,  9,  12,  5,   6,  3,   0, 14},
     				{11,  8,  12,  7,   1, 14,   2, 13,   6, 15,   0,  9,  10,  4,   5,  3}};
    
    int sBOX6[4][16] = {{12,  1,  10, 15,   9,  2,   6,  8,   0, 13,   3,  4,  14,  7,   5, 11},
     				{10, 15,   4,  2,   7, 12,   9,  5,   6,  1, 13, 14,   0, 11,   3,  8},
      				{9, 14, 15,  5,   2,  8,  12,  3,   7,  0,   4, 10,   1, 13,  11,  6},
      				{4,  3,   2, 12,   9,  5,  15, 10,  11, 14,   1,  7,   6,  0,   8, 13}};
      				
    int sBOX7[4][16] = {{4, 11,   2, 14,  15,  0,   8, 13,   3, 12,   9,  7,   5, 10,   6,  1},
     				{13,  0,  11,  7,   4,  9,   1, 10,  14,  3,   5, 12,   2, 15,   8,  6},
      				{1,  4,  11, 13,  12,  3,   7, 14,  10, 15,   6,  8,   0,  5,   9,  2},
      				{6, 11,  13,  8,   1,  4,  10,  7,   9,  5,   0, 15,  14,  2,   3, 12}};
      				
    int sBOX8[4][16] = {{13,  2,   8,  4,   6, 15,  11,  1,  10,  9,   3, 14,   5,  0,  12,  7},
      				{1, 15,  13,  8,  10,  3,   7,  4,  12,  5,   6, 11,   0, 14,   9,  2},
      				{7, 11,   4,  1,   9, 12,  14,  2,   0,  6,  10, 13,  15,  3,   5,  8},
      				{2,  1,  14,  7,   4, 10,   8, 13,  15, 12,   9,  0,   3,  5,   6, 11}};
*/

//Block starts from 0
int * Encrypter::breakInBlocks(int* content, int blockNo){
	int* newBlock = new int[BLOCK_SIZE];
	int startPos = blockNo*BLOCK_SIZE;
	int count =0;
	for(int i=startPos; i<startPos+BLOCK_SIZE; i++){
		newBlock[count] = content[i];
		count++;
	}
	
	return newBlock;
}

int * Encrypter::divideBlocks(int* block, int blockSize, int part){
int* newBlock = new int[blockSize/2];
//cout<<"\n\nDIVIDED PART"<<part<<"\n";
	if(part==1){
		for(int i=0; i<blockSize/2; i++){
			newBlock[i] = block[i];
//			cout<<newBlock[i];
		}
	}	else if(part==2){
		for(int j=blockSize/2; j<blockSize; j++){
			newBlock[j-(blockSize/2)] = block[j];
//			cout<<newBlock[j-(blockSize/2)];
		}
	}
//	cout<<"\n";
	return newBlock;
}


int * Encrypter::initialPermute(int* block){
	
	int *newBlock = new int[BLOCK_SIZE];
						
	//	cout<<"INITIAL PERMUTE: ";		
	for(int i=0; i<BLOCK_SIZE; i++){
			newBlock[i] = block[dataPermutationTable1[i]-1]; 
	//		cout<<newBlock[i];
		}
	//	cout<<"\n";
						
	return newBlock;
}

int * Encrypter::permuteKey(int* block){
	
	int* newBlock = new int[PERMUTED_KEY_SIZE];
						
	//		cout<<"\nPERMUTED KEY\n";				
	for(int i=0; i<PERMUTED_KEY_SIZE; i++){
			newBlock[i] = block[keyPermutationTable1[i]-1]; 
		//	cout<<newBlock[i];
		}
		int answer[] = {1,1,1,1,0,0,0, 0,1,1,0,0,1,1, 0,0,1,0,1,0,1, 0,1,0,1,1,1,1, 0,1,0,1,0,1,0, 1,0,1,1,0,0,1, 1,0,0,1,1,1,1, 0,0,0,1,1,1,1};
		//	cout<<"\n\n";
			for(int i=0; i<56; i++){
		//	cout<<answer[i];	
			}						
	return newBlock;
}

//Expand the 32 bit chunk to 48 bits
int * Encrypter::expansionFunction(int* block, int expSize){
	int* newBlock = new int[expSize];	
	
    //cout<<"\nEXPANDED: \n";
	int val=0;
	for (int i=0; i<expSize; i++){
   	    val = expansionTable[i]-1;
	   	newBlock[i] = block[val];
	  // 	cout<<newBlock[i];
	}
	
    //cout<<"\n";

return newBlock;
}

int * Encrypter::decimalToBinaryConverter(unsigned int value, int size){
	unsigned int n=value;
	int remainder=0;
	int next = 0;
	char buff[1];
	//char* buff2 = new char[size];
    char buff2[size] = {'0'}; //Initialize to zero
	int * returnArray = new int[size];
	
	//cout<<"Converting: "<<value<<endl;
	int cnt=0;
	while(n){
	remainder = n%2;
	n = floor(n/2);
	itoa(remainder,&buff2[cnt], 10);
	cnt++;
	}

	//cout<<"\n Size: "<<size<<", cnt: "<<cnt<<endl;
    strrev(buff2); 
	int unfilled = size - cnt;
	for(int i=0; i<size; i++){
	if(i<unfilled){
	returnArray[i] = 0;
	}else{
      returnArray[i] = buff2[i-unfilled]-'0';
}
	//	cout<<returnArray[i];
}
return returnArray;		
}



int* Encrypter::concatenateBlock(int* blockA, int sizeA, int* blockB, int sizeB){
	int totalSize = sizeA+sizeB;
	int* newBlock = new int[totalSize];
//	cout<<"\nCONCATENATED: \n";
	for(int i=0; i<totalSize; i++){
		if(i<sizeA){
				newBlock[i] = blockA[i];
		}else{
			newBlock[i] = blockB[i-sizeA];
		}
//	cout<<newBlock[i];
	}
	
	return newBlock;
}


int** Encrypter::concatenateAndPermuteKey(int** leftKeys, int** rightKeys, int subKeySize, int noOfKeys){
	int keySize = subKeySize*2;
//	cout<<"Key Size: "<<keySize;
	

	int** concatenatedSubKeys = new int*[noOfKeys]; 
	int** concatAndPermuted = new int*[noOfKeys];
	for(int i=0; i<noOfKeys; i++){
	
		concatenatedSubKeys[i] = new int[keySize];
		concatAndPermuted[i] = new int[PERMUTED_KEY_SIZE_TWO];
		//Concatenate
		concatenatedSubKeys[i] = Encrypter::concatenateBlock(leftKeys[i], subKeySize, rightKeys[i], subKeySize);	
		//Permute
	//	cout<<"\nCONCATENATED & PERMUTED "<<i+1<<" :\n ";
		for(int j=0; j<PERMUTED_KEY_SIZE_TWO; j++){
		concatAndPermuted[i][j] = 	concatenatedSubKeys[i][keyPermutationTable2[j]-1];
	//		cout<<concatAndPermuted[i][j]<<" ";
		}
	//			cout<<"\n";
	}
	
	
	return concatAndPermuted; 	
	
}

int* Encrypter::rounds(int* leftBlock, int* rightBlock, int** concatAndPermutedSubkeys){
	
	int val;
    int tempStorage[PERMUTED_KEY_SIZE_THREE];
    int tempStorage2[PERMUTED_KEY_SIZE_THREE];
    int tempStorage3[PERMUTED_KEY_SIZE_THREE];
    int* roundOutputR = (int*) malloc(sizeof(int)*PERMUTED_KEY_SIZE_THREE);
    int* roundOutputL=  (int*) malloc(sizeof(int)*PERMUTED_KEY_SIZE_THREE);
	
memcpy(roundOutputL, leftBlock, sizeof(int)*PERMUTED_KEY_SIZE_THREE); //memcpy used to copy a block of memory
memcpy(roundOutputR, rightBlock, sizeof(int)*PERMUTED_KEY_SIZE_THREE);
		
	//16 rounds
	for(int i=0; i<ROUNDS; i++){
	cout<<"ROUND : "<<i+1<<"\n";
		  
          int* expandedRightBlock = expansionFunction(roundOutputR, EXPANSION_SIZE );
	//	cout<<"XORED : "<<"\n";
		//XOR OPERATION AND SAVING IN B-CHAMBER
		for(int j=0; j<PERMUTED_KEY_SIZE_TWO; j++){
		
		if(j>=0 && j<6){
			B1[j]	= expandedRightBlock[j]^concatAndPermutedSubkeys[i][j];
		}else if(j>=6 && j<12){
			B2[j-6]	= expandedRightBlock[j]^concatAndPermutedSubkeys[i][j];
		}else if(j>=12 && j<18){
			B3[j-12]	= expandedRightBlock[j]^concatAndPermutedSubkeys[i][j];
		}else if(j>=18 && j<24){
			B4[j-18]	= expandedRightBlock[j]^concatAndPermutedSubkeys[i][j];
		}else if(j>=24 && j<30){
			B5[j-24]	= expandedRightBlock[j]^concatAndPermutedSubkeys[i][j];
		}else if(j>=30 && j<36){
			B6[j-30]	= expandedRightBlock[j]^concatAndPermutedSubkeys[i][j];
		}else if(j>=36 && j<42){
			B7[j-36]	= expandedRightBlock[j]^concatAndPermutedSubkeys[i][j];
		}else if(j>=42 && j<48){
			B8[j-42]	= expandedRightBlock[j]^concatAndPermutedSubkeys[i][j];
		}

		}
		//	cout<<"\n";
			
		//GET SBLOCK CONTENT 1
		//extract first & last bit, concatenate and get its decimal equivalent
		itoa(B1[0], &sBox1YBits[0], 10);
		itoa(B1[5], &sBox1YBits[1], 10);	
		
		sBox1YDecimal = binaryToDecimaConverter(sBox1YBits, 2);
		
		//	extract the middle four bits, concatenate and get its decimal equivalent
		itoa(B1[1], &sBox1XBits[0], 10);
		itoa(B1[2], &sBox1XBits[1], 10);
		itoa(B1[3], &sBox1XBits[2], 10);
		itoa(B1[4], &sBox1XBits[3], 10);
	
		sBox1XDecimal = binaryToDecimaConverter(sBox1XBits, 4);

		val = sBOX1[sBox1YDecimal][sBox1XDecimal]; //Switched X,Y axis to suit array structure
		int* s1 = Encrypter::decimalToBinaryConverter(val, 4);
		
			//GET SBLOCK CONTENT 2
		//extract first & last bit, concatenate and get its decimal equivalent
		itoa(B2[0], &sBox2YBits[0], 10);
		itoa(B2[5], &sBox2YBits[1], 10);	
		sBox2YDecimal = binaryToDecimaConverter(sBox2YBits,2);
	
		//	extract the middle four bits, concatenate and get its decimal equivalent
		itoa(B2[1], &sBox2XBits[0], 10);
		itoa(B2[2], &sBox2XBits[1], 10);
		itoa(B2[3], &sBox2XBits[2], 10);
		itoa(B2[4], &sBox2XBits[3], 10);
		sBox2XDecimal = binaryToDecimaConverter(sBox2XBits, 4);
		
		val = sBOX2[sBox2YDecimal][sBox2XDecimal];
		int* s2 = Encrypter::decimalToBinaryConverter(val, 4);
			
			//GET SBLOCK CONTENT 3
		//extract first & last bit, concatenate and get its decimal equivalent
		itoa(B3[0], &sBox3YBits[0], 10);
		itoa(B3[5], &sBox3YBits[1], 10);	
		sBox2YDecimal = binaryToDecimaConverter(sBox3YBits,2);
	
		//	extract the middle four bits, concatenate and get its decimal equivalent
		itoa(B3[1], &sBox3XBits[0], 10);
		itoa(B3[2], &sBox3XBits[1], 10);
		itoa(B3[3], &sBox3XBits[2], 10);
		itoa(B3[4], &sBox3XBits[3], 10);
		sBox3XDecimal = binaryToDecimaConverter(sBox3XBits,4);
		
		val = sBOX3[sBox3YDecimal][sBox3XDecimal];
		int* s3 = Encrypter::decimalToBinaryConverter(val, 4);
			
			//GET SBLOCK CONTENT 4
		//extract first & last bit, concatenate and get its decimal equivalent
		itoa(B4[0], &sBox4YBits[0], 10);
		itoa(B4[5], &sBox4YBits[1], 10);	
		sBox4YDecimal = binaryToDecimaConverter(sBox4YBits,2);
	
		//	extract the middle four bits, concatenate and get its decimal equivalent
		itoa(B4[1], &sBox4XBits[0], 10);
		itoa(B4[2], &sBox4XBits[1], 10);
		itoa(B4[3], &sBox4XBits[2], 10);
		itoa(B4[4], &sBox4XBits[3], 10);
		sBox4XDecimal = binaryToDecimaConverter(sBox4XBits,4);
		
		val = sBOX4[sBox4YDecimal][sBox4XDecimal];
		int* s4 = Encrypter::decimalToBinaryConverter(val, 4);
	
			//GET SBLOCK CONTENT 5
		//extract first & last bit, concatenate and get its decimal equivalent
		itoa(B5[0], &sBox5YBits[0], 10);
		itoa(B5[5], &sBox5YBits[1], 10);	
		sBox5YDecimal = binaryToDecimaConverter(sBox5YBits,2);
	
		//	extract the middle four bits, concatenate and get its decimal equivalent
		itoa(B5[1], &sBox5XBits[0], 10);
		itoa(B5[2], &sBox5XBits[1], 10);
		itoa(B5[3], &sBox5XBits[2], 10);
		itoa(B5[4], &sBox5XBits[3], 10);
		sBox5XDecimal =binaryToDecimaConverter(sBox5XBits,4);
		
		val = sBOX5[sBox5YDecimal][sBox5XDecimal];
		int* s5 = Encrypter::decimalToBinaryConverter(val, 4);
	
			//GET SBLOCK CONTENT 6
		//extract first & last bit, concatenate and get its decimal equivalent
		itoa(B6[0], &sBox6YBits[0], 10);
		itoa(B6[5], &sBox6YBits[1], 10);	
		sBox6YDecimal = binaryToDecimaConverter(sBox6YBits,2);
	
		//	extract the middle four bits, concatenate and get its decimal equivalent
		itoa(B6[1], &sBox6XBits[0], 10);
		itoa(B6[2], &sBox6XBits[1], 10);
		itoa(B6[3], &sBox6XBits[2], 10);
		itoa(B6[4], &sBox6XBits[3], 10);
		sBox6XDecimal = binaryToDecimaConverter(sBox6XBits,4);
		
		val = sBOX6[sBox6YDecimal][sBox6XDecimal];
		int* s6 = Encrypter::decimalToBinaryConverter(val, 4);
		
				//GET SBLOCK CONTENT 7
		//extract first & last bit, concatenate and get its decimal equivalent
		itoa(B7[0], &sBox7YBits[0], 10);
		itoa(B7[5], &sBox7YBits[1], 10);	
		sBox7YDecimal = binaryToDecimaConverter(sBox7YBits,2);
	
		//	extract the middle four bits, concatenate and get its decimal equivalent
		itoa(B7[1], &sBox7XBits[0], 10);
		itoa(B7[2], &sBox7XBits[1], 10);
		itoa(B7[3], &sBox7XBits[2], 10);
		itoa(B7[4], &sBox7XBits[3], 10);
		sBox7XDecimal = binaryToDecimaConverter(sBox7XBits,4);
		
		val = sBOX7[sBox7YDecimal][sBox7XDecimal];
		int* s7 = Encrypter::decimalToBinaryConverter(val, 4);
	
		//GET SBLOCK CONTENT 8
		//extract first & last bit, concatenate and get its decimal equivalent
		itoa(B8[0], &sBox8YBits[0], 10);
		itoa(B8[5], &sBox8YBits[1], 10);	
		sBox8YDecimal = binaryToDecimaConverter(sBox8YBits,2);
	
		//	extract the middle four bits, concatenate and get its decimal equivalent
		itoa(B8[1], &sBox8XBits[0], 10);
		itoa(B8[2], &sBox8XBits[1], 10);
		itoa(B8[3], &sBox8XBits[2], 10);
		itoa(B8[4], &sBox8XBits[3], 10);
		sBox8XDecimal = binaryToDecimaConverter(sBox8XBits,4);
		
		val = sBOX8[sBox8YDecimal][sBox8XDecimal];
		int* s8 = Encrypter::decimalToBinaryConverter(val, 4);
	
		//CONCATENATE SBLOCK CONTENT 1,2,3,4,5,6,7,8
		for(int k=0; k<PERMUTED_KEY_SIZE_THREE; k++){
			if(k>=0 && k<4){
					tempStorage[k] = s1[k];
			}else if(k>=4 && k<8){
					tempStorage[k] = s2[k-4];
			}else if(k>=8 && k<12){
					tempStorage[k] = s3[k-8];
			}else if(k>=12 && k<16){
					tempStorage[k] = s4[k-12];
			}else if(k>=16 && k<20){
					tempStorage[k] = s5[k-16];
			}else if(k>=20 && k<24){
					tempStorage[k] = s6[k-20];
			}else if(k>=24 && k<28){
					tempStorage[k] = s7[k-24];
			}else if(k>=28 && k<32){
					tempStorage[k] = s8[k-28];
			}
		}
		//PERMUTE CONCATENATRED DATA
		for(int l=0; l<PERMUTED_KEY_SIZE_THREE; l++){
			tempStorage2[l] = tempStorage[dataPermutationTable2[l]-1];
			
	}	
			cout<<"RIGHT-16: \n";
		for(int m=0; m<PERMUTED_KEY_SIZE_THREE; m++){
			tempStorage3[m] = roundOutputR[m];
			roundOutputR[m] = roundOutputL[m]^tempStorage2[m];
			cout<<roundOutputR[m];
			
		}
			
		memcpy(roundOutputL,tempStorage3,sizeof(int)*PERMUTED_KEY_SIZE_THREE);
		
			
				cout<<"\nLEFT-16 \n";
		for(int l=0; l<PERMUTED_KEY_SIZE_THREE; l++){
				cout<<roundOutputL[l];
			}
			cout<<"\n\n";	
			
	}	
	//Reverse Order
	int* reversed = concatenateBlock(roundOutputR, PERMUTED_KEY_SIZE_THREE, roundOutputL, PERMUTED_KEY_SIZE_THREE);
	int* encryptedMsg = (int*) malloc(sizeof(int)*BLOCK_SIZE);
	//Final Permute
	cout<<"\nENCRYPTED BLOCK: \n";
	for(int n=0; n<BLOCK_SIZE; n++){
		encryptedMsg[n] = reversed[dataPermutationTableFinal[n]-1];
			cout<<encryptedMsg[n];	
	}
	return encryptedMsg;
}


int Encrypter::binaryToDecimaConverter(char* input, int size){
	int temp=0;
	int sum=0;
		//cout<<"\nBinary to Decimal Conversion\n";
		int cnt=0;
	for(int i=size-1; i>=0; i--){
		temp  = input[i]-'0';
		//cout<<temp<<", ";
			if(temp>0){
		sum = sum+pow(2, cnt);		
	}
	cnt++	;
	}
	//cout<<"\n";
	return sum;
}
	
	

