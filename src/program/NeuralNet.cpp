//
//  NeuralNet.cpp
//  NeuralNet
//
//  Created by Angel on 11/24/16.
//  Copyright © 2016 Angel. All rights reserved.
//

#include "NeuralNet.hpp"

using namespace std;

NeuralNet::NeuralNet() {};

NeuralNet::NeuralNet(ifstream &input) {
    LoadNeuralNet(input);
};

void NeuralNet::LoadNeuralNet(ifstream &input){

    //parsing the input file
    input>> num_i >> num_h >> num_o;
    
    //resize vectors acoording to the input
    act_i.resize(num_i+1, 0);
    act_h.resize(num_h+1, 0);
    act_o.resize(num_h+1, 0);
    
    //set bias
    act_i[0] = -1;
    act_h[0] = -1;
    
    //rezize weight vector
    vector<double> tmp_1 (num_h+1, 0);
    vector<double> tmp_2 (num_o+1, 0);
    weight_ih.resize(num_i+1, tmp_1);
    weight_ho.resize(num_h+1, tmp_2);
    
    //assign weights input->hidden
    double wgt_ih;
    for(int j = 1; j <= num_h; j++) {
        //include 0 for bias
        for(int i = 0; i <= num_i; i++) {
            input >> wgt_ih;
            weight_ih[i][j]= wgt_ih;
        }
    }
    
    //assign weights hidden->output
    double wgt_ho;
    for(int j= 1; j <= num_o; j++) {
        for(int i = 0; i <= num_h; i++) {
            input >> wgt_ho;
            weight_ho[i][j] = wgt_ho;
        }
    }
    return;
}
