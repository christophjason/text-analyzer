/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Passage.h
 * Author: aminuibrahim
 *
 * Created on September 1, 2017, 3:26 PM
 */

#ifndef PASSAGE_H
#define PASSAGE_H
#include <string>
#include <vector>
#include <fstream>

#include <unordered_map>
class Passage {
public:
    Passage(std::string file);
    Passage(const Passage& orig);
    virtual ~Passage();
    
    std::string getPassage();
    std::string getToUpperAll();
    std::string getToLowerAll();
    
    std::vector<std::string> getWords();
    std::vector<std::string> getSentences();
    std::unordered_map<std::string, int> getWordOccurence();
    
    
    void findWord(std::string word); 
    void findWordInsenstive(std::string word);
    void replaceWord(std::string word, std::string replacement);
    void capitalizeFirstLetter();
   
    
    int noBlankSpaces(int flag = 0);
    int noCapitalLetters(int flag = 0); 
    int noPunctuationMarks(int flag = 0);
    int noSentences(int flag = 0);
    int noWords(int flag = 0);
    
    void printToUpperAll();
    void printToLowerAll();
    void printWordOccurences();
    void printWords();
    void printSentences();
    void printPassage();
    
    bool joinFile(const std::string fileName2);  
  
    void lowerCase(std::string& strToConvert);
    bool isSentencePunc(char character);
    
    //vectors
    std::vector<std::string> passageWords;
    std::vector<std::string> passageSentences;
    std::vector<char> passagePunctuationMarks;
    
    //hash maps
    std::unordered_map<std::string, int> wordOccurence;
        
private:
    //fileNames
    std::string fileName;
    
    
    //texts
    std::string passageText;
    std::string passageToUpperAllText;
    std::string passageToLowerAllText;
    
    //number counts
    int punctuationsCount;
    int wordsCount;
    int sentencesCount;
    int blankSpacesCount;
    
    //helper functions
    bool capitalLetter(char character);
    int findCaseInsensitive(std::string data, std::string toSearch, int pos = 0);
    
};

#endif /* PASSAGE_H */

