#ifndef __GRAMMAR_H_
#define __GRAMMAR_H_
#include <bits/stdc++.h>

using namespace std;

class Grammar
{
protected:
  set<char> nonterminals;
  set<char> terminals;
  char start;
  set<pair<string, string>> rules;
  int minimum(queue<pair<string, int>> &queue);
  int minimum(set<string> words);
  int countOfTerminals(string word);

public:
  Grammar(string stringGrammar);
  string hello() const;
  void toReducedNormalForm();
  void toEpsilonFreeForm();
  string isEquivalent(Grammar *grammar);
  string grammarToString();
};
#endif