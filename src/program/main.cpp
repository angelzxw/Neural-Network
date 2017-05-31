//
//  main.cpp
//  NeuralNet
//
//  Created by Angel on 11/24/16.
//  Copyright © 2016 Angel. All rights reserved.
//

#include <iostream>
#include "NeuralNet.hpp"
#include "TrainNeuralNet.hpp"
#include "TestNeuralNet.hpp"

int main(int argc, const char * argv[]) {
    while(true) {
        int opt;
        while(true) {
            cout << "Please select one of the following:" << endl;
            cout << "1. Train" << endl;
            cout << "2. Test" << endl;
            cout << "3. Exit" << endl;
            cin >> opt;
            if(opt != 1 && opt != 2 && opt != 3) {
                cout << "Invalid input" << endl;
            }else {
                break;
            }
            cout << endl;
        }
        switch(opt) {
            case 1:
            {
                cout << "Start Training Program." << endl;
                TrainNeuralNet trainer;
                trainer.BackPropLearning();
                cout << "Training Completed." << endl;
                cout << endl;
                break;
            }
            case 2:
            {
                cout << "Start Testing..." << endl;
                TestNeuralNet tester;
                tester.Test();
                cout << endl;
                cout << "Testing Completed." << endl;
                break;
            }
            case 3:
            {
                cout << "Exiting program." << endl;
                exit(0);
            }
        }
    }
    return 0;
}
