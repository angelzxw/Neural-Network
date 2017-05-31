//
//  NeuralNet.hpp
//  NeuralNet
//
//  Created by Angel on 11/24/16.
//  Copyright © 2016 Angel. All rights reserved.
//

#ifndef NeuralNet_hpp
#define NeuralNet_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ios>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <csignal>
#include <cstring>
#include <unistd.h>
#include <math.h>

#define sigmoid(x) 1/(1+exp(-x))
#define sigmoidInvs(x) -log(1/x-1)
#define sigmoidDeriv(x) sigmoid(x)*(1-sigmoid(x))

using namespace std;

class NeuralNet {
    
public:
    
    //num of input, hidden and output nodes
    int num_i, num_h, num_o;
    
    //activation vector
    vector<double> act_i, act_h, act_o;
    
    //weight vectors: from input to hidden nodes and from hidden to output nodes
    vector<vector<double> > weight_ih, weight_ho;
    
    //constructor
    NeuralNet();
    NeuralNet(ifstream &input_file);
    
    //parse input file and load data
    void LoadNeuralNet(ifstream &input_file);
    
    //friend classes that can access its variables
    friend class TrainNeuralNet;
    friend class TestNeuralNet;
};





#endif /* NeuralNet_hpp */
