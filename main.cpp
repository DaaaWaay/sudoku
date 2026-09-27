#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void titleScreen(){
    cout<<"SUDOKU"<<endl;
    system("pause");
}

bool loadBoardFromFile(const string& filename, int board[9][9]){
    ifstream inFile(filename);
    if (!inFile){
        cerr << "Unable to open " << filename << endl;
        return false;
    }

    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            if (!(inFile >> board[row][col])){
                cerr << "Unable to read the complete 9x9 board from " << filename << endl;
                return false;
            }
        }
    }
    return true;
}

void printBoard(int board[9][9]){
    for (int row = 0; row < 9; row++){
        if (row % 3 == 0){
            cout << "+-------+-------+-------+" << endl;
        }
        cout << "| ";
        for (int col = 0; col < 9; col++){
            cout << board[row][col] << ' ';
            if (col % 3 == 2){
                cout << (col == 8 ? "|" : "| ");
            }
        }
        cout << endl;
    }
    cout << "+-------+-------+-------+" << endl;
}


int main(){
    int board[9][9];
    titleScreen();
    if (!loadBoardFromFile("board.txt", board)){
        return 1;
    }
    printBoard(board);
}