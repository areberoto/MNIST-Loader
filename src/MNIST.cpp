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

    //If true, training data is loaded, else test data
    MNIST_DS data_set{ false };

    Matrix image{ data_set.getImage(0) };
    int label{ data_set.getLabel(0) };
    
    cout << "Print first image: " << endl;
    cout << image << endl;
    cout << "Print label of image: " << label << endl;

    cout << "Print random mini batch: " << endl;
    data_set.randomSet(10);

    for (size_t i{ 0 }; i < 10; i++) {
        cout << data_set.getMiniBatchImages()[i] << endl;
        cout << "Label: " << (int) data_set.getMiniBatchLabels()[i] << endl;
    }
    
    return 0;
}