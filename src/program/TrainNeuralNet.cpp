//
//  TrainNeuralNet.cpp
//  NeuralNet
//
//  Created by Angel on 11/24/16.
//  Copyright © 2016 Angel. All rights reserved.
//

#include "TrainNeuralNet.hpp"
#include "NeuralNet.hpp"

TrainNeuralNet::TrainNeuralNet() {
    //open files
    string file_name;
    cout << "Please enter the initial neural network: ";
    cin >> file_name;
    init_file.open(file_name.c_str());
    if (!init_file) {
        cerr << "Error opening file\n";
        return;
    }
    cout << "Please enter the training set: ";
    cin >> file_name;
    train_file.open(file_name.c_str());
    if (!train_file) {
        cerr << "Error opening file\n";
        return;
    }
    cout << "Please enter the output file: ";
    cin >> file_name;
    output.open(file_name.c_str());
    if (!output) {
        cerr << "Error opening file\n";
        return;
    }
    //number of epochs
    cout << "Please enter the number of epochs: ";
    cin >> epochs;
    if(epochs <= 0) {
        cout << "Error: invalid value." << endl;
        return;
    }
    //learning rate
    cout << "Please enter the learning rate: ";
    cin >> learning_rate;
    if(learning_rate <= 0) {
        cout << "Error: invalid value." << endl;
        return;
    }
    net = NULL;
};

int TrainNeuralNet::LoadTrainingData() {
    string line;
    getline(train_file,line);
    stringstream ss(line);
    ss >> num_train;
    ss >> num_i >> num_o;
    if(num_i != net->num_i || num_o != net->num_o) {
        return -1;
    }
    string example;
    while(getline(train_file,example)) {
        training_set.push_back(example);
    }
    return 0;
}

void TrainNeuralNet::LoadTrainingExample(string example) {
    tmp_input.clear();
    tmp_output.clear();
    
    //initialize weights
    tmp_input.push_back(0);
    tmp_output.push_back(0);
    
    stringstream ss(example);
    double val;
    int pos = 1;
    while(ss >> val) {
        //first num_i goes to input vector
        if(pos <= num_i) {
            tmp_input.push_back(val);
            pos++;
        }else{//the rest goes to output vector
            tmp_output.push_back(val);
        }
    }
    return;
}

void TrainNeuralNet::BackPropLearning() {
    //load initial neural network
    net = new NeuralNet(init_file);
    //load training set
    if(LoadTrainingData() == -1) {
        cout << "Error loading training data." << endl;
        return;
    }
    //resize deltas
    delta_o.resize(num_o+1,0);
    delta_h.resize(net->num_h+1,0);
    
    //go through epochs
    for(int i = 1; i <= epochs; i++) {
        vector<string>::iterator itr = training_set.begin();
        for(; itr != training_set.end(); ++itr) {
            LoadTrainingExample(*itr);
            BackPropagate();
        }
    }
    SaveNet();
    return;
}
void TrainNeuralNet::BackPropagate() {
    //propagate the inputs forward
    for(int i = 1; i <= num_i; i++) {
        net->act_i[i] = tmp_input[i];
    }
    //compute activations for each node
    for(int j = 1; j < net->act_h.size(); j++) {
        //sum of products of current weight with all activations of previous layer
        for(int i = 0; i < net->act_i.size(); i++) {
            net->act_h[j] += net->weight_ih[i][j] * net->act_i[i];
        }
        net->act_h[j] = sigmoid(net->act_h[j]);
    }
    for(int j = 1; j < net->act_o.size(); j++) {
        for(int i = 0; i < net->act_h.size(); i++) {
            net->act_o[j] += net->weight_ho[i][j] * net->act_h[i];
        }
        net->act_o[j] = sigmoid(net->act_o[j]);
    }
    
    //propagate deltas backward
    for(int i = 1; i <= num_o; i++) {
        delta_o[i] = sigmoidDeriv(sigmoidInvs(net->act_o[i])) * (tmp_output[i] - net->act_o[i]);
    }
    //compute deltas
    for(int i = 0; i < delta_h.size(); i++) {
        for(int j = 1; j < delta_o.size(); j++) {
            delta_h[i] += net->weight_ho[i][j] * delta_o[j];
        }
        delta_h[i] *= sigmoidDeriv(sigmoidInvs(net->act_h[i]));
    }
    
    //update weights
    for(int i = 0; i < net->act_i.size(); i++) {
        for(int j = 1; j < delta_h.size(); j++) {
            net->weight_ih[i][j] += learning_rate * net->act_i[i] * delta_h[j];
        }
    }
    for(int i = 0; i < net->act_h.size(); i++) {
        for(int j = 1; j < delta_o.size(); j++) {
            net->weight_ho[i][j] += learning_rate * net->act_h[i] * delta_o[j];
        }
    }

    //reset
    fill(net->act_i.begin(), net->act_i.end(), 0);
    fill(net->act_h.begin(), net->act_h.end(), 0);
    fill(net->act_o.begin(), net->act_o.end(), 0);
    fill(delta_o.begin(), delta_o.end(), 0);
    fill(delta_h.begin(), delta_h.end(), 0);
    net->act_i[0] = -1;
    net->act_h[0] = -1;
    return;
}

//output results
void TrainNeuralNet::SaveNet() {
    output << net->num_i << " " << net->num_h << " " << net->num_o << endl;
    for(int h = 1; h <= net->num_h; h++) {
        output << fixed << setprecision(3) << net->weight_ih[0][h];
        for(int i = 1; i <= net->num_i; i++) {
            output << " " << fixed << setprecision(3) << net->weight_ih[i][h];
        }
        output << endl;
    }
    for(int o = 1; o <= net->num_o; o++) {
        output << fixed << setprecision(3) << net->weight_ho[0][o];
        for(int h = 1; h <= net->num_h; h++) {
            output << " " << fixed << setprecision(3) << net->weight_ho[h][o];
        }
        output << endl;
    }
    return;
}
