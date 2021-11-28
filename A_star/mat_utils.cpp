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


int ** get_matrix(int grid_size)
{
    char c;
    int ** matrix = new int*[grid_size];
    for(int i=0; i<grid_size; i++) matrix[i] = new int[grid_size];

    cout << "Enter initial board layout:" << endl;
    for(int i=0; i<grid_size; i++) {
        for(int j=0; j<grid_size; j++) {
            cin >> c;
            matrix[i][j] = c - '0';
            if(matrix[i][j] == -6) {
                matrix[i][j] = 0;
            }
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
}
