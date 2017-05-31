//
//  main.cpp
//  data
//
//  Created by Angel on 12/17/16.
//  Copyright © 2016 Angel. All rights reserved.
//

#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h> 

using namespace std;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

int main() {
    
    ifstream inFile("student_por.data");
    ofstream outFile("student_por.train");
    
    string line;
    int index = 0;
    while (getline(inFile, line)) {
        if (index % 2 == 1) {
            vector<string> tokens = split(line, ';');
            // Get inputs
            for (int i = 0; i < 33; ++i) {
                double tmp = stod (tokens[i]);
                switch (i) {
                    case 2:
                        tmp = tmp/22;
                        break;
                    case 6:
                        tmp = tmp/4;
                        break;
                    case 7:
                        tmp = tmp/4;
                        break;
                    case 8:
                        tmp = tmp/2;
                        break;
                    case 9:
                        tmp = tmp/2;
                        break;
                    case 10:
                        tmp = tmp/1.5;
                        break;
                    case 12:
                        tmp = tmp/4;
                        break;
                    case 13:
                        tmp = tmp/4;
                        break;
                    case 14:
                        tmp = tmp/4;
                        break;
                    case 23:
                        tmp = tmp/5;
                        break;
                    case 24:
                        tmp = tmp/5;
                        break;
                    case 25:
                        tmp = tmp/5;
                        break;
                    case 26:
                        tmp = tmp/5;
                        break;
                    case 27:
                        tmp = tmp/5;
                        break;
                    case 28:
                        tmp = tmp/5;
                        break;
                    case 29:
                        tmp = tmp/93;
                        break;
                    case 30:
                        tmp = tmp/20;
                        break;
                    case 31:
                        tmp = tmp/20;
                        break;
                    case 32:
                        tmp = tmp/20;
                        break;
                        
                    default:
                        break;
                }
                tmp = roundf(tmp * 1000) / 1000;
                outFile << tmp << " ";
            }
            outFile << endl;
        }
        
        ++index;
    }
    
    inFile.close();
    outFile.close();
    
    return 0;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
