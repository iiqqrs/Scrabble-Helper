#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include <algorithm>
#include "Board.h"
using namespace std;

//Make bool for tile is_anchor? and set k value for anchor (number of non anchors to the left)
// //South should work in update() function. Now just delete the letters that don't make words

void Board::update(int i, int j, string direction){
    string tempString;
    if(direction == "North"){
        if(!theBoard[i-1][j].used){
            int tempI = i;
            int wordLength = 0;
            while(theBoard[tempI][j].used && tempI <=14){
                wordLength++;
                tempI++;
                if(tempI > 14){
                    tempI = 14;
                    break;
                }
            }
            int innerI = i;
            for(int n = 0; n < wordLength; n++){
                tempString += theBoard[innerI][j].letter;
                innerI++;
            }
            for(int k = 65; k < 91 ; k++){
                string add_me;
                add_me += char(tolower(k)); 
                tempString.insert(0, add_me);
                if(!dictionary.findWord(tempString)){
                    //cout << "Removing: " << char(tolower(k)) <<endl;
                    theBoard[i-1][j].crossVertical.erase(std::remove(theBoard[i-1][j].crossVertical.begin(), theBoard[i-1][j].crossVertical.end(), char(tolower(k))), theBoard[i-1][j].crossVertical.end());
                }
                tempString.erase(0, 1); // Should delete first char.
            }
        }
    }
    else if(direction == "South"){
        if(!theBoard[i+1][j].used){
            int tempI = i;
            int wordLength = 0;
            while(theBoard[tempI][j].used && tempI >=0){
                wordLength++;
                tempI--;
                if(tempI < 0){
                    tempI = 0;
                    break;
                }
            }
            int innerI = tempI+1;
            for(int n = 0; n < wordLength; n++){
                tempString += theBoard[innerI][j].letter;
                innerI++;
            }
            //cout << "Temp: " << tempString << endl;
            for(int k = 65; k < 91 ; k++){
                tempString += char(tolower(k));
                if (!dictionary.findWord(tempString)){
                    //cout << "Removing: " << char(tolower(k)) <<endl;
                    theBoard[i+1][j].crossVertical.erase(std::remove(theBoard[i+1][j].crossVertical.begin(), theBoard[i+1][j].crossVertical.end(), char(tolower(k))), theBoard[i+1][j].crossVertical.end());
                }
                tempString.pop_back();
            }
        }
    }
    else if(direction == "East"){
        if(!theBoard[i][j+1].used){
            int tempJ = j;
            int wordLength = 0;
            while(theBoard[i][tempJ].used && tempJ >= 0){
                wordLength++;
                tempJ--;
                if(tempJ < 0){
                    tempJ = 0;
                    break;
                }
            }
            int innerJ = tempJ+1;
            for(int n = 0; n < wordLength; n++){
                tempString += theBoard[i][innerJ].letter;
                innerJ++;
            }
            //cout << "Prefix: " << tempString << endl;
            for(int k = 65; k < 91 ; k++){
                tempString += char(tolower(k));
                if(!dictionary.findWord(tempString)){
                    //cout << "Removing: " << char(tolower(k)) <<endl;
                    theBoard[i][j+1].crossHorizontal.erase(std::remove(theBoard[i][j+1].crossHorizontal.begin(), theBoard[i][j+1].crossHorizontal.end(), char(tolower(k))), theBoard[i][j+1].crossHorizontal.end());
                }
                tempString.pop_back();
            }
        }
    }
    else if(direction == "West"){
        if(!theBoard[i][j-1].used){
            int tempJ = j;
            int wordLength = 0;
            while(theBoard[i][tempJ].used && tempJ <=14){
                wordLength++;
                tempJ++;
                if(tempJ > 14){
                    tempJ = 14;
                    break;
                }
            }
            int innerJ = j;
            for(int n = 0; n < wordLength; n++){
                tempString += theBoard[i][innerJ].letter;
                innerJ++;
            }
            for(int k = 65; k < 91 ; k++){
                string add_me;
                add_me += char(tolower(k)); 
                tempString.insert(0, add_me);
                if(!dictionary.findWord(tempString)){
                    //cout << "Removing: " << char(tolower(k)) <<endl;
                    theBoard[i][j-1].crossHorizontal.erase(std::remove(theBoard[i][j-1].crossHorizontal.begin(), theBoard[i][j-1].crossHorizontal.end(), char(tolower(k))), theBoard[i][j-1].crossHorizontal.end());
                }
                tempString.erase(0, 1); //Delete first char.
            }
        }
    }
}

void Board::updateTiles(){ // Cross check, sets anchors, updates possible chars at tile
    //Fuck.
    for(int i = 0; i < 15; i++){// Row
        for(int j = 0; j < 15; j++){//Column
            if(theBoard[i][j].used){
                if(i == 0){
                    if(j == 0){
                        //Can do south, east
                        if (!theBoard[i+1][j].used){//South
                            update(i,j, "South");
                            theBoard[i+1][j].is_anchor = true;
                        }
                        if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].is_anchor = true;
                        }
                    }
                    else if(j == 14){
                        //can do west, south
                        if(!theBoard[i][j-1].used){//West
                            update(i, j, "West");
                            theBoard[i][j-1].is_anchor = true;
                        }
                        if(!theBoard[i+1][j].used){//South
                            update(i, j, "South");
                            theBoard[i+1][j].is_anchor = true;
                        }
                    }else{
                        //Can do east, west, south
                        if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].is_anchor = true;
                        }
                        if(!theBoard[i][j-1].used){//West
                            update(i, j, "West");
                            theBoard[i][j-1].is_anchor = true;
                        }
                        if(!theBoard[i+1][j].used){//South
                            update(i, j, "South");
                            theBoard[i+1][j].is_anchor = true;
                        }
                    }
                }
                else if(i == 14){
                    if(j == 0){
                        //north, east
                        if(!theBoard[i-1][j].used){//North
                            update(i,j, "North");
                            theBoard[i-1][j].is_anchor = true;
                        }
                        if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].is_anchor = true;
                        }
                    }
                    else if(j == 14){
                        //north, west
                        if(!theBoard[i-1][j].used){//North
                            update(i,j,"North");
                            theBoard[i-1][j].is_anchor = true;
                        }
                        if(!theBoard[i][j-1].used){//West
                            update(i,j, "West");
                            theBoard[i][j-1].is_anchor = true;
                        }
                    }else{
                        //east, west, north
                        if(!theBoard[i-1][j].used){//North
                            update(i,j, "North");
                            theBoard[i-1][j].is_anchor = true;
                        }
                        if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].is_anchor = true;
                        }
                        if(!theBoard[i][j-1].used){//West
                            update(i,j, "West");
                            theBoard[i][j-1].is_anchor = true;
                        }
                    }
                }
                else if(j == 0){
                    if(i == 0){
                        // can do east, south
                        if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].is_anchor = true;
                        }
                        if(!theBoard[i+1][j].used){//South
                            update(i, j, "South");
                            theBoard[i+1][j].is_anchor = true;
                        }
                    }
                    else if(i == 14){
                        //north, east
                        if(!theBoard[i-1][j].used){//North
                            update(i,j, "North");
                            theBoard[i-1][j].is_anchor = true;
                        }  
                        if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].is_anchor = true;
                        }
                    }else{
                        //north, south, east
                        if(!theBoard[i-1][j].used){//North
                            update(i,j, "North");
                            theBoard[i-1][j].is_anchor = true;
                        }
                        if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].is_anchor = true;
                        }
                        if(!theBoard[i+1][j].used){//South
                            update(i, j, "South");
                            theBoard[i+1][j].is_anchor = true;
                        }
                    }
                }
                else if(j == 14){
                    if(i == 0){
                        //south, west
                        if(!theBoard[i+1][j].used){//South
                            update(i, j, "South");
                            theBoard[i+1][j].is_anchor = true;
                        }
                        if(!theBoard[i][j-1].used){//West
                            update(i,j, "West");
                            theBoard[i][j-1].is_anchor = true;
                        }
                    }
                    else if(i == 14){
                        //west, north
                        if(!theBoard[i-1][j].used){//North
                            update(i,j, "North");
                            theBoard[i-1][j].is_anchor = true;
                        }
                        if(!theBoard[i][j-1].used){//West
                            update(i,j, "West");
                            theBoard[i][j-1].is_anchor = true;
                        }
                    }else{
                        //north, south, west
                        if(!theBoard[i-1][j].used){//North
                            update(i,j, "North");
                            theBoard[i-1][j].is_anchor = true;
                        }
                        if(!theBoard[i+1][j].used){//South
                            update(i, j, "South");
                            theBoard[i+1][j].is_anchor = true;
                        }
                        if(!theBoard[i][j-1].used){//West
                            update(i,j, "West");
                            theBoard[i][j-1].is_anchor = true;
                        }
                    }
                }else{
                    // can do all
                    if(!theBoard[i-1][j].used){//North
                            update(i,j, "North");
                            theBoard[i-1][j].is_anchor = true;
                    }
                    if(!theBoard[i+1][j].used){//South
                            update(i, j, "South");
                            theBoard[i+1][j].is_anchor = true;
                    }
                    if(!theBoard[i][j-1].used){//West
                            update(i,j, "West");
                            theBoard[i][j-1].is_anchor = true;
                    }
                    if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].is_anchor = true;
                    }  
                }
            }
        }
    }
}
//To generate all moves from Anchorsquare, assuming that there are k 
// non-anchor squares to the left of it, we call Leftpart("", root of dawg, k)


Board::Board(){
    //Load dictionary
    ifstream werdz ("words.txt");
    string current_word;
    while(getline(werdz, current_word)){
        dictionary.newWord(current_word);
    }
    werdz.close();
    //End load of dictionary.
    
    //Begin board read in
    ifstream import_board ("Board.txt");
    string line;
    
    //Call once to load rack (first line in Board.txt)
    getline(import_board,line);
    //cout <<"Our rack: " << line <<endl;
    
    // Start anagram
    //only reading and producing seven letter words, not 6 or 5
    for (int i = 0; i < line.length(); i++) {
        if (isalpha(line[i])) {
            line[i] = tolower(line[i]);
            //cout << "Initializing board: " << line[i] << endl;
        }
    }
    sort(line.begin(), line.end());
    while(next_permutation(line.begin(), line.end())){
        int incSize = 1;
        while(incSize <= line.length()){
            string tempLine;
            for(int i = 0; i < incSize; i++){
                tempLine += line[i];
            }
            if(dictionary.findWord(tempLine)){
                if (!(find(rack_words.begin(), rack_words.end(), tempLine) != rack_words.end())){
                    rack_words.push_back(tempLine);
                }
            }
            incSize++;
        }
    }
    //End anagram
    
    for(int i=0; i<7; i++){
        Tile newTile;
        newTile.letter = line[i];
        rack.push_back(newTile);
    }
    
    //Now store the rest in board
    // Iterator should leave off at line 2 which is first line of actual board
    int vertical_count = 0;
    while(getline(import_board,line)){
        for(int i=0; i<15; i++){
            Tile newTile;
            if(isdigit(line[i])){
                switch(line[i]){
                    case '2': //2 is a double letter tile
                        newTile.letter_multip = 2;
                        break;
                    case '3': //3 is a triple letter tile
                        newTile.letter_multip = 3;
                        break;
                    case '4'://4 is a double word tile.
                        newTile.word_multip = 2;
                        break;
                    case '9': //9 is a triple word tile
                        newTile.word_multip = 3;
                        break;
                    default:
                        cout << "Don't get here please!" << endl;
                        break;
                }
            }else if(isalpha(line[i])){
                newTile.letter = tolower(line[i]);
                newTile.used = true;
            }
            theBoard[vertical_count][i] = newTile;
        }
        vertical_count++;
    }
    import_board.close();
    //End read in of board.
    
    // Now call board analyzer to update tiles for imported board.
    updateTiles();
}