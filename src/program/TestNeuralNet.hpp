//
//  TestNeuralNet.hpp
//  NeuralNet
//
//  Created by Angel on 11/24/16.
//  Copyright © 2016 Angel. All rights reserved.
//

#ifndef TestNeuralNet_hpp
#define TestNeuralNet_hpp

#include <stdio.h>
#include "NeuralNet.hpp"

class TestNeuralNet{
    
    ifstream net_file, test_file;
    ofstream output;
    NeuralNet *net;
    int num_test;
    int num_i, num_o;
    
    //testing data
    vector<string> testing_set; //testing data set
    vector<double> tmp_input; //input data for one training example
    vector<bool> tmp_expected, tmp_predicted ; //expected and actual output data for one testing example
    
    //vector for A,B,C,D
    vector<vector<int> > counts;
    
    //vector for overall accuracy, precision, recall, and F1 for each category
    vector<vector<double> > metrics;
    
    //vectors for micro and macro averages for overall accuracy, precision, recall, and F1
    vector<double> microavg, macroavg;

public:
    
    TestNeuralNet();
    
    int LoadTestingData();
    void LoadTestingExample(string testing_ex);
    void Test();
    
    //compute outputs
    void ComputeOutputs();
    
    //catigorize
    void CompareOutputs();
    
    //compute metrics
    void ComputeMetrics();
    
    void Save();
    double CalcAccuracy(int A, int B, int C, int D);
    double CalcPrecision(int A, int B);
    double CalcRecall(int A, int C);
    double CalcF1(double precision, double recall);
};

#endif /* TestNeuralNet_hpp */
