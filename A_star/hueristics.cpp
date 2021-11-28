#include <bits/stdc++.h>
using namespace std;

int hamming_distance(int **matrix, int k) {
    int h = 0; int num = 1;
    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++) {
            cout << "num :" << num << ", mat: " << matrix[i][j] << endl;
            if(matrix[i][j] != num++) h++;
        }
    return --h;
}

