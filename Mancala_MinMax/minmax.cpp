#include <bits/stdc++.h>
#include "game_board.cpp"
using namespace std;


#define MAX_DEPTH 7
#define INF 2147480000


//HEURISTIC FUNCTIONS
int heuristic1(Board board){ return board.pockets[0] - board.pockets[7]; }












typedef pair<Board, int> ScoreBoard;
ScoreBoard pruned_minmax(Board board, int depth, bool is_max, int alpha, int beta) {
    //leaf
    if(end_of_game(board)) {
        if(board.pockets[0] > board.pockets[7])
            return make_pair(board, board.pockets[0]+INF);
        else return make_pair(board, -(board.pockets[7]+INF));
    }

    //max_depth e heuristic 1
    if(depth == MAX_DEPTH) {
        //cout << board.pockets[0] - board.pockets[7] << " -> scores" << endl;
        return make_pair(board, heuristic1(board));
    }

    if(is_max){
        int best_score = -INF;
        BoardChild list = getChildren(board, true); //gets children of top(first) player
        Board best_board = list.at(0);
        for(auto child : list) {
            //printBoard(child);
            int score = pruned_minmax(child, depth+1, false, alpha, beta).second;
            if(best_score < score) {
                best_score = score;
                best_board = child;
            }
            if(best_score >= beta) return make_pair(best_board, best_score);
            alpha = max(alpha, best_score);
        }
        return make_pair(best_board, best_score);

    }else{
        int best_score = INF;
        BoardChild list = getChildren(board, false); //gets children of bottom(second) player
        Board best_board = list.at(0);
        for(auto child : list){
            int score = pruned_minmax(child, depth+1, true, alpha, beta).second;
            if(best_score > score) {
                best_score = score;
                best_board = child;
            }
            if(best_score <= alpha) return make_pair(best_board, best_score);
            beta = min(beta, best_score);
        }
        return make_pair(best_board, best_score);
    }
}