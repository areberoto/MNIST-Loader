#include<fstream>
#include<string>
#pragma once

using std::string;
using std::ifstream;

class MNIST_DS{
	string fileName;
	int n;
	int m;
	int magic_number;
	int number_of_items;
	Matrix* image_dat_set;
	unsigned char* label_dat_set;
	ifstream inFile;

	//Private methods
	void loadImages(string set);
	void loadLabels(string set);

public:
	MNIST_DS(string name);
	~MNIST_DS();
	void load();
	int reverseInt(int i);
};
