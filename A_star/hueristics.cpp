#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> position;


int hamming_distance(int **matrix, int ** goal_mat, int k) {
    int h = 0;
    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++) {
            if(matrix[i][j] != goal_mat[i][j] && goal_mat[i][j]) h++;
        }
    return h;
}


int manhattan_distance(int **matrix, int **goal_mat ,int k) {
    int man = 0;
    map<int, position> position_matrix;
    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++)
            position_matrix[matrix[i][j]] = make_pair(i, j);

    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++)
            if(matrix[i][j] != goal_mat[i][j] && goal_mat[i][j]) {
                position pos = position_matrix[goal_mat[i][j]];
                man += abs(pos.first - i) + abs(pos.second - j);
            }

    return man;
}


bool correct_row(int val, int row, int k) {
    int bound = k * row;
    return val > bound && val <= (bound+k);
}

int linear_conflict(int **matrix, int **goal_mat ,int k) {
    int conflicts = 0;
    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++) {
            //row conflicts
            if(correct_row(matrix[i][j], i, k)) {
                for(int c=j+1; c<k; c++)
                    if(matrix[i][j] > matrix[i][c] && correct_row(matrix[i][c], i, k)) {
                        conflicts++;
                        cout << "pairs: " << matrix[i][j] << "," << matrix[i][c] << endl;
                    }
            }
            //column conflicts?
        }
    return conflicts * 2 + manhattan_distance(matrix, goal_mat, k);
}