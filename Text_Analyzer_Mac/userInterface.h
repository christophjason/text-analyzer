/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   userInterface.h
 * Author: aminuibrahim
 *
 * Created on September 7, 2017, 11:45 AM
 */

#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "Passage.h"
class userInterface {
public:
    userInterface(Passage* passage);
    userInterface(const userInterface& orig);
    virtual ~userInterface();
    
    void count();
    void find();
    void replace();
    void caseOperation();
    void joinFiles();
    int  goBack();
    void clearScreen();
    int  mainMenu();
    void retry( int flag);
private:
    Passage* passage;
};

#endif /* USERINTERFACE_H */

