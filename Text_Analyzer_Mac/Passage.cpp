/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Passage.cpp
 * Author: aminuibrahim
 * 
 * Created on September 1, 2017, 3:26 PM
 */

#include "Passage.h"
#include <cstdio>
#include <string>
#include <cstring>
#include <regex>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib> 
#include <locale>

/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 *      1820151002
 * @function 
 *  A consturctor for the Passage Class. it sets the passage file as the fileName 
 *  that was passed to it.
 *   
 * Constructor: Passage(std::string file)
 *      
 * POST CONDITION:
 *      sets the fileName
 *      sets the vector PasssageWords with all the words in the Passage
 *      sets the string passageText with the text in the passage
 *      sets the vector Passage Sentences with the sentences in the passage   
 */
Passage::Passage(std::string file) {
    this->fileName = file;
    this->passageWords = this->getWords();
    this->passageText = this->getPassage();
    this->passageSentences = this->getSentences();
}

Passage::Passage(const Passage& orig) {
}

Passage::~Passage() {
}

/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 *      1820151002
 * @function std::string Passage::getPassage()
 *      gets the passage Text and stores it in the passageText String
 * @return
 *  returns a string containing the text in the passage
 *         
 */
std::string Passage::getPassage(){

    std::string getContent;
    std::ifstream openfile(this->fileName);
    if(openfile.is_open())
    {
        while(!openfile.eof())
        {
            getline(openfile, getContent);
         
        }
    }
    openfile.close();
    this->passageText = getContent;
    //return the a string containing the passage.
    return this->passageText;
}

/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 *      1820151002
 * @function Passage::printPassage()
 *      prints out a Passage heading and the text of the passage below
 * 
 *  
 *         
 */
void Passage::printPassage(){
    std::cout << "\n\n--------------------Passage------------------\n\n";
    std::cout << this->passageText;
}

/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 *      1820151002
 * @function
 *      gets all the words in the passage and stores them in a string vector 
 *      sets the wordOccurence vector with the number of occurence of each word 
 * @return
 *  returns a string vector containing all space separated words in the passage
 *         
 */
std::vector<std::string> Passage::getWords(){ 
    
    std::ifstream inFile;
    inFile.open(this->fileName);
    std::string word;
  
    while (inFile >> word) {
     
        //saves the position of the first matching punctuation
        //return string::npos if no occurence is found
        int found = word.find_first_of(" .,?!()\""); 
        
        //remove punctuation marks from words by replacing with empty space
        while (found!=std::string::npos){
              word[found]='\0'; // \0 is used to represent an empty space
              found=word.find_first_of(".,?!()",found+1);
        }
        this->passageWords.push_back(word);
        std::unordered_map<std::string,int>::const_iterator got = this->wordOccurence.find(word);
        if(got == this->wordOccurence.end()){
            //word does not exist yet so insert and put 1 as the number of times
            this->wordOccurence.insert(std::make_pair<std::string,int>(word,1));
        }else{
            //word exist so update the number of occurence
            this->wordOccurence.at(word) += 1;
        }   
    }
    inFile.close();
    return this->passageWords;
}
/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 *      1820151002
 * @function Passage::noWords()
 *      prints out the number of words if the default flag is not changed
 *      only gets the number of words in the default flag is changed
 * @return
 *      returns the number of words
 *         
 */
int Passage::noWords(int flag){
    
    int nowrd = passageWords.size();
    if(flag == 0){
        std::cout << "No of Words: "  << nowrd << "\n\n";
    }
    return nowrd;
}

/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 *      1820151002
 * @function void Passage::printWordOccurences()
 *      
 *      prints headers and a list of words and occurences
 *  
 *  
 *         
 */
void Passage::printWordOccurences(){
     std::cout << "\n\n--------------------WORD OCCURRENCES------------------\n\n";
    std::cout << " WORD:OCCURRENCE\n\n";
    for (auto it =  this->wordOccurence.begin();
        it !=  this->wordOccurence.end(); ++it ){
       
        std::cout << " " << it->first << ":" << it->second;
        std::cout << std::endl;
    }
}
/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 *      1820151002
 * @function 
 *      std::unordered_map<std::string, int> Passage::getWordOccurence()     
 * @return
 *      returns the wordOccurence unordered_map
 *         
 */
std::unordered_map<std::string, int> Passage::getWordOccurence(){
    return this->wordOccurence;
}

/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 *      1820151002
 * @function
 *      gets all the sentences in the passage, sentences are a group of words or
 *      phrases that end with a , the function stores the sentences in a string 
 *      vector 
 * @return
 *  returns a string vector containing all , separated sentences in the passage
 *         
 */
std::vector<std::string> Passage::getSentences(){
    
    std::string passage = this->passageText;
    std::string sentence;
    std::vector<std::string> localSentences;
    int sentenceCount = 0;
    std::regex sep ("[.]+");
    std::sregex_token_iterator tokens(passage.cbegin(), passage.cend(), sep, -1);
    std::sregex_token_iterator end;
    
    for(; tokens != end; ++tokens){
          localSentences.push_back(*tokens);
          sentenceCount++;
    }
    
    this->sentencesCount = sentenceCount;
    for(int i = 0; i < localSentences.size(); i++){
        std::string curr = localSentences[i];
        char front = curr.front();
        char back = curr.back();
        if(front == ' '){
            curr[0] = '\0';
            if(curr[1] == ' ')
            curr[1] = '\0';
            
        }
        if(back == ' '){
            curr[curr.size()] = '\0';
            back = curr.back();
        }
     
        this->passageSentences.push_back(curr);
    }

    return this->passageSentences;
}

/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 *      1820151002
 * @function Passage::printWords()
 *      
 *      prints a header 
 *      --------------------All Words------------------
 *      and a list of words in the passage under.        
 */
void Passage::printWords(){
    std::cout << "\n\n--------------------All Words------------------\n\n";
 
    for(int i = 0; i < this->passageWords.size(); i++){
        std::cout << " " << this->passageWords[i] << std::endl;
    }
}

/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 *      1820151002
 * @function
 *      prints a header 
 *      --------------------All Sentences------------------
 *      and a list of sentences in the passage
 *         
 */
void Passage::printSentences(){
    std::cout << "\n\n--------------------All Sentences------------------\n\n";
 
    for(int i = 0; i < this->passageSentences.size(); i++){
        std::string curr = this->passageSentences[i];
        std::cout << "\nSentence " << i + 1 << ":\n"<< curr << "\n";
        
    }
}

/**
 * 
 * @Author
 *      Christopher Jason S 
 *      Student ID: 1820151020
 * @function std::string Passage::getToUpperAll()
 *      A function that changes the file contents into upper case format
 * @return
 *      returns a string with all the passage contents in uppercase
 *         
 */
std::string Passage::getToUpperAll(){
  
    
  std::locale loc;
  std::string str = this->passageText;

  std::string us;
  for (int i=0; i<str.length(); i++){
      us.push_back(std::toupper(str[i]));
      
  }
 
  std::fstream inFile;
  inFile.open(fileName,std::ios::out);
  inFile<<us; //write  the new upper string to the file
  this->passageToUpperAllText = us;
  return this->passageToUpperAllText;
  
}

/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 * @function
 *      prints the the passage contents in uppercase
 *          
 */
void Passage::printToUpperAll(){
  std::string str = this->getToUpperAll();
  std::cout << "--------------toUpperAll-----------------\n\n";       
  std::cout << str << "\n\n";
}



/**
 * 
 * @Author
 *      Christopher Jason S 
 *      Student ID: 1820151020
 * @function
 *      changes all the content of the file to lower case
 * @return
 *  returns a string containing the passage in lower case format
 *         
 */
std::string Passage::getToLowerAll(){
  
  std::locale loc;
  std::string str = this->passageText;

  std::string ls;
  for (int i=0; i<str.length(); i++){
      ls.push_back(std::tolower(str[i]));   
  }
  std::fstream inFile;
  inFile.open(fileName,std::ios::out);
  inFile<<ls;
  this->passageToLowerAllText = ls;
 
  return   this->passageToLowerAllText;
}

/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 * @function Passage::printToLowerAll()
 *      prints a header 
 *      --------------toLowerAll-----------------
 *      and the passage in lower case beneath the header
 * 
 *  
 *         
 */
void Passage::printToLowerAll(){
  
 
   std::string str = this->getToLowerAll();
  
    std::cout << "--------------toLowerAll-----------------\n\n";       
    std::cout << str << "\n\n";
}
/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 * @function int Passage::noSentences(int flag = 0)
 *      returns a count of the number of sentences in the passage
 *      if default flag is not changed, it prints the number of sentences
 *  @return
 *      returns the no of sentences in the passage
 *         
 */  
int Passage::noSentences(int flag){
    int noSen =  this->passageSentences.size();
    if(flag == 0)
    std::cout << "No of Sentences: " << noSen << "\n\n";
    return noSen;
}

/**
 * 
 * @Author
 *      Christopher Jason S 
 *      Student ID: 1820151020
 * @function
 *      counts the number of blank spaces in the passage,
 *       if default flag is not changed, it prints the number of blank spaces
 * @return
 *      returns the number of blank spaces
 *         
 */
int Passage::noBlankSpaces(int flag){
        std::ifstream inFile;
        std::string lfileName = this->fileName;
	inFile.open(lfileName);
	char c;
	int count=0;
	while(!inFile.eof())
	{
            inFile.get(c);
            if(c==' ')
            count++;
	}
        if(flag == 0)
	std::cout<<"Number of blank spaces: "<<count << "\n\n";
	inFile.close();
        this->blankSpacesCount = count;
        return this->blankSpacesCount;
}
/**
 * 
 * @Author
 *      Christopher Jason S 
 *      Student ID: 1820151020
 * @function
 *        counts the number of capital letters in the passage,
 *       if default flag is not changed, it prints the number of capital letters
 * @return
 *      returns the number of capital letters
 *         
 */
int Passage::noCapitalLetters(int flag){
    std::ifstream inFile;
    inFile.open(this->fileName);
    char c;
    int count=0;
    while(!inFile.eof()){
        inFile.get(c);
        if(capitalLetter(c)){
            count++;
        }
       
    }
    if(flag == 0)
    std::cout<<"Number of Capital Letters: "<<count << "\n\n";
    inFile.close();
    return count;
}
/**
 * 
 * @Author
 *      Christopher Jason S 
 *      Student ID: 1820151020
 * @function bool Passage::capitalLetter(char character)
 *      
 * @return
 *  returns true if the char is capital, false otherwise
 *         
 */
bool Passage::capitalLetter(char character){
    switch(character){
        case 'A':
             return true;
        case 'B':
             return true;
        case 'C':
             return true;
        case 'D':
             return true;
        case 'E':
             return true;
        case 'F':
             return true;
        case 'G':
             return true;
        case 'H': 
             return true;
        case 'I':
             return true;
        case 'J':
             return true;
        case 'K':
             return true;
        case 'L':
             return true;
        case 'M':
             return true;
        case 'N':
             return true;
        case 'O':
             return true;
        case 'P':
             return true;
        case 'Q':
             return true;
        case 'R':
             return true;
        case 'S':
             return true;
        case 'T':
             return true;
        case 'U':
             return true;
        case 'V':
             return true;
        case 'W':
             return true;
        case 'X':
             return true;
        case 'Y':
             return true;
        case 'Z':
              return true;
        default: 
            return false;
    }
}

/**
 * 
 * @Author
 *      Christopher Jason S 
 *      Student ID: 1820151020
 * @function
 *       counts the number of punctuation marks in the passage,
 *       if default flag is not changed, it prints the number of punctuation marks
 * @return
 *      returns the number of punctuation marks
 *         
 */
int Passage::noPunctuationMarks(int flag){
        std::ifstream inFile;
	inFile.open(this->fileName);
	char c;
	int count=0;
	while(!inFile.eof())
	{
		inFile.get(c);
		if(c=='.' ||c=='?'||c==','||c=='!'||c==':'||c==';'||c=='"'||c=='-'||c=='('||c==')')
			count++;
	}
        if(flag == 0)
	std::cout<<"Number of punctuation marks: "<<count << "\n\n";
	inFile.close();
        return count;
}

/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim 
 *      Student ID: 1820151002
 * @function void Passage::findWord(std::string word)
 *      
 * finds a word in the passage and prints the position and sentence it was found 
 *  
 *         
 */
void Passage::findWord(std::string word){
    bool flag = false;
    for(int i = 0; i < this->passageSentences.size(); i++ ){
          
         std::string str = passageSentences[i];
         std::string str2 (word);
         int found = str.find(str2);
         if (found!=std::string::npos){
             flag = true;
            std::cout << "\""<< word <<"\" found at position: " << found << " of sentence: " << i + 1 << "\n" ;
            std::cout << str << "\n\n";
         }
    }
    if(flag == false){
         std::cout << "\""<< word <<"\" not found in Passage\n";
    }
  
}
/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim
 * @function
 *     Find Case Insensitive Sub String in a given substring 
 * @return
 *  
 * 
 */
int Passage::findCaseInsensitive(std::string data, std::string toSearch, int pos )
{

	// Convert complete given String to lower case
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	// Convert complete given Sub String to lower case
	std::transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);
	// Find sub string in given string
	return data.find(toSearch, pos);
}
/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim 
 *      Student ID: 1820151002
 * @function
 *      finds a word in a passage, different case words are regarded as same
 * 
 * POSTCONDITION:
 *      prints the position the word was found or notifies by printing if it wasn't found
 *         
 */
void Passage::findWordInsenstive(std::string word){
    bool flag = false;
    for(int i = 0; i < this->passageSentences.size(); i++ ){
          
         std::string str = passageSentences[i];
         std::string str2 (word);
         int found = this->findCaseInsensitive(str,word);
         if (found!=std::string::npos){
            std::cout << "\""<< word <<"\" found at position: " << found << " of sentence: " << i + 1 << "\n" ;
            std::cout << str << "\n\n";
            flag = true;
         }
    }
    if(flag == false){
        std::cout << "\n" << word << " was not found in the passage" << "\n\n";
    }
}

/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim 
 *      Student ID: 1820151002
 * @function
 *      replaces a "word" with a "replacement" in the passage 
 *  
 *         
 */
void Passage::replaceWord(std::string word, std::string replacement ){
    int wordSize = word.size();
             
    std::string alterPassageText = this->passageText;
    
    std::string str2 (word);
    int found = alterPassageText.find(str2);
    while (found!=std::string::npos){
        alterPassageText.replace(found,wordSize, replacement);
        found = alterPassageText.find(str2);
    }
         
    std::cout <<"------------ \"" << word << "\" replaced with \"" << replacement << "\"----------\n\n";
    std::cout <<  alterPassageText << "\n\n";
    std::fstream inFile;
    inFile.open(fileName,std::ios::out);
    inFile<<alterPassageText;

}  
/**
 * 
 * @Author
 *      Christopher Jason S 
 *      Student ID: 1820151020
 * @function
 *      joins the content of the passage with the content of another file
 * PARAMETER
 *  fileName1: the file to be joined with passage
 * @return
 *      return true if files were joined successfully else returns false
 *         
 */
bool Passage::joinFile(const std::string fileName1){
    std::ifstream file;
    //std::string fileName = this->fileName;
    file.open(this->fileName);
    std::ifstream file1;
    file1.open(fileName1);
    if(file.is_open() && file1.is_open()){
        std::string newFileName = "joined.txt";
        std::ofstream combinedFile(newFileName);
        combinedFile << file.rdbuf()<<"\n"<< file1.rdbuf();
        return true;
    }
    std::cout<<"Error: The two files could not be joined\n\n";
    return false; 
}

/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim & Jason
 *      Student ID: 1820151002 & 1820151020
 * @function
 *      changes the passage to sentence case, it effects the changes on the file
 *      and prints the new format 
 * @return
 *  
 *         
 */
void Passage::capitalizeFirstLetter(){
   //Identifies if the sentence has been capitalized. Set to false by default.
  bool thisSentenceCapped = false;
  std::string strToConvert = this->passageText;
  lowerCase(strToConvert);  //Lowercase the string before processing.

  for (unsigned int i=0; i<strToConvert.length();i++)
  {
    //At a punctuation mark, the next sentence has not been manipulated
    //yet to have its first letter capitalized, so thisSentenceCapped is false.
    if (isSentencePunc(strToConvert[i]))
      thisSentenceCapped = false;

    if ((thisSentenceCapped==false) && (std::isalpha(strToConvert[i])))
    {
      strToConvert[i]=std::toupper(strToConvert[i]);
      thisSentenceCapped = true;
    }

  }
  std::cout << "------------------------Sentence Case------------------------\n";
  std::cout << strToConvert << "\n\n";
  std::fstream inFile;
  inFile.open(fileName,std::ios::out);
  inFile<<strToConvert;
  
 
}
/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim 
 *      Student ID: 1820151002
 * @function lowerCase
 *     Description: makes all the characters of a string lowercase
 * PARAMETERS
 *      strToConvert: the string being manipulated
 * Precondition:
 *      strToConvert: undefined
 * HEADERS
 *      #include <string> 
 * @return
 *  Postcondition:
 *      Returns the string all lowercase
 *         
 */

void Passage::lowerCase(std::string& strToConvert)
{
   for(unsigned int i=0;i<strToConvert.length();i++)
   {
      strToConvert[i] = std::tolower(strToConvert[i]);
   }
}

/**
 * 
 * @Author
 *      Aminu Ibrahim Hashim 
 *      Student ID: 1820151002
 * @function  isSentencePunc
 *      Description: Checks to see if a character is a punctuation mark used to denote
 *                   the end of a sentence. (! . ?)
 * PARAMETERS
 *      character: The character being tested
 * Precondition:
 *      character: defined
 * @return
 *  Postcondition:
 *      Returns boolean value of true if the character is ! . or ?
 *         
 */

bool Passage::isSentencePunc(char character)
{
  switch(character)
  {
    case '!':
    case '.':
    case '?':
      return true;
    default:
      return false;
  }
}
