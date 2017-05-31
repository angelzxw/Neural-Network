//
//  TrainNeuralNet.hpp
//  NeuralNet
//
//  Created by Angel on 11/24/16.
//  Copyright © 2016 Angel. All rights reserved.
//

#ifndef TrainNeuralNet_hpp
#define TrainNeuralNet_hpp

#include <stdio.h>
#include "NeuralNet.hpp"

class TrainNeuralNet{

    ifstream init_file, train_file;
    ofstream output;
    int epochs;
    double learning_rate;
    NeuralNet *net;
    int num_train;
    int num_i, num_o;
    
    //training data
    vector<string> training_set;
    vector<double> tmp_input; //input data for one training example
    vector<bool> tmp_output; //output data for one training example
    
    vector<double> delta_o, delta_h;
    
public:
    TrainNeuralNet();
    
    //parse training file and load training examples
    int LoadTrainingData();
    
    // Take string data and convert it into numeric data in vector
    void LoadTrainingExample(string training_ex);
    
    //back propagation learning
    void BackPropLearning();
    
    //back propagation learning with one training example
    void BackPropagate();

    //save trained network to output file
    void SaveNet();
};

#endif /* TrainNeuralNet_hpp */
