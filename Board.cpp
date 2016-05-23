#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include <algorithm>
#include "Board.h"
using namespace std;

void Board::legalMove(string word, int y_coord, int x_coord, string move_direction){
    int move_score=0;
    int letterMult[word.length()];
    int wordMult[word.length()];
    //If all 7 tiles are used you get a 50 point bonus idk how we're gonna account for this
    if(move_direction == "Right"){
        //Create array of multipliers (both)
        //First find the word value (including only letter multiplier)
        //Find the highest word multiplier and multiply the word value and return.
        //cout <<"Right score" <<endl;
        int x_var = x_coord;
        for(int i=0; i < word.length(); i++){
            if(!theBoard[x_var][y_coord].used){
                letterMult[i] = theBoard[x_var][y_coord].letter_multip;
                wordMult[i] = theBoard[x_var][y_coord].word_multip;
            }
            //otherwise multiplier = 1
            letterMult[i] = 1;
            wordMult[i] = 1;
        }
        
        int wordSum=0;
        for(int i=0; i < word.length(); i++){
            wordSum += (letterMult[i] * letterValues[word[i]]);
        }
        //cout <<"word sum: " <<wordSum <<endl;
        //Find highest word multiplier
        int largestWordMult = 1;
        for(int i=0; i < word.length(); i++){
            if(wordMult[i] > largestWordMult){
                largestWordMult = wordMult[i];
            }
        }
        move_score = (wordSum*largestWordMult);
    }
    
    if(move_direction == "Down"){
        int y_var = y_coord;
        for(int i=0; i < word.length(); i++){
            if(!theBoard[x_coord][y_var].used){
                letterMult[i] = theBoard[x_coord][y_var].letter_multip;
                wordMult[i] = theBoard[x_coord][y_var].word_multip;
            }
            //otherwise multiplier = 1
            letterMult[i] = 1;
            wordMult[i] = 1;
        }
        
        int wordSum=0;
        for(int i=0; i < word.length(); i++){
            wordSum += (letterMult[i] * letterValues[word[i]]);
        }
        //Find highest word multiplier
        int largestWordMult = 1;
        for(int i=0; i < word.length(); i++){
            if(wordMult[i] > largestWordMult){
                largestWordMult = wordMult[i];
            }
        }
        move_score = (wordSum*largestWordMult);
    }
    
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
                    theBoard[i-1][j].crossVertical.erase(std::remove(theBoard[i-1][j].crossVertical.begin(), theBoard[i-1][j].crossVertical.end(), char(tolower(k))), theBoard[i-1][j].crossVertical.end());
                }
                tempString.erase(0, 1);
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
            for(int k = 65; k < 91 ; k++){
                tempString += char(tolower(k));
                if (!dictionary.findWord(tempString)){
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
            for(int k = 65; k < 91 ; k++){
                tempString += char(tolower(k));
                if(!dictionary.findWord(tempString)){
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
                    theBoard[i][j-1].crossHorizontal.erase(std::remove(theBoard[i][j-1].crossHorizontal.begin(), theBoard[i][j-1].crossHorizontal.end(), char(tolower(k))), theBoard[i][j-1].crossHorizontal.end());
                }
                tempString.erase(0, 1);
            }
        }
    }
}

void Board::updateKvals(){
    for(int i = 0; i < 15; i++){ // Row
        for(int j = 0; j < 15; j++){ //Column
            if(theBoard[i][j].anchor_vertical || theBoard[i][j].anchor_horizontal){
                //Horizontal
                int leftIt = j-1;
                int k_count_west = 0;

                while(leftIt >-1){
                    if((theBoard[i][leftIt].anchor_horizontal || theBoard[i][leftIt].anchor_vertical) || isalpha(theBoard[i][leftIt].letter)){
                        break;
                    }else{
                        k_count_west++;
                        leftIt--;
                    }
                }
                theBoard[i][j].kHorizontal = k_count_west;
                
                //Vertical
                int northIt = i-1;
                int k_count_north = 0;
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

void Board::updateTiles(){
    for(int i = 0; i < 15; i++){ // Row
        for(int j = 0; j < 15; j++){ //Column
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
                            update(i, j, "West");
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

void Board::leftPart(string partialWord, Node* root, int kHoriz, Tile tile){
    extendRight(partialWord, root, tile, false);
    if(kHoriz > 0){
        Node* tempNode = root;
        for(int i = 0; i < tempNode->children().size(); i++){
           if((find(raw_rack.begin(), raw_rack.end(), tempNode->children().at(i)->letter) != raw_rack.end())){
                char tempChar = tempNode->children().at(i)->letter;
                int rawRackIndex = 0;
                for(int j = 0; j < raw_rack.size(); j++){
                    if(raw_rack.at(j) == tempChar){
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

void Board::upPart(string partialWord, Node* root, int kVert, Tile tile){
    extendDown(partialWord, root, tile, false);
    if(kVert > 0){
        Node* tempNode = root;
        for(int i = 0; i < tempNode->children().size(); i++){
            if((find(raw_rack.begin(), raw_rack.end(), tempNode->children().at(i)->letter) != raw_rack.end())){
                char tempChar = tempNode->children().at(i)->letter;
                int rawRackIndex = 0;
                for(int j = 0; j < raw_rack.size(); j++){
                    if(raw_rack.at(j) == tempChar){
                        rawRackIndex = j;
                        break;
                    }
                }
                
                raw_rack.erase(raw_rack.begin()+rawRackIndex);
                Node* nPrime =  tempNode->children().at(i);
                
                upPart(partialWord+tempChar, nPrime, kVert-1, tile);
                raw_rack.insert(raw_rack.begin()+rawRackIndex, tempChar);
            }
        }
    }
}

void Board::extendRight(string partialWord, Node* node, Tile tile, bool prefixIsWord){
    if(!(tile.used)){ // or edge of the board?
        if((node->isComplete()) & !prefixIsWord){
            int word_length = partialWord.length();
            int x_cord = tile.xCoord - word_length;
            int y_cord = tile.yCoord;
            legalMove(partialWord, x_cord, y_cord, "Right");
        }
        
        Node* tempNode = node;
        for(int i = 0; i < tempNode->children().size(); i++){
             if(find(tile.crossVertical.begin(), tile.crossVertical.end(), tempNode->children().at(i)->letter) != tile.crossVertical.end() &&
                find(raw_rack.begin(), raw_rack.end(), tempNode->children().at(i)->letter) != raw_rack.end()){
                char tempChar = tempNode->children().at(i)->letter;
                int rawRackIndex = 0;
                for(int j = 0; j < raw_rack.size(); j++){
                    if (raw_rack.at(j) == tempChar){
                        rawRackIndex = j;
                        break;
                    }
                }
                raw_rack.erase(raw_rack.begin()+rawRackIndex);
               
                Node* nPrime =  tempNode->children().at(i);
                if(((tile.xCoord)+1) < 14){
                    Tile nextTile = theBoard[tile.yCoord][tile.xCoord+1];
                    extendRight(partialWord+tempChar, nPrime, nextTile, false);
                    raw_rack.insert(raw_rack.begin()+rawRackIndex, tempChar);
                }
            }
        }
    }else{
        char charInTile = tile.letter;
        Node* tempNode = node;
        for(int i = 0; i < tempNode->children().size(); i++){
            if(tempNode->children().at(i)->letter == charInTile){
                Tile nextTile = theBoard[tile.yCoord][tile.xCoord+1];
                extendRight(partialWord+charInTile, tempNode->children().at(i), nextTile, false);
            }
        }
    }
}

void Board::extendDown(string partialWord, Node* node, Tile tile, bool prefixIsWord){
    if(!(tile.used)){
        if((node->isComplete()) & !prefixIsWord){
           int word_length = partialWord.length();
           int x_cord = tile.xCoord;
           int y_cord = tile.yCoord - word_length;
           legalMove(partialWord, x_cord, y_cord, "Down");
        }
        
        Node* tempNode = node;
        for(int i = 0; i < tempNode->children().size(); i++){
             if(find(tile.crossHorizontal.begin(), tile.crossHorizontal.end(), tempNode->children().at(i)->letter) != tile.crossHorizontal.end() &&
                find(raw_rack.begin(), raw_rack.end(), tempNode->children().at(i)->letter) != raw_rack.end()){
                char tempChar = tempNode->children().at(i)->letter;
                
                int rawRackIndex = 0;
                for(int j = 0; j < raw_rack.size(); j++){
                    if(raw_rack.at(j) == tempChar){
                        rawRackIndex = j;
                        break;
                    }
                }
                raw_rack.erase(raw_rack.begin()+rawRackIndex);
                Node* nPrime =  tempNode->children().at(i);
                
                if(!(((tile.yCoord)+1) > 14)){
                    Tile nextTile = theBoard[tile.yCoord+1][tile.xCoord];
                    extendDown(partialWord+tempChar, nPrime, nextTile, false);
                    raw_rack.insert(raw_rack.begin()+rawRackIndex, tempChar);
                }
            }
        }
    }else{
        char charInTile = tile.letter;
        Node* tempNode = node;
        for(int i = 0; i < tempNode->children().size(); i++){
            if(tempNode->children().at(i)->letter == charInTile){
                Tile nextTile = theBoard[tile.yCoord+1][tile.xCoord];
                extendDown(partialWord+charInTile, tempNode->children().at(i), nextTile, false);
            }
        }
    }
}

void Board::placeHorizontal(int row, int col){
    if(col > 0){
        if(theBoard[row][col-1].used){
            string prefix;
            Tile tileIt = theBoard[row][col-1];
            int colIt = col-1;
            while((tileIt.used) && colIt >= 0){
                prefix += theBoard[row][colIt].letter;
                colIt--;
                tileIt = theBoard[row][colIt];
            }
            string flipPrefix;
            for(int wrdLength = prefix.length()-1; wrdLength >= 0; wrdLength--){
                flipPrefix += prefix[wrdLength];
            }
            Node* partialNode = dictionary.findPartial(flipPrefix);
            
            if(dictionary.findWord(flipPrefix)){
                extendRight(flipPrefix, partialNode, theBoard[row][col], true);
            }
            else if(partialNode != 0){
                extendRight(flipPrefix, partialNode, theBoard[row][col], false); 
            }
        }else{
            if (row < 14){
                row = row+1;
            }
            leftPart("", dictionary.getRoot(), theBoard[row][col].kHorizontal, theBoard[row][col]);
        }
    }else{
        if (row < 14){
            row = row+1;
        }        
        leftPart("", dictionary.getRoot(), theBoard[row][col].kHorizontal, theBoard[row][col]);
    }
}

void Board::placeVertical(int row, int col){
    if(row > 0){
        if(theBoard[row-1][col].used){
            string prefix = "";
            Tile tileIt = theBoard[row-1][col];
            int rowIt = row-1;
            while((tileIt.used) && rowIt >= 0){
                prefix += theBoard[rowIt][col].letter;
                rowIt--;
                if(rowIt < 0){
                    break;
                }
                tileIt = theBoard[rowIt][col];
            }
            string flipPrefix;
            for(int wrdLength = prefix.length()-1; wrdLength >= 0; wrdLength--){
                flipPrefix += prefix[wrdLength];
            }
            Node* partialNode = dictionary.findPartial(flipPrefix);
            
            if(dictionary.findWord(flipPrefix)){
                extendDown(flipPrefix, partialNode, theBoard[row][col], true);
            }else if(partialNode != 0){
                extendDown(flipPrefix, partialNode, theBoard[row][col], false); 
            }
        }else{
            if(col < 14){
                col = col+1;
            }
            upPart("", dictionary.getRoot(), theBoard[row][col].kVertical, theBoard[row][col]);
        }
    }else{
        if(col < 14){
            col = col+1;
        }        
        upPart("", dictionary.getRoot(), theBoard[row][col].kVertical, theBoard[row][col]);
    }
}

//Wrapper function that facilitates the placement of a word
//This function will call all helper functions/attributes (leftExtend(), rightExtend(), is_anchor, etc..)
void Board::placeWord(){
    for(int row = 0; row < 15; row++){
        for(int col = 0; col < 15; col++){
            if(theBoard[row][col].anchor_horizontal && theBoard[row][col].anchor_vertical){ //If tile is both vertical and horizontal anchor
                placeHorizontal(row,col);
                placeVertical(row,col);
            }else if((theBoard[row][col].anchor_horizontal)){ //If tile is only a horizontal anchor
                placeHorizontal(row,col);
            }
            else if(theBoard[row][col].anchor_vertical){ //If tile is only a vertical anchor
                placeVertical(row,col);
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
            if (!(find(rack_words.begin(), rack_words.end(), tempLine) != rack_words.end())){
                rack_words.push_back(tempLine);
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
            newTile.xCoord = i;
            newTile.yCoord = vertical_count;
            theBoard[vertical_count][i] = newTile;
        }
        vertical_count++;
    }
    import_board.close();
    //End read in of board.
    
    //Load letter vals into map
    ifstream letter_vals ("Values.txt");
    while(getline(letter_vals,line)){
        string int_string;
        char temp_char = tolower(line[0]);
        for(int i=2; i < line.length(); i++){
            int_string += char(tolower(line[i]));
        }
        int temp_int = stoi(int_string);
        //cout << "letter: " << temp_char << " Value: " << temp_int << endl;
        letterValues.insert(pair<char,int>(temp_char, temp_int));
    }
    letter_vals.close();
    //Finish load letter vals into map
    
    // Now call board analyzer to update tiles for imported board.
    updateTiles();
}