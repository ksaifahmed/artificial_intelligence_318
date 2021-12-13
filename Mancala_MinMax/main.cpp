#include <bits/stdc++.h>

using namespace std;

struct Board {
    int *pockets;

    Board() {
        pockets = new int[14];
    }

    void init_board() const {
        for (int i = 0; i < 14; i++) pockets[i] = 4;
        pockets[0] = pockets[7] = 0;
    }
};


Board getCopy(Board board) {
    Board new_board;
    for (int i = 0; i < 14; i++)
        new_board.pockets[i] = board.pockets[i];
    return new_board;
}


Board getMove(Board b, int index) {
    Board board = getCopy(b);
    bool top = index > 0 && index < 7;
    int beads = board.pockets[index];
    board.pockets[index--] = 0;
    while (beads--) {
        if ((!top && !index) || index == -1) index = 13; // for going round and skipping opponent store
        else if (top && index == 7) index--; //skip opponents store
        cout << "value: " << board.pockets[index] << ", index: " << index << ", beads, " << beads << endl;
        board.pockets[index]++;

        //steal
        if(!beads && board.pockets[index] == 1) {
            cout << "index: " << 14-index << ", val: " << board.pockets[14-index] << endl;
            if(top) board.pockets[0] += board.pockets[14-index] + 1;
            else board.pockets[7] += board.pockets[14-index] + 1;
            board.pockets[14-index] = board.pockets[index] = 0;
        }

        index--;
    }
    return board;
}


bool end_of_game(Board board){
    int sum1 = 0, sum2 = 0;
    for(int i = 1; i<7; i++) sum1 += board.pockets[i];
    for(int i = 8; i<14; i++) sum2 += board.pockets[i];
    return (!sum1 || !sum2);
}


void printBoard(Board board) {
    cout << "\t";
    for (int i = 1; i < 7; i++) cout << board.pockets[i] << " ";
    cout << endl << board.pockets[0] << "\t\t\t " << board.pockets[7] << endl << "\t";
    for (int i = 13; i > 7; i--) cout << board.pockets[i] << " ";
    cout << endl;
}


int main() {
    Board b, copy;
    b.pockets[13] = 34;
    //copy = b.getCopy();
    printBoard(copy);
    return 0;
}
