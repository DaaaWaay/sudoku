#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
using namespace std;
bool fixedCells[9][9];


void titleScreen(){             // title splash
    cout<<"SUDOKU"<<endl;
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

void printBoard(int board[9][9]){       //outputs the board nicely

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
    return true;
    //todo check squares
}

bool makeMove(string action, int board[9][9]){

    char colChar = action[0];
    int col = colChar - 'A';
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
    int col = colChar - 'A';
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


int main(){
    int board[9][9];

    titleScreen();
    if (!loadBoardFromFile("board.txt", board)){
        return 1;
    }

    initFixedCells(board);
     
    string action;
    action = "na";

    while (!(isBoardSolved(board))){
        printBoard(board);

    
        cout << "Enter your action in the form [colomb]-[row]=[number] eg. A-1=5"<< endl;
        checkMove(action);
        cin >> action;
        makeMove(action,board);
    }
    endScreen();
}