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
            current = child;
        }else{
            Node* tmp = new Node();
            tmp->setChar(s[i]);
            current->appendChild(tmp);
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



/*void Trie::getRackWords(const string& prefix, map<char, int>& rack, vector<string>& results){
        if (complete_word){
            results.push_back(prefix);
        }
        Node* temp = root;
        while(temp != NULL){
            if(rack.)
        }
        
        for(map<char, Trie*>::iterator it = children.begin(); it != children.end(); it++){
            if (rack.find(it->first) != rack.end() && rack[it->first] > 0){
                    rack[it->first] -=1;
                    it->second->getRackWords(prefix + it->first, rack, results);
                    rack[it->first] +=1;
            }
        }
    }
    */