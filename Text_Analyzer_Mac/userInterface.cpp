/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   userInterface.cpp
 * Author: aminuibrahim
 * 
 * Created on September 7, 2017, 11:45 AM
 */

#include "userInterface.h"
#include <cstdlib>
#include <iostream>

userInterface::userInterface(Passage* passage) {
    this->passage = passage;
}

userInterface::userInterface(const userInterface& orig) {
}

userInterface::~userInterface() {
}
/**
 * 
 * @Author
 *      Christopher Jason S 
 *      kembabazi Barbara Gamukama Yihong
 * @function
 *      Prints the Main Menu
 *         
 */

int userInterface::mainMenu(){
        clearScreen();
	int input;
        std::cout<<"------------------Text Analyzer-----------------\n\n";
        std::cout<<"1) Count\n";
	std::cout<<"2) Find\n";
	std::cout<<"3) Replace\n";
	std::cout<<"4) Case Operation\n";
	std::cout<<"5) Join Files\n";
        std::cout<<"6) Exit\n";
	std::cout<<"What would you like to do?: ";
	std::cin>>input;
	
	switch(input){
		case 1:
			count();
                        break;
		case 2:
			find();
                        break;
		case 3:
			replace();
                        break;
		case 4:
			caseOperation();
                        break;
		case 5:
			joinFiles();
                        break;        
                case 6:
			exit(1);
                        break;
		default: 
                    exit(1); 				
	}
	return 0;
}
/**
 * 
 * @Author
 *      Christopher Jason S 
 *      kembabazi Barbara Gamukama Yihong
 * @function
 *      Prints the count interface
 *         
 */
void userInterface::count(){
      clearScreen();
      
      std::cout<<"------------------Text Analyzer-----------------\n";
      std::cout<<"-------------------COUNT------------------------\n";
      
      this->passage->noSentences();
      this->passage->noWords();
      this->passage->noBlankSpaces();
      this->passage->noCapitalLetters();
      this->passage->noPunctuationMarks();
      this->passage->printWordOccurences();

      goBack();
}
/**
 * 
 * @Author
 *      Christopher Jason S 
 *      kembabazi Barbara Gamukama Yihong
 * @function
 *      Prints the Find Interface
 *         
 */	
void userInterface::find(){
        clearScreen();
	std::cout<<"------------------Text Analyzer-----------------\n";
	std::cout<<"--------------------FIND------------------------\n";
        std::cout<<"Input 1 for case sensitive or 2 for case search Insensitive: ";
        int type;
        std::cin >>type;
	std::cout<<"Input the word you want to find: ";
        
        std::string word;
        std::cin >> word;
        
        if(type == 1){
            this->passage->findWord(word);
        }else{
            this->passage->findWordInsenstive(word);
        }
	retry(2);
}
/**
 * 
 * @Author
 *      Christopher Jason S 
 *      kembabazi Barbara Gamukama Yihong
 * @function
 *      Prints the replace interface
 *         
 */	
void userInterface::replace(){
        clearScreen();
	std::cout<<"------------------Text Analyzer-----------------\n";
	std::cout<<"---------------------REPLACE--------------------\n";
	std::cout<<" Input the word you want to find: ";
        std::string word;
        std::cin >> word;
	this->passage->findWord(word);
	std::cout<<"Replace with: ";
        std::string rword;
        std::cin >> rword;
        this->passage->replaceWord(word,rword);

	goBack();
}
/**
 * 
 * @Author
 *      Christopher Jason S 
 *      kembabazi Barbara Gamukama Yihong
 * @function
 *      Prints case operation interface
 *         
 */
void userInterface::caseOperation(){
        clearScreen();
	int c;
	std::cout<<"\n--------------------Text Analyzer-----------------------\n";
	std::cout<<"----------------------CASE OPERATION----------------------\n";
	std::cout<<"1) Uppercase all\n";
	std::cout<<"2) Lowercase all\n";
	std::cout<<"3) Sentence case\n";
        std::cout<<"4) Back to Main Menu\n";
        std::cout << "What would you like to do?: ";
        std::cin >> c;
       
	switch(c){
	    case 1:
                clearScreen();
                this->passage->printToUpperAll();

                break;
	    case 2:
                clearScreen();
                this->passage->printToLowerAll();
                break;
	    case 3:
                clearScreen();
                this->passage->capitalizeFirstLetter();
                break;
            case 4:
                goBack(); 
                break;
	    default : 
                goBack();
         }

	retry(1);
}
/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 *      Christopher Jason S 
 *      kembabazi Barbara Gamukama Yihong
 * @function
 *      Prints case operation interface
 *    flag 1 = return to caseOperation Menu
 *    flag 2 =  return to      
 */

void userInterface::retry( int flag){
 std::cout << "\nPress 1 to return to previous menu";
 std::cout << "\nPress 2 to return to Main menu";
 std::cout << "\nPress 3 to return Exit \n";
    int inp;
    std::cout << "input: ";
    std::cin >> inp;
    switch(inp){
        case 1:
            if(flag == 1){
                caseOperation();
            }
             else if(flag == 2){
                 find();
            }
             else if(flag == 3){
                
            }   
            break;
        case 2:
           mainMenu();;
            break;
        case 3:
            exit(1);
            break;
    }
}
/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 *      Christopher Jason S 
 *      kembabazi Barbara Gamukama Yihong
 * @function
 *      Prints join file interface
 *         
 */
void userInterface::joinFiles(){
        clearScreen();
	std::cout<<"\n------------------Text Analyzer------------------------\n";
	std::cout<<"---------------------JOIN FILES--------------------------\n";
	std::cout<<"Input name of the file you want to join: ";
        std::string fileName;
        std::cin >> fileName;
	bool joinFile = this->passage->joinFile(fileName);
        if(joinFile == true){
            std::cout << "Files Successfully Joined in joined.txt \n"; 
        }else{
            std::cout << "Files were not Successfully Joined\n"; 
        }
	goBack();
}
/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 *      Christopher Jason S 
 *      kembabazi Barbara Gamukama Yihong
 * @function
 *      Prints ho back interface and operation
 *          
 */	
int userInterface::goBack(){
	char i;
        std::cout << "\npress 0 to go back to the Main Menu:";
	std::cin>>i;
	if(i=='0'){
            clearScreen();
	    mainMenu();
	}
          std::cout << "\n--------------BYE----------------\n";
          //exit
          exit(1);
           
}
/**
 * 
 * @Author
 *      Christopher Jason S 
 *      
 * @function
 *     clear the screen
 *        
 */
void userInterface::clearScreen(){
	#ifdef WINDOWS
	system("cls");
	#endif
	system("clear");

        
}
