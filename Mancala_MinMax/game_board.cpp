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


bool isEqual(Board board1, Board board2){
    for(int i=0; i<14; i++){
        if(board1.pockets[i] != board2.pockets[i])
            return false;
    }
    return true;
}


Board getTopPlayerMove(Board b, int index) {
    Board board = getCopy(b);
    int beads = board.pockets[index];
    board.pockets[index--] = 0;

    while (beads--) {
        if(index == -1) index = 13;
        if(index == 7) index = 6;
        board.pockets[index]++;
        if(!beads && index > 0 && index < 7 && board.pockets[index] == 1 && board.pockets[14-index]) {
            board.pockets[0] += board.pockets[14-index] + 1;
            board.pockets[index] = board.pockets[14-index] = 0;
        }
        index--;

    }
    return board;
}


Board getBottomPlayerMove(Board b, int index) {
    Board board = getCopy(b);
    int beads = board.pockets[index];
    board.pockets[index--] = 0;

    while (beads--) {
        if(index == 0) index = 13;
        board.pockets[index]++;
        if(!beads && index > 7 && index < 14 && board.pockets[index] == 1 && board.pockets[14-index]) {
            board.pockets[7] += board.pockets[14-index] + 1;
            board.pockets[index] = board.pockets[14-index] = 0;
        }
        index--;

    }
    return board;
}


bool bonus_turn(Board board, int index, bool top){
    int beads = board.pockets[index--];
    if(!top){
        while (beads--) {
            if(index == 0) index = 13;
            if(!beads && index == 7) return true;
            index--;
        }
    }else{
        while (beads--) {
            if(index == -1) index = 13;
            if(index == 7) index = 6;
            if(!beads && index == 0) return true;
            index--;
        }
    }
    return false;
}


bool bonus_turn(Board original, Board new_board, bool top){
    if(top){
        for(int i=1; i<7; i++){
            if(original.pockets[i]) {
                Board child = getTopPlayerMove(original, i);
                if(bonus_turn(original, i, top) && isEqual(child, new_board))
                    return true;
            }
        }
    }else{
        for(int i=13; i>7; i--){
            if(original.pockets[i]) {
                Board child = getBottomPlayerMove(original, i);
                if(bonus_turn(original, i, !top) && isEqual(child, new_board))
                    return true;
            }
        }
    }

    return false;
}


typedef vector<Board> BoardChild;
BoardChild getChildren(Board board, bool top){
    BoardChild list;
    if(top){
        for(int i=1; i<7; i++){
            if(board.pockets[i]){
                list.push_back(getTopPlayerMove(board, i));
                if(bonus_turn(board, i, true)) swap(list[0], list[list.size()-1]);
            }
        }

    }else{
        for(int i=8; i<14; i++){
            if(board.pockets[i]){
                list.push_back(getBottomPlayerMove(board, i));
                if(bonus_turn(board, i, false)) swap(list[0], list[list.size()-1]);
            }
        }
    }
    return list;
}


bool end_of_game(Board board){
    int sum1 = 0, sum2 = 0;
    for(int i = 1; i<7; i++) sum1 += board.pockets[i];
    for(int i = 8; i<14; i++) sum2 += board.pockets[i];
    return (!sum1 || !sum2);
}

bool top_won(Board board){
    int sum1 = 0, sum2 = 0;
    for(int i = 1; i<7; i++) sum1 += board.pockets[i];
    for(int i = 8; i<14; i++) sum2 += board.pockets[i];
    if(board.pockets[0] == board.pockets[7]) return sum1 > sum2;
    return board.pockets[0] > board.pockets[7];
}

void printBoard(Board board) {
    cout << "\n\t";
    for (int i = 1; i < 7; i++) cout << board.pockets[i] << " ";
    cout << endl << board.pockets[0] << "\t\t\t " << board.pockets[7] << endl << "\t";
    for (int i = 13; i > 7; i--) cout << board.pockets[i] << " ";
    cout << endl << endl;
}

