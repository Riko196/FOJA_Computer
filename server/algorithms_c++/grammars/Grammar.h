#ifndef __GRAMMAR_H_
#define __GRAMMAR_H_
#include <bits/stdc++.h>

using namespace std;

#define epsilon ""
#define substitutedEpsilon "*"

class PrecedentialRelation;

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
  set<char> getNonterminals() const;
  set<char> getTerminals() const;
  char getStart() const;
  set<pair<string, string>> getRules() const;
  Grammar(string stringGrammar);
  string hello() const;
  void toReducedNormalForm();
  void toEpsilonFreeForm();
  string isEquivalent(Grammar *grammar);
  string grammarToString();
  bool isPrecedential();
  string getYourPrecedentialRelationString();
};
#endif