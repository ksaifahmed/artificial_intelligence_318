#include <bits/stdc++.h>
using namespace std;


void print_matrix(int ** matrix, int grid_size)
{
    cout << endl;
    for(int i=0; i<grid_size; i++) {
        for(int j=0; j<grid_size; j++) {
            if(matrix[i][j]) cout << matrix[i][j] << " ";
            else cout << "* ";
        }
        cout << endl;
    }cout <<"----------------------------------"<<endl;

}

int ** copyMatrix(int ** matrix, int grid_size)
{
    int ** new_mat = new int*[grid_size];
    for(int i=0; i<grid_size; i++) new_mat[i] = new int[grid_size];

    for(int i=0; i<grid_size; i++)
        for(int j=0; j<grid_size; j++)
             new_mat[i][j] = matrix[i][j];
    return new_mat;
}


int **get_matrix(int grid_size) {
    int **matrix = new int *[grid_size];
    for (int i = 0; i < grid_size; i++)
        matrix[i] = new int[grid_size];

    cout << "Enter initial board layout:" << endl;
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}


int ** get_goal_matrix(int grid_size)
{
    int ** matrix = new int*[grid_size];
    for(int i=0; i<grid_size; i++) matrix[i] = new int[grid_size];
    int val = 0;

    for(int i=0; i<grid_size; i++)
        for(int j=0; j<grid_size; j++)
            matrix[i][j] = ++val;


    matrix[grid_size-1][grid_size-1] = 0;
    return matrix;
}


bool is_equal_matrix(int ** mat1, int ** mat2, int k)
{
    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++)
            if(mat1[i][j] != mat2[i][j]) return false;
    return true;
}


int get_inversions(int **matrix, int k) {
    int inv = 0, size = k*k - 1;
    int *arr = new int[size];

    int c = 0;
    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++)
            if(matrix[i][j])
                arr[c++] = matrix[i][j];

    for(int i=0; i<size; i++)
        for(int j=i+1; j<size; j++)
            if(arr[i] > arr[j]) inv++;

    return inv;
}


void is_solvable(int **matrix, int k) {
    int inv = get_inversions(matrix, k);
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
                if(!matrix[i][j]) {
                    blank_r = i;
                    cout << "\nrow of zero: " << i << endl;
                    break;
                }
        if((blank_r&1 && !(inv&1)) || (!(blank_r&1) && inv&1))
            cout << "Puzzle solvable!" << endl;
        else cout << "Puzzle NOT solvable!" << endl;
    }
}

