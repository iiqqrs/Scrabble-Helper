#include <iostream>
#include <vector>
using namespace std;

#ifndef _TRIE_H_
#define _TRIE_H_

class Node {
public:
    Node();
    ~Node();
    char content();
    void setChar(char c);
    bool is_word();
    void make_complete();
    Node* findChild(char c);
    void appendChild(Node* child);
    vector<Node*> children();
    char letter;
    bool isComplete() {
        if (complete_word) {
            return true;
        }
        else {
            return false;
        }
    }
private:
    
    bool complete_word;
    vector<Node*> child;
};

class Trie {
public:
    Trie();
    ~Trie();
    void newWord(string s);
    bool findWord(string s);
    bool isComplete(Node* node);
    Node* getRoot() {
        return root;
    }
    //void getRackWords(const string& prefix, map<char, int>& rack, vector<string>& results);
private:
    Node* root;
};

#endif 