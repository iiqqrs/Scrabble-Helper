#include <iostream>
#include <vector>
#include <queue>
#include "Trie.h"
using namespace std;

#ifndef _BOARD_H_
#define _BOARD_H_

struct Tile{
    bool used;
    bool anchor_horizontal;
    bool anchor_vertical;
    char letter; //Letter on tile
    int word_multip;
    int letter_multip;
    int kHorizontal; //(number of non anchors to the left)
    int kVertical;
    int xCoord;
    int yCoord;
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
        anchor_horizontal = false;
        anchor_vertical = false;
        kHorizontal = 0;
        kVertical = 0;
        xCoord = 0;
        yCoord = 0;
        
    }
};

struct Move{
  int score;
  string full_word;
  int x;
  int y;
  string direction;
};

struct LessThanByScore{
  bool operator()(const Move& l, const Move& r){
    return l.score < r.score;
  }
};

class Board{
    public:
        Trie dictionary;
        priority_queue<Move, vector<Move>, LessThanByScore> scored_moves;
        vector<string> rack_words;
        vector<char> raw_rack;
        vector<Tile> rack;
        Tile theBoard[15][15];
        void updateTiles();
        void update(int row, int column, string direction);
        void updateKvals();
        void placeWord();
        void leftPart(string partialWord, Node* root, int kHoriz, Tile tile);
        void upPart(string partialWord, Node* root, int kVert);
        void extendRight(string partialWord, Node* node, Tile tile);
        void extendDown(string partialWord, Node* node, Tile tile);
        void legalMove(string word, int x_coord, int y_coord, string move_direction);

        Board();
};

#endif