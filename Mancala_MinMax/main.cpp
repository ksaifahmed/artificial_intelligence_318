#include <bits/stdc++.h>
using namespace std;
#include "game_engine.cpp"


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
            start_human_vs_comp(board, true, 1);
        }else start_human_vs_comp(board, false, 1);
    }else if(mode == 2){
        int h1, h2;
        Heuristics::display_heuristics();
        cout << "Select heuristics for computer 1: ";
        cin >> h1;
        cout << "Select heuristics for computer 2: ";
        cin >> h2;
        start_comp_vs_comp(board, h1, h2);
    }
    else {
        cout << "invalid mode, terminating game...\n";
    }
}



int main() {
    start_game();
    return 0;
}
