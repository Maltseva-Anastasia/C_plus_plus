#include "text.h"

Text::Text() : length(2) {} 

void Text::setFileName(char* FileName)
{
  fileName.replace(0, fileName.size(), FileName); 
}

bool Text::setStringLenght(int& Length)
{
  if (Length < 2) 
    return false;
  length = Length;  
  return true;
}

list<string> Text::parse(istream& str)
{
  list<string> sentence; 
  istream_iterator<string> parser(str); 
  istream_iterator<string> end;
  while (parser!= end)
  {
    sentence.push_back(*parser); 
    parser++;
  }
  return sentence;
}

int Text::getStrLen(list<string>& str)
{
  int length = 0;
  for (auto& l : str)
    length += l.size();
  return length;
}

void Text::split(int i)
{
  string temp = text[i].begin()->substr(length - 1, text[i].begin()->size());
  text[i].begin()->erase(length - 1, text[i].begin()->size()); 
  strLen[i] = length; 
  *text[i].begin() += '-';  
  list<string>::iterator j = --text[i].end(); 
  while (text[i].size() != 1)
  {
    text[i + 1].push_front(*j); 
    strLen[i + 1] += text[i + 1].begin()->size(); 
    j--;
    text[i].pop_back(); 
  }
  text[i + 1].push_front(temp); 
  strLen[i + 1] += temp.size(); 
}

void Text::move(int i)
{
  unsigned int len = strLen[i] + text[i].size() - 1;  
  list<string>::iterator j = text[i].end();
  while (length < len)  
  {
    j--;
    len -= (j->size() + 1);
  }
  list<string>::iterator pos = text[i].end(), temp;
  pos--;  
  while (true)
  {
    text[i + 1].push_front(*pos); 
    strLen[i + 1] += pos->size(); 
    temp = pos;
    if (pos == j) 
    {
      strLen[i] -= pos->size();
      text[i].erase(pos);
      break;
    }
    pos--;
    strLen[i] -= temp->size();  
    text[i].erase(temp);
  }
}

void Text::layout(void)
{
  for (unsigned int i = 0; i < text.size(); i++)  
  {
    if ((strLen[i] + text[i].size() - 1) > length)  
    {
      if (i + 1 == text.size()) 
      {
        list<string> temp;
        text.push_back(temp); 
        strLen.push_back(0);
      }
      if (text[i].begin()->size() > length) 
        split(i);
      else
        move(i);  
    }
  }
}

bool Text::readFromFile(void)
{
  ifstream fis(fileName);
  if (!fis.is_open()) 
    return false;
  string temp;  
  while (true)
  {
    std::getline(fis, temp); 
    istrstream str(temp.data());  
    text.push_back(parse(str)); 
    strLen.push_back(getStrLen(*(--text.end()))); 
    if (fis.fail() || fis.eof())  
    {
      fis.clear();
      break;
    }
  }
  fis.close();  
  layout(); 
  return true;
}

void Text::print(void)
{
  for (unsigned int i = 0; i < text.size(); i++) 
  {
    int n = (length - (strLen[i] + text[i].size() - 1)) / 2; 
    for (int i = 0; i < n; i++) 
      cout << ' ';
    for (auto& word : text[i])  
      cout << word << " ";
    cout << endl; 
  }
}