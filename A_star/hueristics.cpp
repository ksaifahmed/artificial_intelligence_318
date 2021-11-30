#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> position;
typedef vector<vector <int> > Matrix;


int hamming_distance(Matrix matrix, Matrix goal_mat) {
    int h = 0, k = matrix.size();
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            if (matrix.at(i).at(j) != goal_mat.at(i).at(j) && goal_mat.at(i).at(j))
                h++;
        }
    return h;
}


int manhattan_distance(Matrix matrix, Matrix goal_mat) {
    int man = 0, k = matrix.size();
    map<int, position> position_matrix;
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            position_matrix[matrix.at(i).at(j)] = make_pair(i, j);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            if (matrix.at(i).at(j) != goal_mat.at(i).at(j) && goal_mat.at(i).at(j)) {
                position pos = position_matrix[goal_mat.at(i).at(j)];
                man += abs(pos.first - i) + abs(pos.second - j);
            }

    return man;
}


bool correct_row(int val, int row, int k) {
    int bound = k * row;
    return val > bound && val <= (bound + k);
}


bool correct_col(int val, int col, int k) {
    return (val % k == col + 1) && val;
}


int linear_conflict(Matrix matrix, Matrix goal_mat) {
    int conflicts = 0, k = matrix.size();
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            //row conflicts
            if (correct_row(matrix.at(i).at(j), i, k)) {
                for (int c = j + 1; c < k; c++)
                    if (matrix.at(i).at(j) > matrix.at(i).at(c) && correct_row(matrix.at(i).at(c), i, k)) {
                        conflicts++;
                        cout << "pairs: " << matrix.at(i).at(j) << "," << matrix.at(i).at(c) << endl;
                    }
            }

            //column conflicts
            if (correct_col(matrix.at(j).at(i), i, k)) {
                for (int c = j + 1; c < k; c++)
                    if (matrix.at(j).at(i) > matrix.at(c).at(i) && correct_col(matrix.at(c).at(i), i, k)) {
                        conflicts++;
                        cout << "pairs: " << matrix.at(j).at(i) << "," << matrix.at(c).at(i) << endl;
                    }
            }
        }

    return conflicts * 2 + manhattan_distance(matrix, std::move(goal_mat));
}


int get_h(const Matrix& matrix, const Matrix& goal_mat, int h) {
    if(h == 0) return hamming_distance(matrix, goal_mat);
    else if(h == 1) return manhattan_distance(matrix, goal_mat);
    else return linear_conflict(matrix, goal_mat);
}