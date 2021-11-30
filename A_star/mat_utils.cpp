#include <bits/stdc++.h>
using namespace std;

typedef vector<vector <int> > Matrix;
void print_matrix(Matrix matrix)
{
    cout << endl;
    for(int i=0; i<matrix.size(); i++) {
        for(int j=0; j<matrix.size(); j++) {
            if(matrix.at(i).at(j)) cout << matrix.at(i).at(j) << " ";
            else cout << "* ";
        }
        cout << endl;
    }cout <<"----------------------------------"<<endl;

}


void swap_matrix_elm(Matrix *matrix, int i1, int r1, int i2, int r2) {
    int temp = matrix -> at(i1).at(r1);
    matrix -> at(i1).at(r1) = matrix -> at(i2).at(r2) ;
    matrix -> at(i2).at(r2) = temp;
}


Matrix copyMatrix(vector<vector <int> > matrix)
{
    Matrix new_mat;

    for(int i=0; i<matrix.size(); i++) {
        vector<int> v1;
        v1.reserve(matrix.size());
        for(int j=0; j<matrix.size(); j++) {
            v1.push_back(matrix.at(i).at(j));
        }new_mat.push_back(v1);
    }
    return new_mat;
}


Matrix get_matrix(int grid_size) {
    Matrix matrix;
    int n;
    cout << "Enter initial board layout:" << endl;
    for (int i = 0; i < grid_size; i++) {
        vector<int> v1;
        v1.reserve(grid_size);
        for (int j = 0; j < grid_size; j++) {
            cin >> n;
            v1.push_back(n);
        }matrix.push_back(v1);
    }
    return matrix;
}


Matrix get_goal_matrix(int grid_size)
{
    Matrix matrix;
    int val = 0;

    for(int i=0; i<grid_size; i++) {
        vector<int> v1;
        v1.reserve(matrix.size());
        for(int j=0; j<grid_size; j++)
            v1.push_back(++val);
        matrix.push_back(v1);
    }
    matrix.at(grid_size-1).at(grid_size-1) = 0;
    return matrix;
}


int get_inversions(Matrix matrix) {
    int k = matrix.size();
    int inv = 0, size = k*k - 1;
    vector<int> list;

    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++)
            if(matrix.at(i).at(j))
                list.push_back(matrix.at(i).at(j));

    for(int i=0; i<size; i++)
        for(int j=i+1; j<size; j++)
            if(list.at(i)> list.at(j)) inv++;

    return inv;
}


void is_solvable(Matrix matrix) {
    int k = matrix.size();
    int inv = get_inversions(matrix);
    //odd grid_size e.g. 3
    if(k&1) {
        if(!(inv&1)) cout << "Puzzle solvable!" << endl; //if inv is even
        else cout << "Puzzle NOT solvable!" << endl; //if inv is odd
    }
    //even grid_size e.g. 4
    else {
        int blank_r = -1;
        for(int i=0; i<k; i++)
            for(int j=0; j<k; j++)
                if(!matrix.at(i).at(j)) {
                    blank_r = i;
                    cout << "\nrow of zero: " << i << endl;
                    break;
                }
        if((blank_r&1 && !(inv&1)) || (!(blank_r&1) && inv&1))
            cout << "Puzzle solvable!" << endl;
        else cout << "Puzzle NOT solvable!" << endl;
    }
}

pair<int, int> get_blank_pos(Matrix matrix) {
    for(int i=0; i<matrix.size(); i++)
        for(int j=0; j<matrix.size(); j++)
            if (!matrix.at(i).at(j)) return make_pair(i, j);

    return make_pair(-1, -1);
}

vector< Matrix > get_neighbours(Matrix matrix) {
    vector< Matrix > neighbours;
    pair<int, int> blank_pos = get_blank_pos(matrix);

    if(blank_pos.first != 0) { //can move UP
        Matrix m = copyMatrix(matrix);
        swap_matrix_elm(&m, blank_pos.first, blank_pos.second, blank_pos.first - 1, blank_pos.second);
        neighbours.push_back(m);
    }
    if(blank_pos.first != matrix.size() - 1) { //can move DOWN
        Matrix m = copyMatrix(matrix);
        swap_matrix_elm(&m, blank_pos.first, blank_pos.second, blank_pos.first + 1, blank_pos.second);
        neighbours.push_back(m);
    }
    if(blank_pos.second != 0) { //can move LEFT
        Matrix m = copyMatrix(matrix);
        swap_matrix_elm(&m, blank_pos.first, blank_pos.second, blank_pos.first, blank_pos.second - 1);
        neighbours.push_back(m);
    }
    if(blank_pos.second != matrix.size() - 1) { //can move RIGHT
        Matrix m = copyMatrix(matrix);
        swap_matrix_elm(&m, blank_pos.first, blank_pos.second, blank_pos.first, blank_pos.second + 1);
        neighbours.push_back(m);
    }

    return neighbours;
}
