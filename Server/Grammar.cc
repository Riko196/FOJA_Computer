#include "Grammar.h"

Grammar::Grammar(set<char> nonterminals, set<char> terminals, char start, set<pair<string, string>> rules)
{
    this->nonterminals = nonterminals;
    this->terminals = terminals;
    this->start = start;
    this->rules = rules;
}

void Grammar::toReducedNormalForm()
{
    for (auto para : this->rules)
        if (para.first.compare(para.second) == 0)
            this->rules.erase(para);

    set<char> terminatedNonterminals;

    while (true)
    {
        bool end = true;
        for (auto para : this->rules)
        {
            bool terminatedRule = true;
            for (unsigned int i = 0; i < para.second.length(); i++)
            {
                if ((terminatedNonterminals.count(para.second[i]) == 0) && (this->terminals.count(para.second[i]) == 0))
                {
                    terminatedRule = false;
                    break;
                }
            }
            if ((terminatedRule) && (terminatedNonterminals.count(para.first[0]) == 0))
            {
                terminatedNonterminals.insert(para.first[0]);
                end = false;
            }
        }
        if (end)
            break;
    }
    for (auto para : this->rules)
    {
        if (terminatedNonterminals.count(para.first[0]) == 0)
        {
            this->rules.erase(para);
            continue;
        }
        for (unsigned int i = 0; i < para.second.length(); i++)
            if ((terminatedNonterminals.count(para.second[i]) == 0) && (this->terminals.count(para.second[i]) == 0))
            {
                this->rules.erase(para);
                break;
            }
    }
    terminatedNonterminals.clear();

    set<char> achievableNonterminals;
    achievableNonterminals.insert(this->start);
    queue<char> q;
    q.push(this->start);
    while (!q.empty())
    {
        char word = q.front();
        q.pop();
        for (auto para : this->rules)
        {
            if (para.first[0] == word)
            {
                for (unsigned int i = 0; i < para.second.length(); i++)
                {
                    if ((achievableNonterminals.count(para.second[i]) == 0) && (this->terminals.count(para.second[i]) == 0))
                    {
                        achievableNonterminals.insert(para.second[i]);
                        q.push(para.second[i]);
                    }
                }
            }
        }
    }

    for (auto para : this->rules)
    {
        if (achievableNonterminals.count(para.first[0]) == 0)
        {
            this->rules.erase(para);
            continue;
        }

        for (unsigned int i = 0; i < para.second.length(); i++)
            if ((achievableNonterminals.count(para.second[i]) == 0) && (this->terminals.count(para.second[i]) == 0))
            {
                this->rules.erase(para);
                break;
            }
    }

    achievableNonterminals.clear();
}

void Grammar::toEpsilonFreeForm()
{
    set<char> removableNonterminals;
    for (auto para : this->rules)
        if (para.second == "")
            removableNonterminals.insert(para.first[0]);

    //finding out removable rules
    while (true)
    {
        bool end = true;
        for (auto para : this->rules)
        {
            bool removableRule = true;
            for (unsigned int i = 0; i < para.second.length(); i++)
            {
                if (removableNonterminals.count(para.second[i]) == 0)
                {
                    removableRule = false;
                    break;
                }
            }
            if ((removableRule) && (removableNonterminals.count(para.first[0]) == 0))
            {
                removableNonterminals.insert(para.first[0]);
                end = false;
            }
        }
        if (end)
            break;
    }

    //computing new rules
    set<pair<string, string>> newRules;

    for (auto para : this->rules)
    {
        string combination = "";
        for (unsigned int i = 0; i < para.second.length(); i++)
            if (removableNonterminals.count(para.second[i]) != 0)
                combination += "0";

        if (combination == "")
            continue;

        while (count(combination.begin(), combination.end(), '1') != combination.length())
        {
            string newRule = "";
            int removableNonterminal = 0;
            for (unsigned int i = 0; i < para.second.length(); i++)
            {
                if (removableNonterminals.count(para.second[i]) != 0)
                {
                    if (combination[removableNonterminal] == '1')
                        newRule += para.second[i];
                    removableNonterminal++;
                }
                else
                    newRule += para.second[i];
            }

            for (int i = combination.length() - 1; i >= 0; i--)
            {
                combination[i] = combination[i] == '0' ? '1' : '0';
                if (combination[i] == '1')
                    break;
            }

            pair<string, string> newRulePair;
            newRulePair.first = para.first;
            newRulePair.second = newRule;
            newRules.insert(newRulePair);
        }
    }

    //inserting new rules
    for (auto newRule : newRules)
        this->rules.insert(newRule);

    //erasing epsilon rules
    for (auto para : this->rules)
        if (para.second == "")
            this->rules.erase(para);
}

bool Grammar::isTerminalWord(string word)
{
    for (unsigned int i = 0; i < word.length(); i++)
        if ((((int)word[i]) < 97) || (((int)word[i]) > 122))
            return false;
    return true;
}

int Grammar::minimum(queue<string> &queue)
{
    int minimum = 0;
    for (unsigned int i = 0; i < queue.size(); i++)
    {
        string s = queue.front();
        queue.pop();
        if (minimum == 0 || minimum > s.length())
            minimum = s.length();
        queue.push(s);
    }
    return minimum - 1;
}

bool Grammar::isEquivalent(Grammar *grammar)
{
    int maxMemory = 0;
    queue<string> thisQueue, grammarQueue;
    set<string> thisWords, grammarWords;

    thisQueue.push(string(1, this->start));
    grammarQueue.push(string(1, grammar->start));
    maxMemory += 2;

    this->toReducedNormalForm();
    grammar->toReducedNormalForm();

    for (unsigned int i = 0; i < 10000; i++)
    {
        if (i % 1000 == 0)
        {
            int thisMinimum = this->minimum(thisQueue);
            int grammarMinimum = grammar->minimum(grammarQueue);

            for (auto word : thisWords)
            {
                if ((word.length() <= min(thisMinimum, grammarMinimum)) && (grammarWords.count(word) == 0))
                    return false;
            }

            for (auto word : grammarWords)
            {
                if ((word.length() <= min(thisMinimum, grammarMinimum)) && (thisWords.count(word) == 0))
                    return false;
            }
        }

        string thisWord = thisQueue.front();
        thisQueue.pop();
        maxMemory -= thisWord.length();
        string grammarWord = grammarQueue.front();
        grammarQueue.pop();
        maxMemory -= grammarWord.length();

        for (unsigned int j = 0; j < thisWord.length(); j++)
        {
            if ((int)thisWord[j] > 90)
                continue;
            for (auto para : this->rules)
            {
                if (para.first == string(1, thisWord[j]))
                {
                    string newString = thisWord;
                    newString.erase(j, 1);
                    newString.insert(j, para.second);
                    if (this->isTerminalWord(newString))
                        thisWords.insert(newString);
                    else
                        thisQueue.push(newString);
                    if (maxMemory + newString.length() > 50000000)
                        return true;
                    else
                        maxMemory += newString.length();
                }
            }
        }

        for (unsigned int j = 0; j < grammarWord.length(); j++)
        {
            if ((int)grammarWord[j] > 90)
                continue;
            for (auto para : grammar->rules)
            {
                if (para.first == string(1, grammarWord[j]))
                {
                    string newString = grammarWord;
                    newString.erase(j, 1);
                    newString.insert(j, para.second);
                    if (this->isTerminalWord(newString))
                        grammarWords.insert(newString);
                    else
                        grammarQueue.push(newString);
                    if (maxMemory + newString.length() > 50000000)
                        return true;
                    else
                        maxMemory += newString.length();
                }
            }
        }
    }

    return true;
}

string Grammar::hello() const
{
    return "hello world!";
}