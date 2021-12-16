#include <bits/stdc++.h>
using namespace std;
#include "comp_vs_human.cpp"


void start_game(){
    Board board;
    board.init_board();
    int mode; char first;

    cout << "1 for computer vs human, 2 for computer vs computer" << endl;
    cin >> mode;
    if(mode == 1){
        cout << "Would you like to go first? [y]" << endl;
        cin >> first;
        if(first == 'y'){
            start_human_vs_comp(board, true);
        }else start_human_vs_comp(board, false);
    }else {
        cout << "invalid mode, terminating game...\n";
    }
}



int main() {
    start_game();
    return 0;
}
