#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include <algorithm>
#include "Board.h"
using namespace std;

//TO DO:
//    Progress was made on extend. It's now taking the letters pre-placed on the board and making possible word combos with them

//    Problem is, it's still including words that don't use the tiles on the board
//    I think this is only a problem for when all word generations are placed to the right or left of the anchor (the anchor isn't getting included)
//
//   The current output is an illusion. It looks like it works, but it's still not including words where the pre-placed tile is in front of the letters
//   from the rack
//
//   UPDATE: I may be wrong. It may actually work. Let's check it.

void Board::legalMove(string word, int x_coord, int y_coord, string move_direction){
    int move_score;
    //Actually score move here
    
    
    //Make a new move and enter into priority queue
    Move m;
    m.score = move_score;
    m.full_word = word;
    m.x = x_coord;
    m.y = y_coord;
    m.direction = move_direction;
    scored_moves.push(m);
}

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

void Board::updateKvals(){
    for(int i = 0; i < 15; i++){// Row
        for(int j = 0; j < 15; j++){//Column
            if(theBoard[i][j].anchor_vertical || theBoard[i][j].anchor_horizontal){
                //cout << "Ever get here" <<endl;
                //Horizontal
                int leftIt = j-1;
                int k_count_west = 0;

                while(leftIt >-1){
                    if((theBoard[i][leftIt].anchor_horizontal || theBoard[i][leftIt].anchor_vertical) || isalpha(theBoard[i][leftIt].letter)){ // letter = ' ' does this show up as alpha (in constructor)
                        //cout << "K: " << k_count_west <<endl;
                        break;
                    }else{
                        k_count_west++;
                        //cout << "i: " << i << " j " << j << " k incrementing?: " << k_count_west << endl;
                        leftIt--;
                    }
                }
                theBoard[i][j].kHorizontal = k_count_west;
                
                
                //Vertical
                int northIt = i-1;
                int k_count_north = 0;
                //cout << "northIt " << northIt << endl;
                while(northIt > -1){
                    if((theBoard[i][leftIt].anchor_horizontal || theBoard[i][leftIt].anchor_vertical) || isalpha(theBoard[northIt][j].letter)){
                        break;
                    }else{
                        k_count_north++;
                        northIt--;
                    }
                }
                theBoard[i][j].kVertical = k_count_north;
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
                            theBoard[i+1][j].anchor_vertical = true;
                        }
                        if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].anchor_horizontal = true;
                        }
                    }
                    else if(j == 14){
                        //can do west, south
                        if(!theBoard[i][j-1].used){//West
                            update(i, j, "West");
                            theBoard[i][j-1].anchor_horizontal = true;
                        }
                        if(!theBoard[i+1][j].used){//South
                            update(i, j, "South");
                            theBoard[i+1][j].anchor_vertical = true;
                        }
                    }else{
                        //Can do east, west, south
                        if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].anchor_horizontal = true;
                        }
                        if(!theBoard[i][j-1].used){//West
                            update(i,j, "West");
                            theBoard[i][j-1].anchor_horizontal = true;
                        }
                        if(!theBoard[i+1][j].used){//South
                            update(i, j, "South");
                            theBoard[i+1][j].anchor_vertical = true;
                        }
                    }
                }
                else if(i == 14){
                    if(j == 0){
                        //north, east
                        if(!theBoard[i-1][j].used){//North
                            update(i,j, "North");
                            theBoard[i-1][j].anchor_vertical = true;
                        }
                        if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].anchor_horizontal = true;
                        }
                    }
                    else if(j == 14){
                        //north, west
                        if(!theBoard[i-1][j].used){//North
                            update(i,j,"North");
                            theBoard[i-1][j].anchor_vertical = true;
                        }
                        if(!theBoard[i][j-1].used){//West
                            update(i,j, "West");
                            theBoard[i][j-1].anchor_horizontal = true;
                        }
                    }else{
                        //east, west, north
                        if(!theBoard[i-1][j].used){//North
                            update(i,j, "North");
                            theBoard[i-1][j].anchor_vertical = true;
                        }
                        if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].anchor_horizontal = true;
                        }
                        if(!theBoard[i][j-1].used){//West
                            update(i,j, "West");
                            theBoard[i][j-1].anchor_horizontal = true;
                        }
                    }
                }
                else if(j == 0){
                    if(i == 0){
                        // can do east, south
                        if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].anchor_horizontal = true;
                        }
                        if(!theBoard[i+1][j].used){//South
                            update(i, j, "South");
                            theBoard[i+1][j].anchor_vertical = true;
                        }
                    }
                    else if(i == 14){
                        //north, east
                        if(!theBoard[i-1][j].used){//North
                            update(i,j, "North");
                            theBoard[i-1][j].anchor_vertical = true;
                        }  
                        if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].anchor_horizontal = true;
                        }
                    }else{
                        //north, south, east
                        if(!theBoard[i-1][j].used){//North
                            update(i,j, "North");
                            theBoard[i-1][j].anchor_vertical = true;
                        }
                        if(!theBoard[i][j+1].used){//East
                            update(i,j, "East");
                            theBoard[i][j+1].anchor_horizontal = true;
                        }
                        if(!theBoard[i+1][j].used){//South
                            update(i, j, "South");
                            theBoard[i+1][j].anchor_vertical = true;
                        }
                    }
                }
                else if(j == 14){
                    if(i == 0){
                        //south, west
                        if(!theBoard[i+1][j].used){//South
                            update(i, j, "South");
                            theBoard[i+1][j].anchor_vertical = true;
                        }
                        if(!theBoard[i][j-1].used){//West
                            update(i,j, "West");
                            theBoard[i][j-1].anchor_horizontal = true;
                        }
                    }
                    else if(i == 14){
                        //west, north
                        if(!theBoard[i-1][j].used){//North
                            update(i,j, "North");
                            theBoard[i-1][j].anchor_vertical = true;
                        }
                        if(!theBoard[i][j-1].used){//West
                            update(i,j, "West");
                            theBoard[i][j-1].anchor_horizontal = true;
                        }
                    }else{
                        //north, south, west
                        if(!theBoard[i-1][j].used){//North
                            update(i,j, "North");
                            theBoard[i-1][j].anchor_vertical = true;
                        }
                        if(!theBoard[i+1][j].used){//South
                            update(i, j, "South");
                            theBoard[i+1][j].anchor_vertical = true;
                        }
                        if(!theBoard[i][j-1].used){//West
                            update(i,j, "West");
                            theBoard[i][j-1].anchor_horizontal = true;
                        }
                    }
                }else{
                    // can do all
                    if(!theBoard[i-1][j].used){//North
                            update(i,j, "North");
                            theBoard[i-1][j].anchor_vertical = true;
                    }
                    if(!theBoard[i+1][j].used){//South
                            update(i, j, "South");
                            theBoard[i+1][j].anchor_vertical = true;
                    }
                    if(!theBoard[i][j-1].used){//West
                            update(i,j, "West");
                            theBoard[i][j-1].anchor_horizontal = true;
                    }
                    if(!theBoard[i][j+1].used){//East
                            update(i, j, "East");
                            theBoard[i][j+1].anchor_horizontal = true;
                    }  
                }
            }
        }
    }
    updateKvals();
}
//To generate all moves from Anchorsquare, assuming that there are k 
// non-anchor squares to the left of it, we call Leftpart("", root of dawg, k)
void Board::leftPart(string partialWord, Node* root, int kHoriz, Tile tile) {
    extendRight(partialWord, root, tile);
    //cout << "finished right" << endl;
    if (kHoriz > 0) {
        //cout << "in here" << endl;
        Node* tempNode = root;
        for (int i = 0; i < tempNode->children().size(); i++) {
            //cout << "over here" << endl;
            
            /*for(int m = 0; m < raw_rack.size(); m ++) {
                cout << "The letter is: " << tempNode->children().at(i)->letter << " vs. " << raw_rack.at(m) << endl;
            }*/
            if ((find(raw_rack.begin(), raw_rack.end(), tempNode->children().at(i)->letter) != raw_rack.end())){
                char tempChar = tempNode->children().at(i)->letter;
                int rawRackIndex = 0;
                for (int j = 0; j < raw_rack.size(); j++) {
                    if (raw_rack.at(j) == tempChar) {
                        rawRackIndex = j;
                        break;
                    }
                }
                
                raw_rack.erase(raw_rack.begin()+rawRackIndex);
                Node* nPrime =  tempNode->children().at(i);
                
                leftPart(partialWord+tempChar, nPrime, kHoriz-1, tile);
                raw_rack.insert(raw_rack.begin()+rawRackIndex, tempChar);
            }
        }
    }
}

void Board::upPart(string partialWord, Node* root, int kVert) {
    
}

void Board::extendRight(string partialWord, Node* node, Tile tile) {
    //cout << "Incomplete word: " << partialWord << endl;
    if (!(tile.used)) {
        if ((node->isComplete())) {
           if((theBoard[tile.yCoord][(tile.xCoord)+1]).used || theBoard[tile.yCoord][tile.xCoord - partialWord.length()-1].used){
               //cout << "Got here with: " << partialWord << endl;
           }else{
               //cout << "x coordinate: " << tile.xCoord << " y coordinate: " << tile.yCoord << " of tile with letter: " << partialWord[partialWord.length()-1] << endl;
               cout << "Full word: " << partialWord << endl;
               int word_length = partialWord.length();
               int x_cord = tile.xCoord - word_length;
               int y_cord = tile.yCoord;
               legalMove(partialWord, x_cord, y_cord, "Right");
           }
        }
        
        Node* tempNode = node;
        for (int i = 0; i < tempNode->children().size(); i++) {
             if (find(tile.crossVertical.begin(), tile.crossVertical.end(), tempNode->children().at(i)->letter) != tile.crossVertical.end() &&
                find(raw_rack.begin(), raw_rack.end(), tempNode->children().at(i)->letter) != raw_rack.end()) {
                char tempChar = tempNode->children().at(i)->letter;
                
                int rawRackIndex = 0;
                for (int j = 0; j < raw_rack.size(); j++) {
                    if (raw_rack.at(j) == tempChar) {
                        rawRackIndex = j;
                        break;
                    }
                }
                
                raw_rack.erase(raw_rack.begin()+rawRackIndex);
               
                Node* nPrime =  tempNode->children().at(i);
                //cout << "Next tile has y coord: " << tile.yCoord << " and x coord: " << tile.xCoord << endl;
                //cout << "tile.xCoord+1: " << (tile.xCoord)+1 << endl;
                if (!(((tile.xCoord)+1) > 14)) {
                    Tile nextTile = theBoard[tile.yCoord][tile.xCoord+1];
                    //cout << "Next tile has y coord: " << nextTile.yCoord << " and x coord: " << nextTile.xCoord << endl;
                    //cout << "about to recurse" << endl;
                    extendRight(partialWord+tempChar, nPrime, nextTile);
                    raw_rack.insert(raw_rack.begin()+rawRackIndex, tempChar);
                }
            }
        }
    }else{
        char charInTile = tile.letter;
        Node* tempNode = node;
        for (int i = 0; i < tempNode->children().size(); i++) {
            if (tempNode->children().at(i)->letter == charInTile) {
                Tile nextTile = theBoard[tile.yCoord][tile.xCoord+1];
                extendRight(partialWord+charInTile, tempNode->children().at(i), nextTile);
            }
        }
    }
}

void Board::extendDown(string partialWord, Node* node, Tile tile){
    
}

//Wrapper function that facilitates the placement of a word
//This function will call all helper functions/attributes (leftExtend(), rightExtend(), is_anchor, etc..)
void Board::placeWord() {
    for (int row = 0; row < 15; row++) {
        for(int col = 0; col < 15; col++) {
            if (theBoard[row][col].anchor_horizontal && theBoard[row][col].anchor_vertical) { //If tile is both vertical and horizontal anchor
                //for (int rackWord = 0; rackWord < rack_words.size(); rackWord++) {
                    //string word = rack_words[rackWord];
                    //If statement that checks if first letter of rack word is in both cross-check vectors
                   //if (find(theBoard[row][col].crossHorizontal.begin(), theBoard[row][col].crossHorizontal.end(), word[word.length()-1]) != theBoard[row][col].crossHorizontal.end()
                        //&& find(theBoard[row][col].crossVertical.begin(), theBoard[row][col].crossVertical.end(), word[word.length()-1]) != theBoard[row][col].crossVertical.end()) {
                        cout << "Tile is at x: " << theBoard[row][col].xCoord << " y: " << theBoard[row][col].yCoord << " with kHorizontal: " << theBoard[row][col].kHorizontal << endl;
                        leftPart("", dictionary.getRoot(), theBoard[row][col].kHorizontal, theBoard[row][col]); 
                       
                    //}
                //}
            }
            else if ((theBoard[row][col].anchor_horizontal)) { //If tile is only a horizontal anchor
                //for (int rackWord = 0; rackWord < rack_words.size(); rackWord++) {
                    //string word = rack_words[rackWord];
                    //if (find(theBoard[row][col].crossHorizontal.begin(), theBoard[row][col].crossHorizontal.end(), word[word.length()-1]) != theBoard[row][col].crossHorizontal.end()) {
                         leftPart("", dictionary.getRoot(), theBoard[row][col].kHorizontal, theBoard[row][col]);
                        
                    //}
            }
            else if (theBoard[row][col].anchor_vertical) { //If tile is only a vertical anchor
                //for (int rackWord = 0; rackWord < rack_words.size(); rackWord++) {
                    //string word = rack_words[rackWord];
                    //if (find(theBoard[row][col].crossVertical.begin(), theBoard[row][col].crossVertical.end(), word[word.length()-1]) != theBoard[row][col].crossVertical.end()) {
                         leftPart("", dictionary.getRoot(), theBoard[row][col].kHorizontal, theBoard[row][col]);
                
                    //}
                //}
            }else{
                continue;
            }
        }
    }
}

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
    for (int i = 0; i < line.length(); i++) {
        raw_rack.push_back(tolower(line[i]));
    }
    // Start anagram
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
            //if(dictionary.findWord(tempLine)){
                if (!(find(rack_words.begin(), rack_words.end(), tempLine) != rack_words.end())){
                    rack_words.push_back(tempLine);
                }
            //}
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
            newTile.xCoord = i;
            newTile.yCoord = vertical_count;
            theBoard[vertical_count][i] = newTile;
        }
        vertical_count++;
    }
    import_board.close();
    //End read in of board.
    
    // Now call board analyzer to update tiles for imported board.
    updateTiles();
}