#include <iostream>
#include <string>
#include <fstream>
#include "Matrix.h"
#include "MNIST_DS.h"

using std::endl;
using std::cout;
using std::string;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::cerr;

//Constructor
MNIST_DS::MNIST_DS(string name) 
	: fileName{ name }, n{ 0 }, m{ 0 }, magic_number{ 0 }, number_of_items{ 0 }, image_dat_set{ nullptr },
    label_dat_set{ nullptr }, inFile{ name, ios::in | ios::binary | ios::ate } {

	if (!inFile) {
		cerr << "Error trying to open the file!\n" << endl;
		exit(1);
	}

    ifstream::pos_type size = inFile.tellg();
    inFile.seekg(0, ios::beg);
}

//Destructor
MNIST_DS::~MNIST_DS(){
	delete[] image_dat_set;
	delete[] label_dat_set;
}

//Load data
void MNIST_DS::load() {
	inFile.read(reinterpret_cast<char*>(&magic_number), sizeof(int));
	magic_number = reverseInt(magic_number);
	inFile.read(reinterpret_cast<char*>(&number_of_items), sizeof(int));
	number_of_items = reverseInt(number_of_items);

    if (magic_number == 2051 && number_of_items == 60000)
        loadImages(string{ "training" });
    else if (magic_number == 2051 && number_of_items == 10000)
        loadImages(string{ "test" });
    else if (magic_number == 2049 && number_of_items == 60000) 
        loadLabels(string{ "training" });
    else
        loadLabels(string{ "test" });
}

//Load images
void MNIST_DS::loadImages(string set) {
    inFile.read(reinterpret_cast<char*>(&n), sizeof(int));
    n = reverseInt(n);
    inFile.read(reinterpret_cast<char*>(&m), sizeof(int));
    m = reverseInt(m);

    unsigned char pixel{ 0 };
    Matrix image{ n, m };
    image_dat_set = new Matrix[number_of_items];

    if (NULL != image_dat_set) {
        cout << "Loading data set of " << set << " images..." << endl;
        for (size_t i{ 0 }; i < number_of_items; i++) {
            for (size_t j{ 0 }; j < n * m; j++) {
                inFile.read(reinterpret_cast<char*>(&pixel), sizeof(unsigned char));
                image[j] = pixel;
            }
            image_dat_set[i] = image;
        }
    }
    else {
        cerr << "Error trying to allocate dynamic memory!\n" << endl;
        exit(1);
    }

    cout << "Finished loading data set of " << set << " images..." << endl;
    inFile.close();
}

//Load labels
void MNIST_DS::loadLabels(string set) {
    unsigned char pixel{ 0 };
    label_dat_set = new unsigned char[number_of_items];

    if (NULL != label_dat_set) {
        cout << "Loading data set of " << set << " labels..." << endl;
        for (size_t i{ 0 }; i < number_of_items; i++) {
            inFile.read(reinterpret_cast<char*>(&pixel), sizeof(unsigned char));
            label_dat_set[i] = pixel;
        }
    }
    else {
        cerr << "Error trying to allocate dynamic memory!\n" << endl;
        exit(1);
    }

    cout << "Finished loading data set of " << set << " labels..." << endl;
    inFile.close();
}

//Convert raw bytes to int
int MNIST_DS::reverseInt(int i) {
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

//Get image
Matrix MNIST_DS::getImage(int index) {
    return image_dat_set[index];
}

//Get label
int MNIST_DS::getLabel(int index) {
    return static_cast<int>(label_dat_set[index]);
}