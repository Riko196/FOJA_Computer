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
  bool isTerminalWord(string word);
  int minimum(queue<string> &queue);

public:
  Grammar(string stringGrammar);
  string hello() const;
  void toReducedNormalForm();
  void toEpsilonFreeForm();
  bool isEquivalent(Grammar *grammar);
  string grammarToString();
};
#endif