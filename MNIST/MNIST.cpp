// MNIST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Matrix.h"
#include "MNIST_DS.h"
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(){
    string fileName = "train-images.idx3-ubyte";
    //string fileName = "train-labels.idx1-ubyte";
    //string fileName = "t10k-images.idx3-ubyte";
    //string fileName = "t10k-labels.idx1-ubyte";

    MNIST_DS data_set{ fileName };
    data_set.load();

    return 0;
}