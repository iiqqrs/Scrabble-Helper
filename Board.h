#include <iostream>
#include <vector>
#include "Trie.h"
using namespace std;

#ifndef _BOARD_H_
#define _BOARD_H_

struct Tile{
    bool used;
    bool is_anchor;
    char letter; //Letter on tile
    int word_multip;
    int letter_multip;
    vector<char> crossVertical;
    vector<char> crossHorizontal;
    
    Tile(){
        for(int i = 65; i < 91 ; i++){
            crossVertical.push_back(char(tolower(i)));
            crossHorizontal.push_back(char(tolower(i)));
        }
        
        used = false;
        letter = ' ';
        word_multip = 1;
        letter_multip = 1;
        is_anchor = false;
    }
};

class Board{
    public:
        Trie dictionary;
        vector<string> rack_words;
        vector<Tile> rack;
        Tile theBoard[15][15];
        void updateTiles();
        void update(int row, int column, string direction);
        Board();
};

#endif