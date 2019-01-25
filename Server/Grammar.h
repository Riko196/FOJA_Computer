#ifndef __GRAMMAR_H_
#define __GRAMMAR_H_
#include <string>
#include <set>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

class Grammar
{
protected:
  set<char> nonterminals;
  set<char> terminals;
  char start;
  set<pair<string, string>> rules;
  bool isTerminalWord(string word);

public:
  Grammar(set<char> nonterminals, set<char> terminals, char start, set<pair<string, string>> rules);
  string hello() const;
  void toReducedNormalForm();
  void toEpsilonFreeForm();
  bool isEquivalent(Grammar *grammar);
  int minimum(queue<string> &queue);
};

/*bool operator<(const pair<string, string> &pair1, const pair<string, string> &pair2)
{
  if (pair1.first != pair2.first)
    return pair1.first < pair2.first;
  else
    return pair1.second > pair2.second;
}*/
#endif