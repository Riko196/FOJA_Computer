#include "Grammar.h"
#include "../relations/PrecedentialRelation.h"

set<char> Grammar::getNonterminals() const
{
    return this->nonterminals;
}

set<char> Grammar::getTerminals() const
{
    return this->terminals;
}

char Grammar::getStart() const
{
    return this->start;
}

set<pair<string, string>> Grammar::getRules() const
{
    return this->rules;
}

Grammar::Grammar(string stringGrammar)
{
    stringstream stringGrammarStream(stringGrammar);
    string segment;
    vector<string> grammar;

    while (getline(stringGrammarStream, segment, '|'))
    {
        grammar.push_back(segment);
    }

    stringstream nonterminalsStream(grammar[0]);
    while (getline(nonterminalsStream, segment, ','))
    {
        this->nonterminals.insert(segment[0]);
    }

    stringstream terminalsStream(grammar[1]);
    while (getline(terminalsStream, segment, ','))
    {
        this->terminals.insert(segment[0]);
    }

    this->start = grammar[2][0];

    stringstream rulesStream(grammar[3]);
    pair<string, string> rule;
    rule.first = epsilon;
    rule.second = epsilon;
    while (getline(rulesStream, segment, ','))
    {
        if (rule.first == epsilon)
        {
            rule.first = segment;
        }
        else
        {
            rule.second = segment;
            if (rule.second == substitutedEpsilon)
                rule.second = epsilon;
            this->rules.insert(rule);
            rule.first = epsilon;
            rule.second = epsilon;
        }
    }
}

void Grammar::toReducedNormalForm()
{
    for (auto rule : this->rules)
        if (rule.first.compare(rule.second) == 0)
            this->rules.erase(rule);

    set<char> terminatedNonterminals;

    while (true)
    {
        bool end = true;
        for (auto rule : this->rules)
        {
            bool terminatedRule = true;
            for (unsigned int i = 0; i < rule.second.length(); i++)
            {
                if ((terminatedNonterminals.count(rule.second[i]) == 0) && (this->terminals.count(rule.second[i]) == 0))
                {
                    terminatedRule = false;
                    break;
                }
            }
            if ((terminatedRule) && (terminatedNonterminals.count(rule.first[0]) == 0))
            {
                terminatedNonterminals.insert(rule.first[0]);
                end = false;
            }
        }
        if (end)
            break;
    }
    for (auto rule : this->rules)
    {
        if (terminatedNonterminals.count(rule.first[0]) == 0)
        {
            this->rules.erase(rule);
            continue;
        }
        for (unsigned int i = 0; i < rule.second.length(); i++)
            if ((terminatedNonterminals.count(rule.second[i]) == 0) && (this->terminals.count(rule.second[i]) == 0))
            {
                this->rules.erase(rule);
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
        for (auto rule : this->rules)
        {
            if (rule.first[0] == word)
            {
                for (unsigned int i = 0; i < rule.second.length(); i++)
                {
                    if ((achievableNonterminals.count(rule.second[i]) == 0) && (this->terminals.count(rule.second[i]) == 0))
                    {
                        achievableNonterminals.insert(rule.second[i]);
                        q.push(rule.second[i]);
                    }
                }
            }
        }
    }

    for (auto rule : this->rules)
    {
        if (achievableNonterminals.count(rule.first[0]) == 0)
        {
            this->rules.erase(rule);
            continue;
        }

        for (unsigned int i = 0; i < rule.second.length(); i++)
            if ((achievableNonterminals.count(rule.second[i]) == 0) && (this->terminals.count(rule.second[i]) == 0))
            {
                this->rules.erase(rule);
                break;
            }
    }

    achievableNonterminals.clear();
}

void Grammar::toEpsilonFreeForm()
{
    set<char> removableNonterminals;
    for (auto rule : this->rules)
        if (rule.second == epsilon)
            removableNonterminals.insert(rule.first[0]);

    //finding out removable rules
    while (true)
    {
        bool end = true;
        for (auto rule : this->rules)
        {
            bool removableRule = true;
            for (unsigned int i = 0; i < rule.second.length(); i++)
            {
                if (removableNonterminals.count(rule.second[i]) == 0)
                {
                    removableRule = false;
                    break;
                }
            }
            if ((removableRule) && (removableNonterminals.count(rule.first[0]) == 0))
            {
                removableNonterminals.insert(rule.first[0]);
                end = false;
            }
        }
        if (end)
            break;
    }

    //computing new rules
    set<pair<string, string>> newRules;

    for (auto rule : this->rules)
    {
        string combination = epsilon;
        for (unsigned int i = 0; i < rule.second.length(); i++)
            if (removableNonterminals.count(rule.second[i]) != 0)
                combination += "0";

        if (combination == epsilon)
            continue;

        while (count(combination.begin(), combination.end(), '1') != combination.length())
        {
            string newRule = epsilon;
            int removableNonterminal = 0;
            for (unsigned int i = 0; i < rule.second.length(); i++)
            {
                if (removableNonterminals.count(rule.second[i]) != 0)
                {
                    if (combination[removableNonterminal] == '1')
                        newRule += rule.second[i];
                    removableNonterminal++;
                }
                else
                    newRule += rule.second[i];
            }

            for (int i = combination.length() - 1; i >= 0; i--)
            {
                combination[i] = combination[i] == '0' ? '1' : '0';
                if (combination[i] == '1')
                    break;
            }

            pair<string, string> newRulePair;
            newRulePair.first = rule.first;
            newRulePair.second = newRule;
            newRules.insert(newRulePair);
        }
    }

    //inserting new rules
    for (auto newRule : newRules)
        this->rules.insert(newRule);

    //erasing epsilon rules
    for (auto rule : this->rules)
        if (rule.second == epsilon)
            this->rules.erase(rule);
}

int Grammar::countOfTerminals(string word)
{
    int count = 0;
    for (unsigned int i = 0; i < word.length(); i++)
        if ((((int)word[i]) >= 97) && (((int)word[i]) <= 122))
            count++;
    return count;
}

int Grammar::minimum(queue<pair<string, int>> &queue)
{
    int minimum = 0;
    int size = queue.size();
    for (unsigned int i = 0; i < size; i++)
    {
        pair<string, int> rule = queue.front();
        queue.pop();
        if (i == 0)
            minimum = rule.second;
        else if (minimum > rule.second)
            minimum = rule.second;
        queue.push(rule);
    }
    return minimum;
}

int Grammar::minimum(set<string> words)
{
    int minimum = 0, i = 0;
    for (auto word : words)
    {
        if (i == 0)
        {
            minimum = word.length();
            i++;
        }
        else if (minimum > word.length())
            minimum = word.length();
    }
    return minimum;
}

string Grammar::isEquivalent(Grammar *grammar)
{
    int maxMemory = 0;
    int reachedSize = 0;
    queue<pair<string, int>> thisQueue, grammarQueue;
    set<string> thisWords, grammarWords;
    pair<string, int> start;

    start.first = string(1, this->start);
    start.second = 0;
    thisQueue.push(start);

    start.first = string(1, grammar->start);
    start.second = 0;
    grammarQueue.push(start);

    maxMemory += 2;

    this->toReducedNormalForm();
    grammar->toReducedNormalForm();

    for (unsigned int i = 0; i < 10000; i++)
    {
        if (i % 1000 == 0)
        {
            int thisMinimum = thisQueue.size() == 0 ? this->minimum(thisWords) : this->minimum(thisQueue);
            int grammarMinimum = grammarQueue.size() == 0 ? this->minimum(grammarWords) : this->minimum(grammarQueue);

            reachedSize = max(reachedSize, min(thisMinimum, grammarMinimum));
            for (auto word : thisWords)
            {
                if ((word.length() < min(thisMinimum, grammarMinimum)) && (grammarWords.count(word) == 0))
                    return word == epsilon ? "Epsilon|0" : word + "|0";
            }

            for (auto word : grammarWords)
            {
                if ((word.length() < min(thisMinimum, grammarMinimum)) && (thisWords.count(word) == 0))
                    return word == epsilon ? "Epsilon|0" : word + "|0";
            }
        }

        pair<string, int> thisWord;
        if (!thisQueue.empty())
        {
            thisWord = thisQueue.front();
            thisQueue.pop();
        }

        maxMemory -= thisWord.first.length();

        pair<string, int> grammarWord;
        if (!grammarQueue.empty())
        {
            grammarWord = grammarQueue.front();
            grammarQueue.pop();
        }

        maxMemory -= grammarWord.first.length();

        for (unsigned int j = 0; j < thisWord.first.length(); j++)
        {
            if ((int)thisWord.first[j] > 90)
                continue;
            for (auto rule : this->rules)
            {
                if (rule.first == string(1, thisWord.first[j]))
                {
                    pair<string, int> newPair = thisWord;
                    newPair.first.erase(j, 1);
                    newPair.first.insert(j, rule.second);
                    newPair.second += this->countOfTerminals(rule.second);

                    if (newPair.second == newPair.first.length())
                        thisWords.insert(newPair.first);
                    else
                        thisQueue.push(newPair);
                    if (maxMemory + newPair.first.length() > 50000000)
                        return to_string(reachedSize) + "|1";
                    else
                        maxMemory += newPair.first.length();
                }
            }
        }

        for (unsigned int j = 0; j < grammarWord.first.length(); j++)
        {
            if ((int)grammarWord.first[j] > 90)
                continue;
            for (auto rule : grammar->rules)
            {
                if (rule.first == string(1, grammarWord.first[j]))
                {
                    pair<string, int> newPair = grammarWord;
                    newPair.first.erase(j, 1);
                    newPair.first.insert(j, rule.second);
                    newPair.second += grammar->countOfTerminals(rule.second);

                    if (newPair.second == newPair.first.length())
                        grammarWords.insert(newPair.first);
                    else
                        grammarQueue.push(newPair);
                    if (maxMemory + newPair.first.length() > 50000000)
                        return to_string(reachedSize) + "|1";
                    else
                        maxMemory += newPair.first.length();
                }
            }
        }
    }

    return to_string(reachedSize) + "|1";
}

string Grammar::grammarToString()
{
    string stringGrammar = epsilon;
    for (auto nonterminal : this->nonterminals)
    {
        stringGrammar += string(1, nonterminal) + ",";
    }
    stringGrammar.pop_back();
    stringGrammar += "|";
    for (auto terminal : this->terminals)
    {
        stringGrammar += string(1, terminal) + ",";
    }
    stringGrammar.pop_back();
    stringGrammar += "|" + string(1, this->start);
    stringGrammar += "|";
    for (auto rule : this->rules)
    {
        stringGrammar += rule.first + ",";
        if (rule.second == substitutedEpsilon)
            stringGrammar += ",";
        else
            stringGrammar += rule.second + ",";
    }
    stringGrammar.pop_back();
    return stringGrammar;
}

bool Grammar::isPrecedential()
{
    // there cant be the rule with epsilon
    for (auto rule : this->rules)
        if (rule.second == epsilon)
            return false;

    // there cant be more than one rules with the same right side
    map<string, int> amountOfRules;
    for (auto rule : this->rules)
    {
        amountOfRules[rule.second]++;
        if (amountOfRules[rule.second] > 1)
            return false;
    }

    // there can't be more than one relations betwen 2 symbols from N merged with P
    PrecedentialRelation *precedentialRelation = new PrecedentialRelation(this);
    bool result = precedentialRelation->atMostOneRelation();
    delete precedentialRelation;
    return result;
}

string Grammar::getYourPrecedentialRelationString()
{
    PrecedentialRelation *precedentialRelation = new PrecedentialRelation(this);
    string precedentialRelationString = precedentialRelation->getPrecedentialRelationString();
    delete precedentialRelation;
    return precedentialRelationString;
}

string Grammar::hello() const
{
    return "hello world!";
}