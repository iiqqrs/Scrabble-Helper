#include <iostream>
#include <fstream>
#include "Trie.h"
#include "Board.h"

int main(){
    Board newB;
    newB.updateTiles();
    newB.placeWord();
    
    //This should be our final output :)
    for(int i = 0; i < 20; i++){
        Move m = newB.scored_moves.top();
        newB.scored_moves.pop();
        if(i == 0){
            cout << "Best move - Score: " << m.score << " Word: "<< m.full_word << " Coords(x,y): (" << m.x << "," << m.y << ") " << m.direction << endl;
        }else{
            cout << "Other Moves - Score: " << m.score << " Word: "<< m.full_word << " Coords(x,y): (" << m.x << "," << m.y << ") "<< m.direction << endl;
        }
    }
}