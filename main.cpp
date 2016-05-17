#include <iostream>
#include <fstream>
#include "Trie.h"
#include "Board.h"

int main(){
    Board newB;
    
    newB.updateTiles();
    newB.placeWord();
    
    //Testing cross check
    /*for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++) {
            if (newB.theBoard[i][j].anchor_vertical || newB.theBoard[i][j].anchor_horizontal){
                
                cout << "i: " << i << " j: " << j << " K_w: " <<  newB.theBoard[i][j].kHorizontal << endl;
                cout << "i: " << i << " j: " << j << " K_n: " <<  newB.theBoard[i][j].kVertical << endl;
            }
        }
    }*/
    
    
}