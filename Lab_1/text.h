#ifndef __TEXT_H
#define __TEXT_H

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <strstream>

using namespace std;

class Text
{
private:
  string fileName; 
  unsigned int length; 
  vector<list<string>> text; 
  vector<int> strLen;
  list<string> parse(istream& str);
  int getStrLen(list<string>& str); 
  void split(int i);  
  void move(int i); 
  void layout(void); 
public:
  Text(); 
  void setFileName(char* FileName); 
  bool setStringLenght(int& Length); 
  bool readFromFile(void);  
  void print(void);
};

#endif