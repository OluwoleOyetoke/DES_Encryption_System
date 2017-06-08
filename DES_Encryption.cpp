/*
This code is writen to perform Electronic Code Block Encryption using DES 
Language: C++
Date 1st June, 2017
Author: Oluwole Oyetoke


KEY GENERATION
1. Create random 64 bit key
2. Permute the 64 bit key using a permuation table (only 56 of the 64 bits are used)
3. Break 64 bit key into left and right (32 bit each)
4. Perform shifts on L0 & R0 to give L(1-16) and R(1-16). Shift Oce for round 1,2,9 and 16
5.Concatenate the 16 Left and Right Keys
6. Do final permutation on key (Key is reduced to 48 bits at thhis stage

MESSAGE PROCESSING
1. Break messsage into 64 bit block
2. Initial permutation of block of 64
3. Break blocks into Left & right stream (32 bit each)
4. Pass each 32 bit block through an expansion table
5. Do R(n) = L(n-1)-1 ^ f(K(n),R(n-1))  ---->L(16)R(16)
6. Inverse Concatenate R(16)L(16)
7. Do final Permuation

*/ 

//Include Necessary Header Files
#include <iostream>  //For keyboard input output operation
#include <fstream>   //For file i/o operation
#include <cstdlib>
#include <string>

//Include other class files
#include "Generator.cpp"
#include "Encrypter.cpp"

#define WIDTH 64
#define HEIGHT 1
#define BLOCK_SIZE 64
#define EXPANSION_SIZE 48
#define KEY_SIZE 64
#define PERMUTED_KEY_SIZE 56
#define PERMUTED_KEY_SIZE_TWO 48
#define SUB_KEY_SIZE 28
#define NUMBER_OF_SUBKEYS 16

using namespace std;

int main(){

Generator gen;
Encrypter enc;

//int* content = gen.randomContent(WIDTH,HEIGHT); //To generate random content
int* key = gen.generateKey(KEY_SIZE);
int totalSize = WIDTH*HEIGHT;
int noOfBlocks = totalSize/BLOCK_SIZE;

//SUBKEY CREATION
//int trialKey[] = {0,0,0,1,0,0,1,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,1,0,1,1,1,1,0,0,1,1,0,0,1,1,0,1,1,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,1};
int trialKey[] = {1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,0,0,0,0,1,0,0,1,0,0,0,1,1,0,0,0,0,0,1,0,0,1,1,1,0,0,1,1,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,1,1,1,0,1}; //second
int* permutedKey = enc.permuteKey(trialKey);  //Permute Key
int* keyLeft =  enc.divideBlocks(permutedKey, PERMUTED_KEY_SIZE, 1);//Get K+ Left
int* keyRight =  enc.divideBlocks(permutedKey, PERMUTED_KEY_SIZE, 2);//Get K= Right
int** subKeysLeft = gen.generateSubKeys(keyLeft, NUMBER_OF_SUBKEYS, SUB_KEY_SIZE, 1); //Generate 16 subkeys for K+(Left)
int** subKeysRight = gen.generateSubKeys(keyRight, NUMBER_OF_SUBKEYS, SUB_KEY_SIZE, 2); //Generate 16 subkeys for K+(Right)
int** concatenatedAndPermutedKeys = enc.concatenateAndPermuteKey(subKeysLeft, subKeysRight, SUB_KEY_SIZE, NUMBER_OF_SUBKEYS);

//DATA APPROPRIATION
//int content[] = {0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,0,1,1,1,1,0,0,0,1,0,0,1,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,0,1,1,1,1}; 
int content[] = {0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,0,0,0,1,0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,1,0,1,1,0}; //second
//Iterrate through all blocks
for(int i=0; i<noOfBlocks; i++){
int* block = enc.breakInBlocks(content, i); //Break entire content into blocks of 64
int* permutedBlock = enc.initialPermute(block); //Permute/mix the block
int* left = enc.divideBlocks(permutedBlock, BLOCK_SIZE, 1); //leftBlock
int* right = enc.divideBlocks(permutedBlock, BLOCK_SIZE, 2); //right Block
int* encrypted= enc.rounds(left, right, concatenatedAndPermutedKeys);
}

	return 1;
}
