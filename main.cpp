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
    char ColTmp = action[0];
    int col = ColTmp - 'A' + 1;
    int row = action[2] - '0';
    int newNum = action[4] - '0';
    cout << col << row << newNum << endl;

    if (!(1 < col && col < 9 && 1 < row && row < 9 && 1 < newNum && newNum < 9 )){
        if (fixedCells[row][col]){
            board[row][col] = newNum;
            return true;
        }
        else{
            cout << "cell is locked" << endl;
            return false;
        }
    }
    else{
        cout << "value out of range" << endl;
        return false;
    }

return false;
}



int main(){
    int board[9][9];

    titleScreen();
    if (!loadBoardFromFile("board.txt", board)){
        return 1;
    }
    
    initFixedCells(board);

    printBoard(board);

    while (!(isBoardSolved(board))){
        printBoard(board);

        string action;
        cout << "Enter your action in the form [colomb]-[row]=[number] eg. A-1=5"<< endl;
        cin >> action;
        makeMove(action,board);
    }
    endScreen();
}