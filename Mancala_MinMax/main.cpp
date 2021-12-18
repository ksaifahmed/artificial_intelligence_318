#include <bits/stdc++.h>
using namespace std;
#include "game_engine.cpp"


void start_game(){
    Board board;
    board.init_board();
    int mode; char first;

    cout << "1 for computer vs human, 2 for computer vs computer, 3 for 100 results" << endl;
    cin >> mode;

    if(mode == 1){
        cout << "Would you like to go first? [y]" << endl;
        cin >> first;
        if(first == 'y'){
            start_human_vs_comp(board, true, 3);
        }else start_human_vs_comp(board, false, 3);
    }



    else if(mode == 2){
        int h1, h2;
        Heuristics::display_heuristics();
        cout << "Select heuristics for computer 1: ";
        cin >> h1;
        cout << "Select heuristics for computer 2: ";
        cin >> h2;
        start_comp_vs_comp(board, h1, h2);
    }


    //results
    else if(mode == 3){
        int h1, h2, limiter = 100;
        int c1 = 0, c2 = 0;
        srand(time(nullptr));
        Heuristics::display_heuristics();
        cout << "Select heuristics for computer 1: ";
        cin >> h1;
        cout << "Select heuristics for computer 2: ";
        cin >> h2;
        while (limiter--){
            int res = fight_comp_vs_comp(board, h1, h2);
            if(res == 1) {
                cout << "Agent with Heuristic "<< h1 <<" WINS!!!\n";
                c1++;
            }
            else if(res == 0) {
                cout << "Agent with Heuristic "<< h2 <<" WINS!!!\n";
                c2++;
            }
        }
        cout << "Heuristic " << h1 << " won " << c1 << " times!\n";
        cout << "Heuristic " << h2 << " won " << c2 << " times!\n";
    }


    else {
        cout << "invalid mode, terminating game...\n";
    }

}



int main() {
    start_game();
    return 0;
}
