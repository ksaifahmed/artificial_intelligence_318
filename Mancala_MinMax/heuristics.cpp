#include <bits/stdc++.h>
using namespace std;

#define W1 10
#define W2 20
#define W3 30


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
        else {
            if(is_top) return board.pockets[0] - board.pockets[7];
            else return board.pockets[7] - board.pockets[0];
        }
    }
};

