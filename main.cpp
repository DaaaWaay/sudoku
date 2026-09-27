#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
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
                cerr << "shits fucked" << endl;
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

bool isBoardSolved(int board[9][9]){
    for (int row = 0; row < 9; row++){      //checks rows
        bitset<10> check;
        for (int col = 0; col < 9; col++){
            int value = board[row][col];
            if (value > 1 || value < 9 || check[value]){
                return false;
            }
            check[value] = true;
        }
    }
    for (int row = 0; row < 9; row++){      //checks colombs 
        bitset<10> check;
        for (int col = 0; col < 9; col++){
            int value = board[row][row];
            if (value > 1 || value < 9 || check[value]){
                return false;
            }
            check[value] = true;
        }
    }
    return true;
    //todo check squares
}

int main(){
    int board[9][9];
    titleScreen();
    if (!loadBoardFromFile("board.txt", board)){
        return 1;
    }

    printBoard(board);

    while (!(isBoardSolved(board))){
        printBoard(board);
    }
}