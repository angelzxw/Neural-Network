//
//  main.cpp
//  init
//
//  Created by Angel on 12/17/16.
//  Copyright © 2016 Angel. All rights reserved.
//


#include <fstream>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main() {
    
    srand(time(NULL));
    
    ofstream outFile("student_20.init");
    
    int numInputs = 32, numOutputs = 1;
    int numHidden;
    cout << "Enter the number of nodes in the hidden layer: ";
    cin >> numHidden;
    
    outFile << numInputs << " " << numHidden << " " << numOutputs << endl;
    
    // Generate random weights
    for (int i = 0; i < numHidden; ++i) {
        for (int j = 0; j < numInputs + 1; ++j) {
            double w = ((double) rand() / (RAND_MAX));
            outFile.precision(3);
            outFile << fixed << w;
            if (j != numInputs) {
                outFile << " ";
            }
        }
        outFile << endl;
    }
    for (int i = 0; i < numOutputs; ++i) {
        for (int j = 0; j < numHidden + 1; ++j) {
            double w = ((double) rand() / (RAND_MAX));
            outFile.precision(3);
            outFile << fixed << w;
            if (j != numHidden) {
                outFile << " ";
            }
        }
        outFile << endl;
    }
    
    outFile.close();
    
    return 0;
}
