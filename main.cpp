#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
using namespace std;
bool fixedCells[9][9];


void titleScreen(){             // title splash https://patorjk.com/software/taag/#p=display&f=Letter&t=sodoku&x=none&v=4&h=4&w=80&we=false
    cout<<  " SSSS  OOO  DDDD   OOO  K   K U   U "<<endl;
    cout<<  "S     O   O D   D O   O K  K  U   U"<<endl; 
    cout<<  " SSS  O   O D   D O   O KKK   U   U"<<endl; 
    cout<<  "    S O   O D   D O   O K  K  U   U "<<endl;
    cout<<  "SSSS   OOO  DDDD   OOO  K   K  UUU"<<endl;
    system("pause");
}

void endScreen(){             // end screen
    cout<<"congratulations you solved it"<<endl;
    system("pause");
}

void clearScreen(){
    // Source - https://stackoverflow.com/a/32008479
    // Posted by catzilla, modified by community. See post 'Timeline' for change history
    // Retrieved 2026-09-27, License - CC BY-SA 3.0

    cout << "\033[2J\033[1;1H";
}

void initFixedCells(int board[9][9]){
    for (int row = 0; row < 9; row++){
            for (int col = 0; col < 9; col++){
                fixedCells[row][col] = (board[row][col] != 0);
            }
    }
}

bool loadBoardFromFile(const string& filename, int board[9][9]){    //loads the board from file 
    ifstream inFile(filename);
    if (!inFile){
        cerr << "Unable to open " << filename << endl;
        return false;
    }

    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            if (!(inFile >> board[row][col])){
                cerr << "shits fucked" << endl;
                return false;
            }
        }
    }
    return true;
}

void printBoard(int board[9][9]){           //outputs the board nicely

    clearScreen();
    cout << " +-A-B-C-+-D-E-F-+-G-H-I-+" << endl;
    for (int row = 0; row < 9; row++){
        if (row % 3 == 0){
            cout << " +-------+-------+-------+" << endl;
        }

        cout << row + 1;
        cout << "| ";

        for (int col = 0; col < 9; col++){
            if (fixedCells[row][col]) {
                cout << "\033[1m" << board[row][col] << "\033[0m ";
            }
            else {
                cout << "\033[34m" << board[row][col] << "\033[0m ";
            }
            if (col % 3 == 2){
                cout << (col == 8 ? "|" : "| ");
            }
        }
        cout << endl;
    }
    cout << " +-------+-------+-------+" << endl;
}

bool isBoardSolved(int board[9][9]){        //checks if the board is solved outputs true or false
    for (int row = 0; row < 9; row++){      //checks rows
        bitset<10> check;
        for (int col = 0; col < 9; col++){
            int value = board[row][col];
            if (value < 1 || value > 9 || check[value]){
                //cout << "error row aaa " << row << col << value << endl;
                return false;
                
            }
            check[value] = true;
        }
    }
    for (int col = 0; col < 9; col++){      //checks colombs 
        bitset<10> check;
        for (int row = 0; row < 9; row++){
            int value = board[row][col];
            if (value < 1 || value > 9 || check[value]){
                cout <<"error col" << col << endl;
                return false;
            
            }
            check[value] = true;
        }
    }
    for (int startRow = 0; startRow < 9; startRow += 3){      //checks sub grids
        for (int startCol = 0; startCol < 9; startCol += 3){
            bitset<10> check;
            for (int row = startRow; row < startRow + 3; row++){
                for (int col = startCol; col < startCol + 3; col++){
                    int value = board[row][col];
                    if (value < 1 || value > 9 || check[value]){
                        cout <<"error subgrid" << endl;
                        return false;
                    }
                    check[value] = true;
                }
            }
        }
    }
    return true;
}

bool makeMove(string action, int board[9][9]){
    
    char colChar = action[0];
    int col = toupper(colChar) - 'A';
    int row = action[2] - '0' - 1;
    int newNum = action[4] - '0';
    //cout << col << row << newNum << endl;

    if (col < 0 || col >= 9 || row < 0 || row >= 9 || newNum < 1 || newNum > 9) {
        cout << "value out of range" << endl;
        return false;
    }

    if (fixedCells[row][col]) {
        cout << "cell is locked" << endl;
return false;
    }

    board[row][col] = newNum;
    return true;
}

bool checkMove(string action){
    if (action == "na"){
        return false;
    }
    char colChar = action[0];    
    int col = toupper(colChar) - 'A';
    int row = action[2] - '0' - 1;
    int newNum = action[4] - '0';
    if (col < 0 || col >= 9 || row < 0 || row >= 9 || newNum < 1 || newNum > 9) {
        cout << "value out of range" << endl;
        return false;
    }

    if (fixedCells[row][col]) {
        cout << "cell is locked" << endl;
    return false;
    }
    return true;
}

bool validateMove(int row, int col, int num, int board[9][9]){
    //check row
    for (int i = 0; i < 9; i++){
        if (board[row][i] == num){
            return false;
        }
    }
    //check col
    for (int i = 0; i < 9; i++){
        if (board[i][col] == num){
            return false;
        }
    }
    
    //check sub grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (board[startRow + i][startCol + j] == num){
                return false;
            } 
        }
    }
    return true;
}

bool solveIt(int board[9][9]){

    bitset<10> options[9][9];
    bitset<10> checkRow[9];
    bitset<10> checkCol[9];
    bitset<10> checkGrid[9];
    for (int row = 0; row < 9; row++){      //checks rows
            for (int col = 0; col < 9; col++){
                int value = board[row][col];
                if (value == 0) continue;
                if (value < 0 || value > 9 || checkRow[row][value]){
                    cout << "error row" << endl;
                    return false;
                }
                checkRow[row][value] = true; 
            }
        }
    for (int col = 0; col < 9; col++){      //checks col
        for (int row = 0; row < 9; row++){
            int value = board[row][col];
            if (value == 0) continue;
            if (value < 0 || value > 9 || checkCol[col][value]){
                cout << "error col" << endl;
                return false;
            }
                checkCol[col][value] = true;
            }
        }
    for (int startRow = 0; startRow < 9; startRow += 3){      //checks sub grids
        for (int startCol = 0; startCol < 9; startCol += 3){
            int grid = (startRow / 3) * 3 + (startCol / 3);
            for (int row = startRow; row < startRow + 3; row++){
                for (int col = startCol; col < startCol + 3; col++){
                    int value = board[row][col];
                    if (value == 0) continue;
                    if (value < 0 || value > 9 || checkGrid[grid][value]){
                        cout <<"error subgrid" << endl;
                        return false;
                    }
                    checkGrid[grid][value] = true;
                }
            }
        }
    }
    for (int row = 0; row < 9; row++){      //combine all bit arrays into one bitmap
        for (int col = 0; col < 9; col++){
            if (board[row][col] != 0){
                continue;
            }
            int box = (row / 3) * 3 + col / 3;
            options[row][col] = ~(checkRow[row] | checkCol[col] | checkGrid[box]);
            options[row][col].reset(0);
        }
    }
    
    int bestRow = -1;
    int bestCol = -1;
    int fewestOptions = 10;
    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            if (board[row][col] == 0){
                int optionCount = options[row][col].count();
                if (optionCount == 0){
                    return false;
                }
                if (optionCount < fewestOptions){
                    bestRow = row;
                    bestCol = col;
                    fewestOptions = optionCount;
                }
            }
        }
    }

    if (bestRow == -1){
        return true;
    }

    for (int value = 1; value <= 9; value++){
        if (options[bestRow][bestCol].test(value)){
            board[bestRow][bestCol] = value;
            if (solveIt(board)){
                return true;
            }
            board[bestRow][bestCol] = 0;
        }
    }
    return false;
}



int main(){
    int board[9][9];

    titleScreen();
    if (!loadBoardFromFile("board.txt", board)){
        cout << "ruh roh" << endl;
        return 1;
    }

    initFixedCells(board);
     
    string action= "na";
    string solve = "SOLVE";

    while (!(isBoardSolved(board))){
        printBoard(board);

        cout << "Enter your action in the form [columnD]-[row]=[number] eg. A-1=5"<< endl;
        checkMove(action);
        cin >> action;
        if (action == solve){
            solveIt(board);
        }
        else {
            makeMove(action,board);
        }
    }
    if (isBoardSolved(board)){
        clearScreen();
        printBoard(board);
        endScreen();
    }
    ;
}