#ifndef __GRAMMAR_H_
#define __GRAMMAR_H_
#include <string>
#include <set>
#include <utility>

using namespace std;

class Grammar
{
private:
  set<char> nonterminals;
  set<char> terminals;
  char start;
  set<pair<string, string>> rules;

public:
  Grammar(/*set<char> nonterminals, set<char> terminals, char start, set<pair<string, string>> rules*/);
  string hello() const;
};
#endif