//
//  TestNeuralNet.cpp
//  NeuralNet
//
//  Created by Angel on 11/24/16.
//  Copyright © 2016 Angel. All rights reserved.
//

#include "TestNeuralNet.hpp"
#include "NeuralNet.hpp"

TestNeuralNet::TestNeuralNet() {
    string file_name;
    //open files
    cout << "Please enter trained neural network: ";
    cin >> file_name;
    net_file.open(file_name.c_str());
    if (!net_file) {
        cerr << "Error opening file\n";
        return;
    }
    cout << "Please enter test file: ";
    cin >> file_name;
    test_file.open(file_name.c_str());
    if (!net_file) {
        cerr << "Error opening file\n";
        return;
    }
    cout << "Please enter output file: ";
    cin >> file_name;
    output.open(file_name.c_str());
    if (!net_file) {
        cerr << "Error opening file\n";
        return;
    }
    net = NULL;
};

int TestNeuralNet::LoadTestingData() {
    string line;
    getline(test_file,line);
    stringstream ss(line);
    ss >> num_test;
    ss >> num_i >> num_o;
    if(num_i != net->num_i || num_o != net->num_o) {
        return -1;
    }
    string example;
    while(getline(test_file,example)) {
        testing_set.push_back(example);
    }
    return 0;
}

void TestNeuralNet::LoadTestingExample(string example) {
    tmp_input.clear();
    tmp_predicted .clear();
    tmp_expected.clear();
    
    //initialize weights
    tmp_input.push_back(0);
    tmp_predicted .push_back(0);
    tmp_expected.push_back(0);
    
    stringstream ss(example);
    
    double val;
    int pos = 1;
    while(ss >> val) {
        //first num_i goes to input vector
        if(pos <= num_i) {
            tmp_input.push_back(val);
            pos++;
        }else{//the rest goes to output vector
            tmp_expected.push_back(val);
        }
    }
    return;
}

void TestNeuralNet::Test() {
    //load initial trained neural network
    net = new NeuralNet(net_file);
    //load testing data
    if(LoadTestingData() == -1) {
        cout << "Error: loading testing data." << endl;
        return;
    }
    
    //initialize vectors
    vector<int> tmp_1(4,0);
    vector<double> tmp_2(4,0);
    counts.resize(num_o+1,tmp_1);
    metrics.resize(num_o+1,tmp_2);
    microavg.resize(4,0);
    macroavg.resize(4,0);
    
    //go through testing examples
    vector<string>::iterator itr = testing_set.begin();
    for(; itr != testing_set.end(); ++itr) {
        LoadTestingExample(*itr);
        ComputeOutputs();
        CompareOutputs();
    }
    
    ComputeMetrics();
    Save();
    
    return;
}

void TestNeuralNet::ComputeOutputs() {
    for(int i = 1; i <= num_i; i++) {
        net->act_i[i] = tmp_input[i];
    }
    for(int j = 1; j < net->act_h.size(); j++) {
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
    
    //round the activations
    for(int j = 1; j <= num_o; j++) {
        tmp_predicted .push_back(net->act_o[j] >= 0.5 ? 1 : 0);
    }
    
    //reset
    fill(net->act_i.begin(), net->act_i.end(), 0);
    fill(net->act_h.begin(), net->act_h.end(), 0);
    fill(net->act_o.begin(), net->act_o.end(), 0);
    net->act_i[0] = -1;
    net->act_h[0] = -1;
    
    return;
}

void TestNeuralNet::CompareOutputs() {
    for(int j = 1; j <= num_o; j++) {
        //A: 1, 1
        if(tmp_predicted [j] && tmp_expected[j]) {
            counts[j][0]++;
        }
        //B: 1, 0
        else if(tmp_predicted [j] && !tmp_expected[j]) {
            counts[j][1]++;
        }
        //C: 0, 1
        else if(!tmp_predicted [j] && tmp_expected[j]) {
            counts[j][2]++;
        }
        //dD: 0, 0
        else if(!tmp_predicted [j] && !tmp_expected[j]) {
            counts[j][3]++;
        }
    }
    return;
}


void TestNeuralNet::ComputeMetrics() {
    
    //sum of A,B,C,D
    int act_tot = 0, B_tot = 0, C_tot = 0, D_tot = 0;
    //sum of metrics
    double overall_acc_tot = 0, precisionum_tot = 0, recall_tot = 0;
    
    for(int j = 1; j <= num_o; j++) {
        int A = counts[j][0];
        int B = counts[j][1];
        int C = counts[j][2];
        int D = counts[j][3];
        act_tot += A;
        B_tot += B;
        C_tot += C;
        D_tot += D;
        
        //calculate metrics
        metrics[j][0] = CalcAccuracy(A,B,C,D);
        metrics[j][1] = CalcPrecision(A,B);
        metrics[j][2] = CalcRecall(A,C);
        metrics[j][3] = CalcF1(metrics[j][1],metrics[j][2]);
        
        overall_acc_tot += metrics[j][0];
        precisionum_tot += metrics[j][1];
        recall_tot += metrics[j][2];
    }
    
    //microaverages
    microavg[0] = CalcAccuracy(act_tot,B_tot,C_tot,D_tot);
    microavg[1] = CalcPrecision(act_tot,B_tot);
    microavg[2] = CalcRecall(act_tot,C_tot);
    microavg[3] = CalcF1(microavg[1],microavg[2]);
    
    //macroaverages
    macroavg[0] = overall_acc_tot/(double)num_o;
    macroavg[1] = precisionum_tot/(double)num_o;
    macroavg[2] = recall_tot/(double)num_o;
    macroavg[3] = CalcF1(macroavg[1],macroavg[2]);
    
    return;
}
void TestNeuralNet::Save() {
    for(int i = 1; i <= num_o; i++) {
        int A = counts[i][0];
        int B = counts[i][1];
        int C = counts[i][2];
        int D = counts[i][3];
        double overall_acc = metrics[i][0];
        double precision = metrics[i][1];
        double recall = metrics[i][2];
        double F1 = metrics[i][3];
        output << fixed << setprecision(3)
        << A << " " << B << " " << C << " " << D << " "
        << overall_acc << " " << precision << " " << recall << " " << F1 << endl;
    }
    //save microaverages and macroaverages
    output << fixed << setprecision(3) << microavg[0] << " " << microavg[1] << " " << microavg[2] << " " << microavg[3] << endl;
    output << fixed << setprecision(3) << macroavg[0] << " " << macroavg[1] << " " << macroavg[2] << " " << macroavg[3] << endl;
    
    return;
}
double TestNeuralNet::CalcAccuracy(int A, int B, int C, int D) {
    return (double)(A+D)/(A+B+C+D);
}

double TestNeuralNet::CalcPrecision(int A, int B) {
    return (double)A/(A+B);
}

double TestNeuralNet::CalcRecall(int A, int C) {
    return (double)A/(A+C);
}

double TestNeuralNet::CalcF1(double precision, double recall) {
    return 2*precision*recall/(precision+recall);
}
