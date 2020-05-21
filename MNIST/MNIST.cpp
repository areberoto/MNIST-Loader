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
    //string fileName = "train-images.idx3-ubyte";
    //string fileName = "train-labels.idx1-ubyte";
    string fileImage = "t10k-images.idx3-ubyte";
    string fileLabel = "t10k-labels.idx1-ubyte";

    MNIST_DS data_set{ fileImage };
    MNIST_DS label_set{ fileLabel };
    data_set.load();
    label_set.load();

    Matrix image{ data_set.getImage(0) };
    int label{ label_set.getLabel(0) };
    
    cout << "Print first image: " << endl;
    cout << image << endl;
    cout << "Print label of image: " << label << endl;

    return 0;
}