#include <iostream>
#include <fstream>
#include "Trie.h"
#include "Board.h"

int main(){
    Board newB;
    
    //newB.update(10,8,"West");
    newB.updateTiles();
    
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            if (newB.theBoard[i][j].is_anchor){
                cout << "Tile at position i=" << i << " and j=" << j << endl;
                cout << "Available letters vertical: " << endl;
                for (int k = 0; k < newB.theBoard[i][j].crossVertical.size(); k++) {
                    cout << newB.theBoard[i][j].crossVertical.at(k) << endl;
                }
                cout << "Available letters horizontal: " << endl;
                for(int m = 0; m < newB.theBoard[i][j].crossHorizontal.size(); m++) {
                    cout <<  newB.theBoard[i][j].crossHorizontal.at(m) << endl;
                }
            }
        }
    }
}