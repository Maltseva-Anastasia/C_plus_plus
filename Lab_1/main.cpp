#include "text.h"

int main(int argc, char* argv[])  
{
  if (argc != 3)  
  {
    cerr << "Wrong amount of input arguments.\n";
    return 1;
  }
  int len = atoi(argv[2]);  
  if (!len && strcmp(argv[2], "0")) 
  {
    cerr << "Input file's name first and the string's length second;\n";
    return 2;
  }
  Text text;
  text.setFileName(argv[1]);  
  if (!text.setStringLenght(len)) 
  {
    cerr << "I'm afraid your string is too short.\n";
    return 3;
  }
  if(!text.readFromFile())  
  {
    cerr << "Couldn't open the file.\n";
    return 4;
  }
  text.print(); 
  return 0;
}