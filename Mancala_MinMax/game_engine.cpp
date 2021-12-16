#include <bits/stdc++.h>
using namespace std;
#include "minmax.cpp"


void start_human_vs_comp(Board board, bool human_first){
    int limit = 100, move;
    if(human_first){
        cout << "========= CURRENT STATE ===========\n";
        printBoard(board);
        while (limit--){
            while (1){
                Board temp = getCopy(board);
                cout << "Your turn [pockets 1-6 on your side]: "; cin >> move;
                if(move>0 && move<7){
                    if(board.pockets[14-move]) {
                        board = getBottomPlayerMove(board, 14 - move);
                    }
                    else{
                        cout << "Pocket is empty, try again!" << endl; continue;
                    }
                }else{
                    cout << "wrong input!\n"; continue;
                }
                cout << "========= after your move: ===========\n";
                printBoard(board);

                if(end_of_game(board) && top_won(board)) {
                    if(top_won(board))
                        cout << "You lost :( \n";
                    else cout << "Congratulations, you win!!!!!\n";
                    return;
                }
                if (bonus_turn(temp, 14 - move, false)) {
                    cout << "BONUS TURN\n";
                    continue;
                } break;
            }

            while (1){
                Board temp = getCopy(board);
                board = pruned_minmax(board, 0, true, -INF, INF).first;
                cout << "========= computer's move: ===========\n";
                printBoard(board);

                if(end_of_game(board) && top_won(board)) {
                    if(top_won(board))
                        cout << "You lost :( \n";
                    else cout << "Congratulations, you win!!!!!\n";
                    return;
                }

                if(bonus_turn(temp, board, true)) {
                    cout << "BONUS TUNR\n";
                    continue;
                } break;
            }
        }
    }
    ///COMPUTER GOES FIRST
    else{
        cout << "========= INITIAL BOARD ===========\n";
        printBoard(board);

        while (limit--){
            break;
        }
    }
}



void start_comp_vs_comp()
{

}