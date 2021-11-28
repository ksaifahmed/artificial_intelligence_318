#include <bits/stdc++.h>
using namespace std;


int hamming_distance(int **matrix, int ** goal_mat, int k) {
    int h = 0;
    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++) {
            if(matrix[i][j] != goal_mat[i][j] && goal_mat[i][j]) h++;
        }
    return h;
}


typedef pair<int, int> position;
int manhattan_distance(int **matrix, int **goal_mat ,int k) {
    int man = 0;
    map<int, position> position_matrix;
    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++) {
            position_matrix[matrix[i][j]] = make_pair(i, j);
            cout << position_matrix[matrix[i][j]].first << "," << position_matrix[matrix[i][j]].second << endl;
        }

    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++)
            if(matrix[i][j] != goal_mat[i][j] && goal_mat[i][j]) {
                position pos = position_matrix[goal_mat[i][j]];
                man += abs(pos.first - i) + abs(pos.second - j);
            }

    return man;
}