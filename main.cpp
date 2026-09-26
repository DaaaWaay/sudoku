#include <iostream>
#include <fstream>
#include <vector>
using namespace std;



void titleScreen(){
    cout<<"SUDOKU"<<endl;
    system("pause");
}

int loadBoardFromFile(string filename, int board[9][9]){
    ifstream inFile(filename);

    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            if (!(inFile >> board[row][col])){
                cerr << "shits fucked"<<endl;
            }
        }
    }
    return board[9][9];
}
void clear() {                                                                      //stolen from stack over flow https://stackoverflow.com/questions/6486289/how-to-clear-the-console-in-c
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

void printBoard(int board[9][9]){

    clear();
    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            cout << board[row][col] <<endl;
        }
        cout << "\n" <<endl;
    }
}


int main(){
    int board[9][9];

    titleScreen();
    loadBoardFromFile("board.txt", board);
    printBoard(board);
} 