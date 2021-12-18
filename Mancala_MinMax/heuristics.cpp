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
        cout << "diff_of_stones_in_stores\n";

        cout << "============HEURISTIC 2===========\n";
        cout << "W1 * diff_of_stones_in_stores + W2 * diff_of_stones_in_pockets\n";

        cout << "============HEURISTIC 3===========\n";
        cout << "W1 * diff_of_stones_in_stores + W2 * diff_of_stones_in_pockets + W3 * bonus\n";

        cout << "============HEURISTIC 4===========\n";
        cout << "how close i am to winning - how close opponent is to winning\n";

        cout << "============HEURISTIC 5===========\n";
        cout << "MAX OF (how close to winning, storage_stone_difference) + weight * bonus\n";

        cout << "============HEURISTIC 6===========\n";
        cout << "stones_in_my_storage - stones_in_opponents_storage\n";
        cout << "==================================\n\n";
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
            int stones1 = 0, stones2 = 0;
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


        ///how close i am to winning - how close opponent is to winning
        else if(n == 4){
            if(is_top) return abs(24-board.pockets[0]) - abs(24-board.pockets[7]);
            else return abs(24-board.pockets[7]) - abs(24-board.pockets[0]);
        }


        ///MAX OF (how close to winning, stone_difference) + weight * bonus
        else if(n == 5){
            int bonus_top = 0, bonus_bottom = 0;
            for(int i=1; i<7; i++) {
                if(bonus_turn(board, i, true)) bonus_top++;
            }

            for(int i=13; i>7; i--) {
                if(bonus_turn(board, i, false)) bonus_bottom++;
            }

            int stone_diff = board.pockets[0] - board.pockets[7];
            if(is_top) return max(abs(24-board.pockets[0]) - abs(24-board.pockets[7]), stone_diff) + W3 * bonus_top;
            else return max(abs(24-board.pockets[7]) - abs(24-board.pockets[0]), -stone_diff) + W3 * bonus_bottom;
        }


        ///difference of stones in stores + bonus + steal
        else if (n == 6){
            int bonus_top = 0, bonus_bottom = 0;
            int steal_top = 0, steal_bottom = 0;
            for(int i=1; i<7; i++) {
                if(bonus_turn(board, i, true)) bonus_top++;
                if(steal_present(board, i, true)) steal_top++;
            }

            for(int i=13; i>7; i--) {
                if(bonus_turn(board, i, false)) bonus_bottom++;
                if(steal_present(board, i, false)) steal_bottom++;
            }

            if (is_top) return board.pockets[0] - board.pockets[7] + W3 * bonus_top + W1 * steal_bottom;
            else return board.pockets[7] - board.pockets[0] + W3 * bonus_bottom + W1 * steal_bottom;
        }


        //difference in stones for n = anything
        else {
            if(is_top) return board.pockets[0] - board.pockets[7];
            else return board.pockets[7] - board.pockets[0];
        }
    }
};

