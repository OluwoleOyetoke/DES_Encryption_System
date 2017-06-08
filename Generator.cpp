//Class used for all the different Generations used by DES
#include <iostream>  //For generating random numbers
#include <ctime>
#include <cstdlib> //Contains the random functions we need.
#include <String.h>
#include <Math.h>

#include "Encrypter.h"
#include "Generator.h"


#define MAX_IMAGE_WIDTH 4096
#define MAX_IMAGE_HEIGHT 4096

#define DES_CHUNK_SIZE 64

using namespace std;

int * Generator::randomContent(int width, int height){
	float allowableWidth = MAX_IMAGE_WIDTH/8;
	float allowableHeight = MAX_IMAGE_HEIGHT/8;
	//VALIDATION
	//Check validity of input
	if(width==0 || height==0){
			cerr<<"Please input width and height greatert than 0"<<endl;
			return NULL;
	}
	//Check size
	else if(width>MAX_IMAGE_WIDTH){
		cerr<<"Width Greater than maximum allowable image width of "<<allowableWidth<<endl;
		return NULL;
	} else if(height>MAX_IMAGE_HEIGHT){
		cerr<<"Height Greater than maximum allowable image height of "<<allowableHeight<<endl;	
		return NULL;
	}
	
	int widthRemainder = 0;
	int heightRemainder = 0;
	//check block fitness (DES works with chunk of 64).....pad if necessary
	if(width%DES_CHUNK_SIZE!=0){
		widthRemainder  = width%DES_CHUNK_SIZE;
		
		if(widthRemainder!=DES_CHUNK_SIZE){
		widthRemainder = DES_CHUNK_SIZE - widthRemainder;	
		}else{
		widthRemainder=	DES_CHUNK_SIZE - width;
		}
	
	}else if(height%DES_CHUNK_SIZE!=0){
				heightRemainder  = height%DES_CHUNK_SIZE;
		
		if(heightRemainder!=DES_CHUNK_SIZE){
		heightRemainder = DES_CHUNK_SIZE - heightRemainder;	
		}else{
		heightRemainder=	DES_CHUNK_SIZE - height;
		}
	}
	
	//Pad values
	width = width+widthRemainder;
	height = height+heightRemainder;
	int oneDLength = width*height;

//cout<<"Width: "<<width<<" Height: "<<height<<endl;


//Create return array (representing image)
    int** content = new int*[width];
	int* content1D = new int[oneDLength];	
srand(time(NULL)); //Set the seed for the random numbers to the current time (so we get a different seed each time we run the program).
	for(int i=0; i<width; i++){
		content[i] = new int[height];
		for(int j=0; j<height; j++){
		    content[i][j] = rand()&1;  //Generate random Binaries
		    content1D[(i*width)+j] = content[i][j];
		}
	//	cout<<"\n\n";
	}
	return content1D;
}

int * Generator::generateKey(int keySize){
	//validate input
	if(keySize==0){
		cerr<<"Key Size has to be > 0"<<endl;
		return NULL;
	}
	
	//is keySize a multiple of 8
	if(keySize%8!=0){
		cerr<<"KeySize needs to be a multiple of 8"<<endl;
	}
	
	int* key = new int[keySize];
	srand(time(NULL)); //Seed with current time
	for(int i=0; i<keySize; i++){
		key[i] = rand()&1;
	}
	return key;
	
}


int ** Generator::generateSubKeys(int* key, int number, int size, int side){ 
	//side= 1, left......2, right
	int shiftTimes[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	int** subKeys = new int*[number];
	
	char positionLeft[] = "Left"; //To signify left or right
	char positionRight[] = "Right"; //To signify left or right
	char buffer[size];
	unsigned int decimalEquivalent;
	int sum=0;
	unsigned int shiftedBinary;
	unsigned int temp;
	unsigned int lastBitMask=(1<<(size-1));//10000000000......000
	unsigned int firstBitMask=1;	//0000000000000......001
	
	unsigned int twentyNinthBitMask = (1<<size);
	unsigned int twentyNinthBitMask2 = ~(1<<size);
	Encrypter enc;
		
	for(int q=0; q<number; q++){
	//	cout<<"ROUND"<<q+1<<endl;
	subKeys[q] = new int[size];
	
	//Convert Array Data to 1 long String
	sum=0;
	for(int i=size-1; i>=0; i--){
			if(key[i]!=0){
		sum = sum+pow(2, size-i-1);	
	}
}
	
	//Convert 1 long string to its decimal equivalent;
	shiftedBinary =  sum;
	//cout<<"Value in Decimal: "<<decimalEquivalent<<endl;
		
	//Shift operation
	for(int w=0; w<shiftTimes[q]; w++){
	
	shiftedBinary = shiftedBinary << 1; //Left shift acording to shift times table
	temp = shiftedBinary&twentyNinthBitMask;
	
	if(temp>0){
		shiftedBinary =shiftedBinary|firstBitMask; //replace first bit in shiftedBit with bit 1
	
	}	else{
	  	//replace with 0 (Default with bit shifting)
	}
	shiftedBinary = shiftedBinary&twentyNinthBitMask2;	//Clear 29th bit (overflow) to 0	
	}
	int* arrayEquivalent = enc.decimalToBinaryConverter(shiftedBinary, size);


if(side==1){
		//	cout<<positionLeft<<" Key "<<q+1<<": ";	
		}else{
		//		cout<<positionRight<<" Key "<<q+1<<": ";
		}
	for(int e=0; e<size; e++){
		subKeys[q][e] =  arrayEquivalent[e];
		key[e] = arrayEquivalent[e];
		//cout<<subKeys[q][e]<<"";	
	}
 		//cout<<"\n"<<endl;
}		
return subKeys;	
	
}



