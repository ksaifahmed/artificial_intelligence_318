#include <bits/stdc++.h>
#include "game_board.cpp"
#include "heuristics.cpp"
using namespace std;


#define MAX_DEPTH 7
#define INF 2147480000



typedef pair<Board, int> ScoreBoard;
ScoreBoard pruned_minmax(Board board, int depth, bool is_max, int alpha, int beta, int heuristic, bool is_top) {
    //leaf
    if(end_of_game(board)) {
        if(is_top){ //minmax called by top player
            if(top_won(board)) //if top wins, return top_store+infinity
                return make_pair(board, board.pockets[0]+INF);
            else return make_pair(board, -(board.pockets[7]+INF));
        }else{ //minmax called by bottom player
            if(!top_won(board)) //if bottom wins, return bottom_store+infinity
                return make_pair(board, board.pockets[7]+INF);
            else return make_pair(board, -(board.pockets[0]+INF));
        }
    }

    //if depth == 0, check for bonus
    if(!depth) {
        if(is_top){
            for(int i=1; i<7; i++)
                if(bonus_turn(board, i, true)) return make_pair(getTopPlayerMove(board, i), INF);
        }else{
            for(int i=8; i<14; i++)
                if(bonus_turn(board, i, false)) return make_pair(getBottomPlayerMove(board, i), INF);
        }
    }

    //max_depth e heuristic 1
    if(depth == MAX_DEPTH) {
        //cout << board.pockets[0] - board.pockets[7] << " -> scores" << endl;
        return make_pair(board, Heuristics::get(heuristic, board, is_top));
    }

    if(is_max){
        int best_score = -INF-1000;
        BoardChild list = getChildren(board, is_top); //gets children of top(first) player
        Board best_board = list.at(0);
        for(auto child : list) {
            //printBoard(child);
            int score = pruned_minmax(child, depth+1, false, alpha, beta, heuristic, is_top).second;

            if(best_score < score) {
                best_score = score;
                best_board = child;
            }else if(best_score == score){
                best_board = random_choice(best_board, child);
            }

            if(best_score >= beta) return make_pair(best_board, best_score);
            alpha = max(alpha, best_score);
        }
        return make_pair(best_board, best_score);

    }else{
        int best_score = INF+1000;
        BoardChild list = getChildren(board, !is_top); //gets children of bottom(second) player
        Board best_board = list.at(0);
        for(auto child : list){
            int score = pruned_minmax(child, depth+1, true, alpha, beta, heuristic, is_top).second;

            if(best_score > score) {
                best_score = score;
                best_board = child;
            }else if(best_score == score){
                best_board = random_choice(best_board, child);
            }

            if(best_score <= alpha) return make_pair(best_board, best_score);
            beta = min(beta, best_score);
        }
        return make_pair(best_board, best_score);
    }
}