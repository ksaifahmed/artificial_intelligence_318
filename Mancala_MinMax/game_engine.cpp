#include <bits/stdc++.h>
using namespace std;
#include "minmax.cpp"


void start_human_vs_comp(Board board, bool human_first, int heuristics){
    int limit = 10000, move;
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

                if(end_of_game(board)) {
                    if(top_won(board))
                        cout << "You lost :( \n";
                    else cout << "Congratulations, you win!!!!!\n";
                    return;
                }
                if (bonus_turn(temp, 14 - move, false)) {
                    cout << "BONUS TURN FOR YOU\n";
                    continue;
                } break;
            }

            while (1){
                Board temp = getCopy(board);
                board = pruned_minmax(board, 0, true, -INF, INF, heuristics, true).first;
                cout << "========= computer's move: ===========\n";
                printBoard(board);

                if(end_of_game(board)) {
                    if(top_won(board))
                        cout << "You lost :( \n";
                    else cout << "Congratulations, you win!!!!!\n";
                    return;
                }

                if(bonus_turn(temp, board, true)) {
                    cout << "BONUS TURN FOR COMPUTER\n";
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
            while (1){
                Board temp = getCopy(board);
                board = pruned_minmax(board, 0, true, -INF, INF, heuristics, true).first;
                cout << "========= computer's move: ===========\n";
                printBoard(board);

                if(end_of_game(board)) {
                    if(top_won(board))
                        cout << "You lost :( \n";
                    else cout << "Congratulations, you win!!!!!\n";
                    return;
                }

                if(bonus_turn(temp, board, true)) {
                    cout << "BONUS TURN FOR COMPUTER\n";
                    continue;
                } break;
            }

            while(1) {
                cout << "========================================\n";
                cout << "Your turn [pockets 1-6 on your side]: "; cin >> move;
                Board temp = getCopy(board);
                if(move>0 && move<7){
                    if(board.pockets[14-move])
                        board = getBottomPlayerMove(board, 14-move);
                    else{
                        cout << "Pocket is empty, try again!" << endl; continue;
                    }
                }else{
                    cout << "wrong input!\n"; continue;
                }
                cout << "========= after your move: ===========\n";
                printBoard(board);

                if(end_of_game(board)) {
                    if(top_won(board))
                        cout << "You lost :( \n";
                    else cout << "Congratulations, you win!!!!!\n";
                    return;
                }

                if (bonus_turn(temp, 14 - move, false)) {
                    cout << "BONUS TURN FOR YOU\n";
                    continue;
                } break;
            }
        }
    }
}



void start_comp_vs_comp(Board board, int h1, int h2)
{
    int limiter = 20000;
    while(limiter--){
        cout << "========= START STATE ===========\n";
        printBoard(board);
        //AGENT 1
        while (1){
            Board temp = getCopy(board);
            board = pruned_minmax(board, 0, true, -INF, INF, h1, true).first;
            cout << "========= Agent with Heuristic " << h1 << "'s move: ===========\n";
            printBoard(board);

            if(end_of_game(board)) {
                if(top_won(board))
                    cout << "Agent with Heuristic "<< h1 <<" WINS!!!\n";
                else cout << "Agent with Heuristic "<< h2 <<" WINS!!!\n";
                return;
            }

            if(bonus_turn(temp, board, true)) {
                cout << "BONUS TURN FOR AGENT WITH HEURISTIC " << h1 <<"\n";
                continue;
            } break;
        }

        //AGENT 2
        while (1){
            Board temp = getCopy(board);
            board = pruned_minmax(board, 0, true, -INF, INF, h2, false).first;
            cout << "========= Agent with Heuristic " << h2 << "'s move: ===========\n";
            printBoard(board);

            if(end_of_game(board)) {
                if(top_won(board))
                    cout << "Agent with Heuristic "<< h1 <<" WINS!!!\n";
                else cout << "Agent with Heuristic "<< h2 <<" WINS!!!\n";
                return;
            }

            if(bonus_turn(temp, board, false)) {
                cout << "BONUS TURN FOR AGENT WITH HEURISTIC " << h2 <<"\n";
                continue;
            } break;
        }

    }
}


///for generating results
int fight_comp_vs_comp(Board board, int h1, int h2){
    int limiter = 200000;
    while(limiter--){
        //AGENT 1
        while (1){
            Board temp = getCopy(board);
            board = pruned_minmax(board, 0, true, -INF, INF, h1, true).first;
            if(end_of_game(board)) {
                if(top_won(board))
                    return 1;
                else return 0;
            }

            if(bonus_turn(temp, board, true)) {
                continue;
            } break;
        }

        //AGENT 2
        while (1){
            Board temp = getCopy(board);
            board = pruned_minmax(board, 0, true, -INF, INF, h2, false).first;

            if(end_of_game(board)) {
                if(top_won(board))
                    return 1;
                else return 0;
            }

            if(bonus_turn(temp, board, false)) {
                continue;
            } break;
        }

    }
    return -1;
}