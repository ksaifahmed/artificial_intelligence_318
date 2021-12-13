#include <bits/stdc++.h>
using namespace std;

struct Board{
    int * pockets;
    Board(){
        pockets =new int[14];
        for(int i=0; i<14; i++) pockets[i] = 4;
        pockets[0] = pockets[13] = 0;
    }

    Board getCopy() {
        Board board;
        for(int i=0; i<14; i++)
            board.pockets[i] = this->pockets[i];
        return board;
    }
};



void printBoard(Board board){
    cout << "\t";
    for(int i=1; i<7; i++) cout << board.pockets[i] << " ";
    cout << endl << board.pockets[0] << "\t\t\t " << board.pockets[13] << endl << "\t";
    for(int i=7; i<13; i++) cout << board.pockets[i] << " ";
    cout << endl;
}

int main() {
    Board b, copy;
    b.pockets[13] = 34;
    //copy = b.getCopy();
    printBoard(copy);
    return 0;
}
