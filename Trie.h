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
        Node* parent; //For testing.
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
        //bool isComplete(Node* node);
        Node* findPartial(string s);
        Node* getRoot() {
            return root;
        }
    private:
        Node* root;
};

#endif 