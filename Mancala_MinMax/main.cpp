#include <bits/stdc++.h>

using namespace std;
#define INF 2147480000
#define MAX_DEPTH 10

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
typedef vector<Board> BoardChild;


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
        //cout << "value: " << board.pockets[index] << ", index: " << index << ", beads, " << beads << endl;
        board.pockets[index]++;

        //steal
        if(!beads && board.pockets[index] == 1 && index != 0 & index != 7) {
            //cout << "index: " << 14-index << ", val: " << board.pockets[14-index] << endl;
            if(top) board.pockets[0] += board.pockets[14-index] + 1;
            else board.pockets[7] += board.pockets[14-index] + 1;
            board.pockets[14-index] = board.pockets[index] = 0;
        }

        index--;
    }
    return board;
}


BoardChild getChildren(Board board, bool top){
    BoardChild list;
    if(top){
        for(int i=0; i<7; i++){
            if(board.pockets[i])
                list.push_back(getMove(board, i));
        }

    }else{
        for(int i=13; i>7; i--){
            if(board.pockets[i])
                list.push_back(getMove(board, i));
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


void printBoard(Board board) {
    cout << "\t";
    for (int i = 1; i < 7; i++) cout << board.pockets[i] << " ";
    cout << endl << board.pockets[0] << "\t\t\t " << board.pockets[7] << endl << "\t";
    for (int i = 13; i > 7; i--) cout << board.pockets[i] << " ";
    cout << endl;
}



typedef pair<Board, int> ScoreBoard;
ScoreBoard pruned_minmax(Board board, int depth, bool is_max, int alpha, int beta) {
    //leaf
    if(end_of_game(board)) {
        if(board.pockets[0] > board.pockets[7])
            return make_pair(board, board.pockets[0]+INF);
        else return make_pair(board, -(board.pockets[7]+INF));
    }

    //max_depth
    if(depth == MAX_DEPTH) {
        return make_pair(board, board.pockets[7] - board.pockets[0]);
    }

    if(is_max){
        int best_score = -INF;
        BoardChild list = getChildren(board, true); //gets children of top(first) player
        for(auto child : list) {
            int score = pruned_minmax(child, depth+1, false, alpha, beta).second;
            best_score = max(score, best_score);
            if(best_score >= beta) return make_pair(board, best_score);
            alpha = max(alpha, best_score);
        }
        return make_pair(board, best_score);

    }else{
        int best_score = INF;
        BoardChild list = getChildren(board, false); //gets children of bottom(second) player
        for(auto child : list){
            int score = pruned_minmax(child, depth+1, true, alpha, beta).second;
            best_score = min(score, best_score);
            if(best_score <= alpha) return make_pair(board, best_score);
            beta = min(beta, best_score);
        }
        return make_pair(board, best_score);
    }
}




int main() {
    Board b;
    b.init_board();

    cout << "best: " << pruned_minmax(b, 0, true, -INF, INF).second << endl;

    BoardChild list = getChildren(b, true);
    for(auto child : list) {
        cout << "score is : " << pruned_minmax(child, 1, false, -INF, INF).second << endl;
    }
    //printBoard(getMove(b, 4));
    return 0;
}
