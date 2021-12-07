//============================================================================
// Name        : lesson_05_CPP_DM.cpp
// Author      : andry antonenko
// IDE         : Qt Creator 4.14.2 based on Qt 5.15.2
// Description : lesson 05 of the C++: difficult moments course
//============================================================================
#include <QCoreApplication>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <tuple>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>
//----------------------------------------------------------------------------
/*
1. Создать шаблонную функцию,
которая принимает итераторы на начало и конец последовательности слов,
и выводящую в консоль список уникальных слов
(если слово повторяется больше 1 раза, то вывести его надо один раз).
Продемонстрировать работу функции, передав итераторы различных типов.
//*/

template<typename RandomIt>
void uniqueWords(RandomIt first,
                 RandomIt last)
{
  std::set<std::string> setWords;
  for(auto it{ first }; it != last; ++it)
    setWords.insert(*it);

  copy(setWords.cbegin(),setWords.cend(),
       std::ostream_iterator<std::string>(std::cout, " "));
}

const std::string SPLIT_SIMBOLS = " .,?!(){}:;'";

std::vector<std::string> split(const std::string &s, const std::string &delim)
{
  std::vector<std::string> vec;

  if(s.length() == 0)
    return vec;

  if(delim.length() == 0)
  {
    vec.push_back(s);
    return vec;
  }

  size_t pos = 0;
  while (pos < s.length() - 1)
  {
    size_t posDelim = s.length();
    for(const char ch: delim)
    {
      size_t p = s.find(ch,pos);
      if(p < posDelim)
        posDelim = p;
    }
    if(posDelim == pos)
    {
      ++pos;
      continue;
    }
    std::string substr = s.substr(pos,posDelim - pos);
    vec.push_back(substr);
    pos = posDelim + 1;
  }
  return vec;
}

template<typename Container>
void getWords(std::ifstream &inFile, Container& cont)
{
  if (inFile.is_open())
  {
    std::string word;
    std::string txt;
    while (!inFile.eof())
    {
      inFile >> word;
      std::transform(word.begin(), word.end(), word.begin(),
                     [](unsigned char c){ return std::tolower(c); } // correct
                    );
      auto vec = split(word, SPLIT_SIMBOLS);

      std::copy(vec.begin(), vec.end(), std::back_inserter(cont));
    }
    inFile.close();
  }
  else
  {
    std::cout << "File did not open!" << std::endl;
  }

}

void task_1()
{
  std::cout << "Task 1\n" << std::endl;

  std::ifstream fin_list("TestFile.txt");

  std::cout << "List:" << std::endl;
  std::list<std::string> listStrings;
  getWords(fin_list,listStrings);
  fin_list.close();
  uniqueWords(listStrings.begin(), listStrings.end());

  std::cout << "\n\nVector:" << std::endl;
  std::ifstream fin_vec("TestFile.txt");
  std::vector<std::string> vectorStrings;
  getWords(fin_vec,vectorStrings);
  fin_vec.close();
  uniqueWords(listStrings.begin(), listStrings.end());

  std::cout << std::endl;
}

//----------------------------------------------------------------------------
/*
2. Используя ассоциативный контейнер, напишите программу,
которая будет считывать данные введенные пользователем
из стандартного потока ввода и разбивать их на предложения.
Далее программа должна вывести пользователю все предложения,
отсортировав их по длине.
//*/

const std::string SPLIT_SIMBOLS_OF_END = ".?!";

std::vector<std::string> split_with_delim(const std::string &s, const std::string &delim)
{
  std::vector<std::string> vec;

  if(s.length() == 0)
    return vec;

  if(delim.length() == 0)
  {
    vec.push_back(s);
    return vec;
  }

  size_t pos = 0;
  while (pos < s.length() - 1)
  {
    size_t posDelim = s.length();
    for(const char ch: delim)
    {
      size_t p = s.find(ch,pos);
      if(p < posDelim)
        posDelim = p;
    }
    if(posDelim == pos)
    {
      ++pos;
      continue;
    }

    while(s[pos] == ' ')
    {
      ++pos;
    }

    std::string substr = s.substr(pos,posDelim - pos + 1);
    vec.push_back(substr);
    pos = posDelim + 1;
  }
  return vec;
}

std::multimap<int,std::string> getSentences()
{
  std::multimap<int,std::string> m;

  std::string sentences;

  std::getline(std::cin,sentences,'\n');

  auto vec = split_with_delim(sentences, SPLIT_SIMBOLS_OF_END);

  std::for_each(vec.begin(),vec.end(),[&m](std::string& sentence){
    m.insert({sentence.length(),std::move(sentence)});
  });

  return m;
}

void task_2()
{
  std::cout << "\nTask 2\n" << std::endl;

  std::cout << "Enter user's data:" << std::endl;
  auto m = getSentences();
  std::cout << "Output sentences:" << std::endl;
  for(auto& a: m)
  {
    std::cout << a.second << std::endl;
  };

  std::cout << std::endl;
}

//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  //--------------------------------------------------------------------------
  // Task 1
  //*
  task_1();
  //*/
  //--------------------------------------------------------------------------
  // Task 2
  //*
  task_2();
  //*/
  //--------------------------------------------------------------------------
  return a.exec();
}
