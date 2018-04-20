/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: aminuibrahim
 *
 * Created on September 1, 2017, 2:26 PM
 */


#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib> 
#include "Passage.h"
#include "userInterface.h"

using namespace std;


int main(int argc, char** argv) {

    std::string file;
    std::cout << "\n\n------------------Text Analyzer-------------------\n\n";
    std::cout << "Input the FileName:";
    std::cin  >> file;
    
    ifstream inFile;
    inFile.open(file);
    
    if (!inFile) {
        std::cout << "Unable to open file " << file << " \n";
        exit(1);
    }
    Passage* passage = new Passage(file);
    userInterface* interface = new userInterface(passage); 
    interface->mainMenu();

   return 0;
}
