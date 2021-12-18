#include <bits/stdc++.h>
using namespace std;

#define W1 50
#define W2 5
#define W3 100


//HEURISTIC FUNCTIONS
class Heuristics{
public:
    static void display_heuristics(){
        cout << "============HEURISTIC 1===========\n";
        cout << "(stones_in_my_storage - stones_in_opponents_storage)\n\n";

        cout << "============HEURISTIC 2===========\n";
        cout << "W1 * (stones_in_my_storage - stones_in_opponents_storage) + W2 * (stones_on_my_side - stones_on_opponents_side)\n\n";

        cout << "============HEURISTIC 3===========\n";
        cout << "W1 * (stones_in_my_storage - stones_in_opponents_storage) + W2 * (stones_on_my_side - stones_on_opponents_side) + W3 * (additional_move_earned)\n\n";

        cout << "============HEURISTIC 4===========\n";
        cout << "(stones_in_my_storage - stones_in_opponents_storage)\n\n";

        cout << "============HEURISTIC 5===========\n";
        cout << "(stones_in_my_storage - stones_in_opponents_storage)\n\n";

        cout << "============HEURISTIC 6===========\n";
        cout << "(stones_in_my_storage - stones_in_opponents_storage)\n\n";
    }

    static int get(int n, Board board, bool is_top){
        if(n == 2) {
            int stones1 = 0, stones2 = 0, ret_val;
            for(int i=1; i<7; i++) stones1 += board.pockets[i];
            for(int i=13; i>7; i--) stones2 += board.pockets[i];
            ret_val = W1*(board.pockets[0] - board.pockets[7]) + W2*(stones1-stones2);
            if(is_top) return ret_val;
            else return -ret_val;
        }
        else if(n == 3){
            int stones1 = 0, stones2 = 0, ret_val;
            int bonus_top = 0, bonus_bottom = 0;
            for(int i=1; i<7; i++) {
                stones1 += board.pockets[i];
                if(bonus_turn(board, i, true)) bonus_top++;
            }
            for(int i=13; i>7; i--) {
                stones2 += board.pockets[i];
                if(bonus_turn(board, i, false)) bonus_bottom++;
            }
            if(is_top) return W1*(board.pockets[0] - board.pockets[7]) + W2*(stones1-stones2) + W3 * bonus_top;
            else return W1*(board.pockets[7] - board.pockets[0]) + W2*(stones2-stones1) + W3 * bonus_bottom;
        }
        else {
            if(is_top) return board.pockets[0] - board.pockets[7];
            else return board.pockets[7] - board.pockets[0];
        }
    }
};
