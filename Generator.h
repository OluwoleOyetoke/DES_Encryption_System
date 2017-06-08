
#ifndef ADDER2
#define ADDER2 2


class Generator{
	
	public:
	
	
	
	  Generator(){}; //Constructor
	~Generator(){}; //Destructor
	
	int * randomContent(int width, int height);
	
	int * generateKey(int keySize);
	int ** generateSubKeys(int* key, int number, int size, int side);
	
};

#endif
