#include <iostream>
#include <vector>
#include "Trie.h"
using namespace std;

Node::Node(){
    letter = ' ';
    complete_word = false;
}

Node::~Node(){
}

char Node::content(){
    return letter;
}

void Node::setChar(char c){
    letter = c;
}

bool Node::is_word(){
    return complete_word;
}

void Node::make_complete(){
    complete_word = true;
}
    
void Node::appendChild(Node* c){
    child.push_back(c);    
}

vector<Node*> Node::children(){ 
    return child;
}

Node* Node::findChild(char c){
    for(int i = 0; i < child.size(); i++){
        Node* tmp = child.at(i);
        if(tmp->content() == c){
            return tmp;
        }
    }
    return NULL;
}


Trie::Trie(){
    root = new Node();
}

Trie::~Trie(){
}

void Trie::newWord(string s){
    Node* current = root;

    if(s.length() == 0){
        current->make_complete(); // an empty word
        return;
    }

    for(int i = 0; i < s.length(); i++){        
        Node* child = current->findChild(s[i]);
        if (child != NULL){
            current = child; //Becomes root no parent
        }else{
            Node* tmp = new Node();
            tmp->setChar(s[i]);
            current->appendChild(tmp);
            tmp->parent = current;
            current = tmp;
        }
        if (i == s.length() - 1){
            current->make_complete();
        }
    }
}

bool Trie::findWord(string s){
    Node* current = root;
    while(current != NULL){
        for(int i = 0; i < s.length(); i++){
            Node* tmp = current->findChild(s[i]);
            if(tmp == NULL){
                return false;
            }
            current = tmp;
        }
        if(current->is_word()){
            return true;
        }else{
            return false;
        }
    }
    return false;
}

Node* Trie::findPartial(string s){
    Node* current = root;
    for(int i = 0; i < s.length(); i++){
        if (current->findChild(s[i]) == NULL) {
            return NULL;
        }else{
            Node* tmp = current->findChild(s[i]);
            current = tmp;
        }
    }
    return current;
}